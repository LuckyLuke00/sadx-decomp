// Writes the functions Ghidra found to a CSV: address,size,ghidra_name,section.
// The progress figures count the rows in game ranges. A function's row runs from its
// entry up to the int3 padding before the next function, or up to the zeros that pad the
// end of its section, so address + size is one past its end. So the row holds the
// function's switch tables too. VC++ puts a catch block inside the code of its function,
// so a catch block gets no row of its own.
// Imported functions and their jmp stubs are skipped: they come from import libraries.
// So are "functions" in sections that can't execute: they are data. A row stops at a
// stub, so the stubs sit between rows.
// A function that only jumps to another one of the exe's own functions stays.
//
// Headless usage: -postScript ExportFunctions.java <output.csv>
// @category Decomp

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.MemoryBlock;

public class ExportFunctions extends GhidraScript {

	private static final byte INT3 = (byte) 0xCC;

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length != 1) {
			throw new IllegalArgumentException("usage: ExportFunctions.java <output.csv>");
		}

		File output = new File(args[0]).getAbsoluteFile();
		output.getParentFile().mkdirs();
		int count = 0;
		try (PrintWriter out = new PrintWriter(output, "UTF-8")) {
			out.println("address,size,ghidra_name,section");
			List<Function> functions = new ArrayList<>();
			for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
				MemoryBlock block = getMemoryBlock(function.getEntryPoint());
				// Ghidra names catch blocks Catch@ and, for catch (...), Catch_All@.
				boolean catchBlock = function.getName().startsWith("Catch@") || function.getName().startsWith("Catch_All@");
				if (block != null && block.isExecute() && !catchBlock) {
					functions.add(function);
				}
			}
			for (int index = 0; index < functions.size(); index++) {
				Function function = functions.get(index);
				if (function.isThunk() && function.getThunkedFunction(true).isExternal()) {
					continue;
				}
				Address entry = function.getEntryPoint();
				MemoryBlock block = getMemoryBlock(entry);
				Address last = block.getEnd();
				byte pad = 0;
				if (index + 1 < functions.size() && functions.get(index + 1).getEntryPoint().compareTo(last) <= 0) {
					last = functions.get(index + 1).getEntryPoint().previous();
					pad = INT3;
				}
				// An instruction of the function can end in a pad byte too, such as jmp $-52 (EB CC).
				while (last.compareTo(entry) > 0 && (getByte(last) == INT3 || getByte(last) == pad)
					&& !function.getBody().contains(last)) {
					last = last.previous();
				}
				out.printf("0x%08x,%d,%s,%s%n",
					entry.getOffset(),
					last.subtract(entry) + 1,
					csvQuote(function.getName(true)),
					block.getName());
				count++;
			}
		}
		println("Exported " + count + " functions to " + args[0]);
	}

	private static String csvQuote(String value) {
		return "\"" + value.replace("\"", "\"\"") + "\"";
	}
}
