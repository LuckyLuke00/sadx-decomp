// Creates the functions that Ghidra's analysis missed, such as ones only a table of
// pointers reaches. VC++ starts each function at a 16-byte boundary, except under /O1,
// and fills the bytes before it with int3 (0xCC). So a boundary starts a function when
// the code before it can't run into it: an int3 byte, a ret or jmp, or defined data,
// such as a jump table, that ends right there. Two cases look the same but aren't: a
// CC byte that belongs to another instruction, such as xor ecx, esp (33 CC), and an
// entry of a jump table, which is a code address next to another one. VC++ aligns a
// jump table to 4 bytes in its function with 1 to 3 bytes of fill, such as mov edi, edi
// (8B FF), and in a function that isn't aligned itself, such as the runtime's memcmp,
// that fill can sit at a boundary too. A table that an instruction reads, such as the
// table of case numbers that a switch reads with movzx after its jump table, is no
// function either. Boundaries go in address order, so the code of each new function
// covers the operand bytes inside it before they are checked.
// Code never runs through padding, so a boundary after int3 starts a function even where
// the body of another one ran into it with a jump. But code that runs into the middle of
// another function is part of it: unoptimized code leaves a dead jmp after a jmp, and
// such a jmp can sit at a boundary.
//
// The linker puts import stubs between the functions of the runtime, without padding. A
// stub is a jmp through a slot of the import table. Analysis disassembles only the stubs
// that a call reaches. The bytes of any other stub could be code that runs into what
// follows, and they are no function between two others. So each stub that starts after
// the end of other code gets a function, like the stubs that analysis reached.
//
// A switch reads its target from a table in the code right after its function. A
// jump that takes its target from a register or from a pointer in data, such as an
// interpreter's table of handlers, goes to other functions instead. So each target of
// such a jump starts a function too.
//
// A function can end in a jmp to another function: a tail call. Hand-written assembly,
// such as the runtime's math routines, also jumps to another routine on a condition.
// Analysis then takes the code at the target into the body of the first function that
// jumps there, apart from that function's own code. VC++ puts the code of a function in
// one piece, so code that a jump reaches past another function, after the end of other
// code, starts a function. So does the lowest code of a body that lies below the entry
// of its function, such as the entry point's jump to _tmainCRTStartup, with no other
// test. A catch block doesn't count as another function: VC++ puts
// it inside the code of its function, which goes on right after it. Targets go in
// address order, so a routine's start comes before the jumps inside it.
//
// A function or catch block that starts with a loop can start with a jmp forward to the
// loop's test, which jumps back to the code right after that jmp, such as a for loop in
// unoptimized code. Analysis takes such code for a thunk, a function that only jumps to
// another, and makes a function of the rest. So each pass first gives each such thunk
// its code back.
//
// An SEH scope table names a filter and a handler for each __try block of a function,
// and VC++ puts both inside the code of the function. The function calls the handler of
// a __finally block itself, so analysis makes a function there. And a filter can follow
// a ret at a boundary. So each pass first removes each function that starts in such a
// filter or handler, and no rule starts one there again. A table is an address that a
// function pushes: four cookie offsets, the first and third below zero, then for each
// block its enclosing level, its filter, or zero for __finally, and its handler. The
// table lies in read-only data. It ends at the first entry whose enclosing level is not
// -2 or the index of an earlier entry, or whose filter or handler is no code address.
//
// The runtime calls each entry of its tables of initializers and terminators, such as
// __xc_a to __xc_z. The startup code names a table's first slot and the slot after its
// last by address, and both hold zero. Between them are only code addresses and zeros.
// Nothing calls an entry, so analysis can leave its code in the body of the function
// before it, and a table can hold only one or two entries. So first each code address
// between two such zeros starts a function, and takes its code from the function
// that held it. If Ghidra can't start a function at one, the script stops with an error.
//
// Some functions only an address in an instruction or in data reaches. A push or a
// store to memory of a code address that starts after the end of other code hands over
// a function: a callback, a destructor for atexit, or the handler stub that an exception
// frame names. A catch block hands back the address where its function goes on in eax,
// so a load into a register doesn't count. Three or more code addresses in a row in
// read-only data are a table of entry points, such as a table of virtual functions or a
// longer table of initializers. A pair isn't: an SEH scope table holds a
// filter and a handler, and the handler is part of its function. Text can read as such a
// run too, such as "sin" or "cos". So an entry only counts where the code before it ends
// or at a 16-byte boundary, and tables come last, once the code that the other rules find
// is in place.
//
// A case block of a switch can also follow a ret or jmp at a boundary. So when a new
// function has a jump whose target it computes, analysis resolves that switch at once,
// and its case blocks join the function before the loop reaches them.
//
// Analysis still leaves code outside the function it belongs to, for four reasons.
// It resolves some switches after it has set the function's body, and it can't resolve
// a switch without a bounds check at all. It disassembles some data that looks like
// a code address, at the wrong offset into real code, which stops the real code where
// the two overlap. And it makes a function of code after a ret that only the jumps of
// the function before reach. So after each pass, each function gets back the code its
// flows reach outside its body.
// Passes repeat until nothing changes, because each one can disassemble more code. Each
// address gets one try at a function over the whole run, so the passes end even where
// analysis undoes a function.
//
// Headless usage: -postScript PaddedFunctions.java, before ExportFunctions.java
// @category Decomp

import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.data.PointerDataType;
import ghidra.program.model.data.Undefined;
import ghidra.program.model.lang.OperandType;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.FlowType;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

public class PaddedFunctions extends GhidraScript {

	private static final byte INT3 = (byte) 0xCC;
	private static final int TABLE_RUN = 3;
	private static final byte[] JMP_THROUGH_SLOT = { (byte) 0xFF, 0x25 };
	// The fill before a jump table: npad 1, 2 and 3 of VC++'s listing.inc.
	private static final byte[][] TABLE_FILL = { { (byte) 0x90 }, { (byte) 0x8B, (byte) 0xFF }, { (byte) 0x8D, 0x49, 0x00 } };
	private static final int STUB_SIZE = 6;
	private final Set<Address> tried = new HashSet<>();

	@Override
	protected void run() throws Exception {
		int created = createAtInitializers();
		analyzeChanges(currentProgram);
		int repaired = 0;
		int removed = 0;
		int passCreated;
		int passRepaired;
		do {
			repairLoopStarts();
			removed += removeScopeTableCode();
			passCreated = createAtImportStubs() + createAtBoundaries() + createAtJumpTargets() + createAtStoredAddresses();
			analyzeChanges(currentProgram);
			passRepaired = repairBodies();
			analyzeChanges(currentProgram);
			if (passCreated == 0 && passRepaired == 0) {
				passCreated = createAtTableEntries();
				analyzeChanges(currentProgram);
			}
			created += passCreated;
			repaired += passRepaired;
			println("Pass: created " + passCreated + ", gave " + passRepaired + " functions their code back");
		}
		while (passCreated > 0 || passRepaired > 0);
		println("Created " + created + " functions at the runtime's initializers, import stubs, after int3 padding, a return or a jump table, where a jump or tail call goes,"
			+ " or where a pushed address or a table of entry points goes; gave " + repaired + " functions their code back;"
			+ " removed " + removed + " functions in SEH filters and handlers");
	}

	/**
	 * Removes each function that starts in a filter or handler that an SEH scope table names,
	 * up to the first instruction that doesn't fall through, and keeps any rule from starting
	 * one there again. Returns how many functions went.
	 */
	private int removeScopeTableCode() throws Exception {
		List<Address> starts = new ArrayList<>();
		for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
			for (Instruction instruction : instructions(function)) {
				if (instruction.getMnemonicString().equals("PUSH") && OperandType.isScalar(instruction.getOperandType(0))) {
					starts.addAll(scopeTableCode(instruction.getScalar(0).getUnsignedValue()));
				}
			}
		}
		int count = 0;
		for (Address start : starts) {
			disassemble(start);
			for (Instruction instruction = getInstructionAt(start); instruction != null;
				instruction = instruction.getFlowType().hasFallthrough() ? getInstructionAt(instruction.getFallThrough()) : null) {
				tried.add(instruction.getAddress());
				Function function = getFunctionAt(instruction.getAddress());
				if (function != null) {
					removeFunction(function);
					count++;
				}
			}
		}
		return count;
	}

	/** The filters and handlers that the SEH scope table at offset names. None if no table is there. */
	private List<Address> scopeTableCode(long offset) throws Exception {
		MemoryBlock block = getMemoryBlock(toAddr(offset));
		if (block == null || block.isExecute() || block.isWrite() || !block.isInitialized() || !block.contains(toAddr(offset + 27))
			|| getInt(toAddr(offset)) >= 0 || getInt(toAddr(offset + 8)) >= 0) {
			return List.of();
		}
		List<Address> code = new ArrayList<>();
		for (int index = 0; block.contains(toAddr(offset + 16 + 12 * index + 11)); index++) {
			Address entry = toAddr(offset + 16 + 12 * index);
			int level = getInt(entry);
			long filter = getInt(entry.add(4)) & 0xFFFFFFFFL;
			long handler = getInt(entry.add(8)) & 0xFFFFFFFFL;
			// The enclosing level is -2 for none, or the index of an earlier entry.
			if (level != -2 && (level < 0 || level >= index) || filter != 0 && !isCodeAddress(filter) || !isCodeAddress(handler)) {
				break;
			}
			if (filter != 0) {
				code.add(toAddr(filter));
			}
			code.add(toAddr(handler));
		}
		return code;
	}

	/**
	 * Creates a function at each entry of the runtime's tables of initializers and terminators.
	 * Throws if Ghidra can't start a function at an entry.
	 */
	private int createAtInitializers() throws Exception {
		SortedSet<Long> bounds = new TreeSet<>();
		for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
			for (Instruction instruction : instructions(function)) {
				for (int operand = 0; operand < instruction.getNumOperands(); operand++) {
					Scalar value = OperandType.isScalar(instruction.getOperandType(operand)) ? instruction.getScalar(operand) : null;
					if (value != null && holdsReadOnlyZero(value.getUnsignedValue())) {
						bounds.add(value.getUnsignedValue());
					}
				}
			}
		}
		// In address order, so the code of each new function is in place before the next start is checked.
		SortedSet<Address> targets = new TreeSet<>();
		Long first = null;
		for (long last : bounds) {
			if (first != null && (last - first) % 4 == 0 && getMemoryBlock(toAddr(first)).contains(toAddr(last))) {
				targets.addAll(initializers(first + 4, last));
			}
			first = last;
		}
		int count = 0;
		for (Address target : targets) {
			Function holder = getFunctionContaining(target);
			if (holder != null && holder.getEntryPoint().equals(target)) {
				continue;
			}
			if (createAt(target, holder) == null) {
				throw new IllegalStateException("Ghidra can't start a function at " + target + ", an entry of the runtime's initializers.");
			}
			count++;
		}
		return count;
	}

	/** Whether offset holds a zero dword in read-only data. */
	private boolean holdsReadOnlyZero(long offset) throws Exception {
		MemoryBlock block = getMemoryBlock(toAddr(offset));
		return block != null && !block.isExecute() && !block.isWrite() && block.isInitialized()
			&& block.contains(toAddr(offset + 3)) && getInt(toAddr(offset)) == 0;
	}

	/** The code addresses in the dwords from start up to end. None if any other dword isn't zero. */
	private List<Address> initializers(long start, long end) throws Exception {
		List<Address> entries = new ArrayList<>();
		for (long offset = start; offset < end; offset += 4) {
			long value = getInt(toAddr(offset)) & 0xFFFFFFFFL;
			if (isCodeAddress(value)) {
				entries.add(toAddr(value));
			}
			else if (value != 0) {
				return List.of();
			}
		}
		return entries;
	}

	/** Creates a function at each import stub that analysis didn't reach: jmp [slot], with the slot in the import table. */
	private int createAtImportStubs() throws Exception {
		Memory memory = currentProgram.getMemory();
		List<Address> stubs = new ArrayList<>();
		for (MemoryBlock block : memory.getBlocks()) {
			if (!block.isExecute() || !block.isInitialized() || block.getSize() < STUB_SIZE) {
				continue;
			}
			Address last = block.getEnd().subtract(STUB_SIZE - 1);
			Address stub = memory.findBytes(block.getStart(), last, JMP_THROUGH_SLOT, null, true, monitor);
			while (stub != null) {
				if (isImportSlot(getInt(stub.add(2)) & 0xFFFFFFFFL)) {
					stubs.add(stub);
				}
				stub = stub.equals(last) ? null : memory.findBytes(stub.next(), last, JMP_THROUGH_SLOT, null, true, monitor);
			}
		}
		// In address order, so the code of a stub is in place before the next one is checked.
		int count = 0;
		for (Address stub : stubs) {
			if (freeCode(stub) && startsAfterEnd(stub) && createAt(stub, null) != null) {
				count++;
			}
		}
		return count;
	}

	/** Whether offset is a slot of the import table: analysis gave it a reference to an imported function. */
	private boolean isImportSlot(long offset) {
		for (Reference reference : getReferencesFrom(toAddr(offset))) {
			if (reference.isExternalReference()) {
				return true;
			}
		}
		return false;
	}

	private int createAtBoundaries() throws Exception {
		int count = 0;
		for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
			if (!block.isExecute() || !block.isInitialized()) {
				continue;
			}
			long first = (block.getStart().getOffset() + 15) & ~15L;
			for (long offset = first; offset <= block.getEnd().getOffset(); offset += 16) {
				Address address = block.getStart().getNewAddress(offset);
				Function holder = getFunctionContaining(address);
				if (holder != null && (holder.getEntryPoint().equals(address) || !afterPadding(address))
					|| getByte(address) == INT3 || !startsAfterEnd(address) || isJumpTable(address) || isTableFill(address)) {
					continue;
				}
				Data data = getDataContaining(address);
				if (data != null && data.isDefined()) {
					// Analysis reads the first 4 bytes of some functions as a pointer or a
					// value. Other data here, such as a switch's table of case numbers, is no
					// function.
					boolean value = data.isPointer() || Undefined.isUndefined(data.getDataType());
					if (!value || !data.getAddress().equals(address)) {
						continue;
					}
					removeData(data);
				}
				if (!inReadTable(address) && createAt(address, holder) != null) {
					count++;
				}
			}
		}
		return count;
	}

	/** Creates a function at each target in code of the computed jumps that aren't switches, and of the tail calls. */
	private int createAtJumpTargets() throws Exception {
		List<Address> computed = new ArrayList<>();
		SortedSet<Address> direct = new TreeSet<>();
		for (Instruction jump : currentProgram.getListing().getInstructions(true)) {
			if (isComputedJump(jump) && !isSwitch(jump)) {
				for (Reference reference : jump.getReferencesFrom()) {
					if (reference.getReferenceType().isFlow() && isCodeAddress(reference.getToAddress().getOffset())) {
						computed.add(reference.getToAddress());
					}
				}
			}
			else if (jump.getFlowType().isJump() && !jump.getFlowType().isComputed()) {
				direct.add(jump.getFlows()[0]);
			}
		}
		int count = 0;
		for (Address target : computed) {
			if (getFunctionAt(target) == null && createAt(target, getFunctionContaining(target)) != null) {
				count++;
			}
		}
		for (Address target : direct) {
			if (isTailCallTarget(target) && createAt(target, getFunctionContaining(target)) != null) {
				count++;
			}
		}
		return count;
	}

	/**
	 * Whether a jump to target is a tail call: the target's holder has the code there past
	 * another function that is no catch block, after the end of other code. Or the target
	 * is the lowest code of its holder's body, below the holder's entry.
	 */
	private boolean isTailCallTarget(Address target) throws Exception {
		Function holder = getFunctionContaining(target);
		if (holder == null || holder.getEntryPoint().equals(target)) {
			return false;
		}
		// VC++ puts the code of a function in one piece, from its entry on. So the lowest
		// code of a body that lies below its entry is the start of another function that
		// the holder jumps to, such as the entry point's jump to _tmainCRTStartup. The bytes
		// before it can be a function that nothing reached, so startsAfterEnd can't tell.
		if (target.equals(holder.getBody().getMinAddress()) && target.compareTo(holder.getEntryPoint()) < 0) {
			return true;
		}
		if (!startsAfterEnd(target)) {
			return false;
		}
		for (Function before : currentProgram.getFunctionManager().getFunctions(target.previous(), false)) {
			if (before.equals(holder)) {
				return false;
			}
			if (!isCatchBlock(before)) {
				return true;
			}
		}
		return true;
	}

	/** Turns each thunk that starts a loop back into one function with all its code. */
	private void repairLoopStarts() throws Exception {
		List<Function> thunks = new ArrayList<>();
		for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
			if (function.isThunk() && startsLoop(function)) {
				thunks.add(function);
			}
		}
		for (Function start : thunks) {
			Function rest = start.getThunkedFunction(false);
			Function body = getFunctionAt(getInstructionAt(start.getEntryPoint()).getMaxAddress().next());
			start.setThunkedFunction(null);
			removeFunction(rest);
			if (body != null && !body.equals(rest)) {
				removeFunction(body);
			}
			// fixupFunctionBody would find the jmp and make the function a thunk again.
			start.setBody(CreateFunctionCmd.getFunctionBody(currentProgram, start.getEntryPoint(), monitor));
		}
	}

	/**
	 * Whether the thunk's jmp goes forward to the test of a loop: code that jumps back to the
	 * code right after the jmp. Ghidra turns a jump to a function into a call, so the
	 * instruction's own name tells.
	 */
	private boolean startsLoop(Function thunk) {
		Function rest = thunk.getThunkedFunction(false);
		Instruction jump = getInstructionAt(thunk.getEntryPoint());
		if (rest == null || rest.isExternal() || jump == null || rest.getEntryPoint().compareTo(thunk.getEntryPoint()) <= 0) {
			return false;
		}
		for (Reference reference : getReferencesTo(jump.getMaxAddress().next())) {
			Instruction from = getInstructionAt(reference.getFromAddress());
			if (from != null && from.getMnemonicString().startsWith("J") && rest.getBody().contains(from.getAddress())) {
				return true;
			}
		}
		return false;
	}

	/** Whether Ghidra named the function as a catch block: Catch@ or, for catch (...), Catch_All@. */
	private static boolean isCatchBlock(Function function) {
		return function.getName().startsWith("Catch@") || function.getName().startsWith("Catch_All@");
	}

	/** Creates a function at each code address that an instruction of a function pushes or stores in memory. */
	private int createAtStoredAddresses() throws Exception {
		List<Address> targets = new ArrayList<>();
		for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
			for (Instruction instruction : instructions(function)) {
				Address target = storedAddress(instruction);
				if (target != null && startsAfterEnd(target)) {
					targets.add(target);
				}
			}
		}
		return createAtFree(targets);
	}

	/** The code address that the instruction pushes or stores in memory, or null. */
	private Address storedAddress(Instruction instruction) {
		String mnemonic = instruction.getMnemonicString();
		int operand = mnemonic.equals("PUSH") ? 0
			: mnemonic.equals("MOV") && !OperandType.isRegister(instruction.getOperandType(0)) ? 1 : -1;
		if (operand < 0 || operand >= instruction.getNumOperands()
			|| !OperandType.isScalar(instruction.getOperandType(operand))) {
			return null;
		}
		Scalar value = instruction.getScalar(operand);
		return value != null && isCodeAddress(value.getUnsignedValue()) ? toAddr(value.getUnsignedValue()) : null;
	}

	/** Creates a function at each entry of a run of code addresses in read-only data. */
	private int createAtTableEntries() throws Exception {
		List<Address> targets = new ArrayList<>();
		for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
			if (block.isExecute() || block.isWrite() || !block.isInitialized()) {
				continue;
			}
			List<Address> run = new ArrayList<>();
			for (long offset = block.getStart().getOffset(); offset + 3 <= block.getEnd().getOffset(); offset += 4) {
				long value = getInt(block.getStart().getNewAddress(offset)) & 0xFFFFFFFFL;
				if (isCodeAddress(value)) {
					run.add(toAddr(value));
					continue;
				}
				if (run.size() >= TABLE_RUN) {
					targets.addAll(run);
				}
				run.clear();
			}
			if (run.size() >= TABLE_RUN) {
				targets.addAll(run);
			}
		}
		// In address order, so the code of each new function is in place before the next start is checked.
		targets.sort(null);
		int count = 0;
		for (Address target : targets) {
			if (freeCode(target) && (startsAfterEnd(target) || target.getOffset() % 16 == 0) && createAt(target, null) != null) {
				count++;
			}
		}
		return count;
	}

	/** Creates a function at each target that no function holds yet and that holds no padding or data. */
	private int createAtFree(List<Address> targets) throws Exception {
		int count = 0;
		for (Address target : targets) {
			if (freeCode(target) && createAt(target, null) != null) {
				count++;
			}
		}
		return count;
	}

	/** Whether no function holds address, and it holds no int3, data, or the middle of an instruction. */
	private boolean freeCode(Address address) throws Exception {
		if (getFunctionContaining(address) != null || getByte(address) == INT3) {
			return false;
		}
		Instruction instruction = getInstructionContaining(address);
		Data data = getDataContaining(address);
		return (instruction == null || instruction.getAddress().equals(address)) && (data == null || !data.isDefined());
	}

	/**
	 * Creates a function at address, and takes its code out of the function that held it.
	 * Returns null if the code at address has no padding before it and runs into another
	 * function, if address had its try already, or if Ghidra can't.
	 */
	private Function createAt(Address address, Function holder) throws Exception {
		disassemble(address);
		if (!afterPadding(address) && runsIntoAnother(address, holder)) {
			return null;
		}
		if (!tried.add(address)) {
			// Each address gets one function, so the passes end even where Ghidra's analysis undoes one.
			return null;
		}
		if (holder != null) {
			// Shrink the other function to its entry, and let its body grow back up to this one.
			holder.setBody(new AddressSet(holder.getEntryPoint()));
		}
		Function function = createFunction(address, null);
		if (holder != null) {
			CreateFunctionCmd.fixupFunctionBody(currentProgram, holder, monitor);
		}
		if (function != null && instructions(function).stream().anyMatch(this::isComputedJump)) {
			analyzeChanges(currentProgram);
		}
		return function;
	}

	/**
	 * Whether the code at address runs into the body of a function other than holder. A
	 * new function would take that code from it. Only code without padding before it
	 * can be part of that function.
	 */
	private boolean runsIntoAnother(Address address, Function holder) {
		AddressSetView body = CreateFunctionCmd.getFunctionBody(currentProgram, address, false, monitor);
		Iterator<Function> others = currentProgram.getFunctionManager().getFunctionsOverlapping(body);
		while (others.hasNext()) {
			Function other = others.next();
			if (holder == null || !other.getEntryPoint().equals(holder.getEntryPoint())) {
				return true;
			}
		}
		return false;
	}

	/** Whether the code before address can't run into it. */
	private boolean startsAfterEnd(Address address) throws Exception {
		if (afterPadding(address)) {
			return true;
		}
		CodeUnit before = currentProgram.getListing().getCodeUnitContaining(address.previous());
		if (before instanceof Instruction instruction) {
			return instruction.getMaxAddress().equals(address.previous()) && !instruction.getFlowType().hasFallthrough();
		}
		return before instanceof Data data && data.isDefined() && data.getMaxAddress().equals(address.previous());
	}

	/**
	 * Whether address lies in a table that an instruction reads. Nothing tells how long such
	 * a table is, so it runs from the address that an instruction reads to the next code.
	 */
	private boolean inReadTable(Address address) throws Exception {
		for (Address at = address; ; at = at.previous()) {
			for (Reference reference : getReferencesTo(at)) {
				if (readsTable(reference)) {
					return true;
				}
			}
			if (followsCode(at)) {
				return false;
			}
		}
	}

	/**
	 * Whether the reference is an instruction that reads memory there. Analysis marks a read
	 * through a register, such as movzx ecx, byte ptr [ecx + table], only as data, like an
	 * address that an instruction pushes or moves into a register.
	 */
	private boolean readsTable(Reference reference) {
		Instruction from = getInstructionAt(reference.getFromAddress());
		int operand = reference.getOperandIndex();
		return from != null && (reference.getReferenceType().isRead()
			|| operand >= 0 && OperandType.isDynamic(from.getOperandType(operand)));
	}

	/** Whether address follows an instruction, int3 or a pointer, or starts its block. */
	private boolean followsCode(Address address) throws Exception {
		if (afterPadding(address)) {
			return true;
		}
		CodeUnit before = currentProgram.getListing().getCodeUnitContaining(address.previous());
		return before instanceof Instruction || before instanceof Data data && data.isPointer();
	}

	/** Whether address is a 16-byte boundary after int3 padding, or at the start of its block. */
	private boolean paddedStart(Address address) throws Exception {
		return address.getOffset() % 16 == 0 && afterPadding(address);
	}

	/** Whether address follows an int3 that is no part of another instruction, or starts its block. */
	private boolean afterPadding(Address address) throws Exception {
		if (!getMemoryBlock(address).contains(address.previous())) {
			return true;
		}
		CodeUnit before = currentProgram.getListing().getCodeUnitContaining(address.previous());
		if (before instanceof Instruction instruction) {
			return instruction.getMnemonicString().equals("INT3");
		}
		return !(before instanceof Data data && data.isDefined()) && getByte(address.previous()) == INT3;
	}

	/**
	 * Whether address holds an entry of a jump table: a code address next to another one.
	 * One alone can be an instruction, such as call (E8 xx xx 00). The entry before counts
	 * too, because the last entry of a table can sit at a boundary.
	 */
	private boolean isJumpTable(Address address) throws Exception {
		return holdsCodeAddress(address) && (holdsCodeAddress(address.add(4)) || holdsCodeAddress(address.subtract(4)));
	}

	/** Whether address holds the fill that VC++ puts before a jump table, then the table. */
	private boolean isTableFill(Address address) throws Exception {
		for (byte[] fill : TABLE_FILL) {
			if (Arrays.equals(getBytes(address, fill.length), fill) && isJumpTable(address.add(fill.length))) {
				return true;
			}
		}
		return false;
	}

	private boolean holdsCodeAddress(Address address) throws Exception {
		return getMemoryBlock(address) != null && isCodeAddress(getInt(address) & 0xFFFFFFFFL);
	}

	private boolean isCodeAddress(long offset) {
		MemoryBlock block = getMemoryBlock(toAddr(offset));
		return block != null && block.isExecute();
	}

	private boolean isComputedJump(Instruction instruction) {
		FlowType flow = instruction.getFlowType();
		return flow.isJump() && flow.isComputed();
	}

	/** Whether the jump reads its target from a table in code, as a switch does: jmp [eax*4 + table]. */
	private boolean isSwitch(Instruction jump) {
		return switchTable(jump) != null;
	}

	/** The table in code that the jump reads its target from, or null. */
	private Address switchTable(Instruction jump) {
		for (Object operand : jump.getOpObjects(0)) {
			long value = operand instanceof Scalar scalar ? scalar.getUnsignedValue()
				: operand instanceof Address address ? address.getOffset() : 0;
			if (isCodeAddress(value)) {
				return toAddr(value);
			}
		}
		return null;
	}

	private List<Instruction> instructions(Function function) {
		List<Instruction> instructions = new ArrayList<>();
		currentProgram.getListing().getInstructions(function.getBody(), true).forEach(instructions::add);
		return instructions;
	}

	/**
	 * Gives each function back the code its flows reach outside its body: code that no
	 * function holds, or a later function that is the owner's own code split off. First it
	 * resolves each switch of the function that analysis left without targets.
	 * Code after int3 padding stays a function of its own, as it does in createAtBoundaries.
	 * Where the code at a flow's target is missing, this clears what stops it from there
	 * to the next function and disassembles again from the target.
	 * Returns how many functions grew.
	 */
	private int repairBodies() throws Exception {
		List<Function> owners = new ArrayList<>();
		currentProgram.getFunctionManager().getFunctions(true).forEach(owners::add);
		int count = 0;
		for (Function owner : owners) {
			if (owner.isDeleted()) {
				continue;
			}
			long size = owner.getBody().getNumAddresses();
			boolean outside = false;
			for (Instruction instruction : instructions(owner)) {
				Address table = isComputedJump(instruction) ? switchTable(instruction) : null;
				if (table != null && flowTargets(instruction).isEmpty()) {
					resolveSwitch(instruction, table, owner);
				}
				for (Address target : flowTargets(instruction)) {
					if (owner.getBody().contains(target) || !isCodeAddress(target.getOffset()) || paddedStart(target)) {
						continue;
					}
					Function holder = getFunctionContaining(target);
					if (holder != null && holder.getEntryPoint().compareTo(owner.getEntryPoint()) > 0 && splitOff(holder, owner)) {
						removeFunction(holder);
						holder = null;
					}
					if (holder == null && getInstructionAt(target) == null) {
						clearStrayCode(target);
						disassemble(target);
					}
					outside |= holder == null;
				}
			}
			if (outside) {
				CreateFunctionCmd.fixupFunctionBody(currentProgram, owner, monitor);
				if (owner.getBody().getNumAddresses() > size) {
					count++;
				}
			}
		}
		return count;
	}

	/**
	 * Whether the function is code of an earlier owner that analysis split off: it goes on
	 * right where the owner's code stops, and only the owner's jumps and switch tables in
	 * code reach it. No call, no jump of another function, no pointer in data.
	 * Ghidra turns a jump to a function into a call, so the instruction's own name tells.
	 */
	private boolean splitOff(Function function, Function owner) throws Exception {
		Address entry = function.getEntryPoint();
		if (!owner.getBody().contains(entry.previous())) {
			return false;
		}
		for (Reference reference : getReferencesTo(entry)) {
			Address from = reference.getFromAddress();
			Instruction instruction = getInstructionAt(from);
			boolean ownJump = instruction != null
				? instruction.getMnemonicString().startsWith("J") && (!isComputedJump(instruction) || isSwitch(instruction))
					&& owner.getBody().contains(from)
				: isCodeAddress(from.getOffset());
			if (!ownJump) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Resolves a switch that Ghidra left alone because it has no bounds check. Each entry
	 * of its table that points between the function's entry and the table is a case. Like
	 * Ghidra does for the switches it resolves, this marks the entries as pointers and adds
	 * a flow from the jump to each case.
	 */
	private void resolveSwitch(Instruction jump, Address table, Function owner) throws Exception {
		for (Address entry = table; ; entry = entry.add(4)) {
			long target = getInt(entry) & 0xFFFFFFFFL;
			if (target < owner.getEntryPoint().getOffset() || target >= table.getOffset()) {
				return;
			}
			createData(entry, PointerDataType.dataType);
			jump.addOperandReference(0, toAddr(target), RefType.COMPUTED_JUMP, SourceType.ANALYSIS);
		}
	}

	/** Where the instruction sends control, other than into a call. */
	private List<Address> flowTargets(Instruction instruction) {
		List<Address> targets = new ArrayList<>();
		if (instruction.getFallThrough() != null) {
			targets.add(instruction.getFallThrough());
		}
		if (instruction.getFlowType().isJump()) {
			for (Reference reference : instruction.getReferencesFrom()) {
				if (reference.getReferenceType().isFlow()) {
					targets.add(reference.getToAddress());
				}
			}
		}
		return targets;
	}

	/**
	 * Clears what stops code from address up to the next function: instructions that no
	 * function holds, and values of unknown type. Analysis disassembles some data that
	 * looks like a code address, at the wrong offset into real code. And it marks the bytes
	 * that such stray code reads as a value. Both stop the real code where they overlap.
	 */
	private void clearStrayCode(Address address) throws Exception {
		Function next = getFunctionAfter(address);
		Address end = next != null ? next.getEntryPoint().previous() : getMemoryBlock(address).getEnd();
		List<CodeUnit> stray = new ArrayList<>();
		for (CodeUnit unit : currentProgram.getListing().getCodeUnits(new AddressSet(address, end), true)) {
			boolean orphan = unit instanceof Instruction && getFunctionContaining(unit.getAddress()) == null;
			boolean value = unit instanceof Data data && data.isDefined() && Undefined.isUndefined(data.getDataType());
			if (orphan || value) {
				stray.add(unit);
			}
		}
		for (CodeUnit unit : stray) {
			clearListing(unit.getMinAddress(), unit.getMaxAddress());
		}
	}
}
