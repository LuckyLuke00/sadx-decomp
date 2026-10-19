// Writes Ghidra's C for each function to <outdir>/<address>.c, for `check.py dossier --c`.
// It skips the files that exist, so a run that stopped goes on where it was.
// With an address list it writes only those functions.
//
// Headless usage: -postScript DumpDecomp.java <outdir> [<address list file, one hex address per line>]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.decompiler.parallel.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.util.task.TaskMonitor;
import java.io.File;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class DumpDecomp extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		File outDir = new File(args[0]);
		outDir.mkdirs();
		List<Function> todo = new ArrayList<>();
		FunctionManager fm = currentProgram.getFunctionManager();
		AddressSpace space = currentProgram.getAddressFactory().getDefaultAddressSpace();
		int missing = 0;
		if (args.length < 2) {
			for (Function f : fm.getFunctions(true)) {
				if (f.isExternal()) continue;
				if (new File(outDir, String.format("%08x", f.getEntryPoint().getOffset()) + ".c").exists()) continue;
				todo.add(f);
			}
		} else {
			for (String line : Files.readAllLines(Paths.get(args[1]))) {
				line = line.trim();
				if (line.isEmpty()) continue;
				if (new File(outDir, line + ".c").exists()) continue;
				Function f = fm.getFunctionAt(space.getAddress(Long.parseLong(line, 16)));
				if (f == null) { missing++; continue; }
				todo.add(f);
			}
		}
		println("To decompile: " + todo.size() + ", no function at " + missing + " addresses");
		AtomicInteger done = new AtomicInteger();
		AtomicInteger failed = new AtomicInteger();
		DecompileConfigurer configurer = ifc -> {
			DecompileOptions options = new DecompileOptions();
			options.grabFromProgram(currentProgram);
			ifc.setOptions(options);
			ifc.toggleCCode(true);
			ifc.toggleSyntaxTree(false);
			ifc.setSimplificationStyle("decompile");
		};
		DecompilerCallback<Void> callback = new DecompilerCallback<Void>(currentProgram, configurer) {
			@Override
			public Void process(DecompileResults results, TaskMonitor m) throws Exception {
				Function f = results.getFunction();
				String name = String.format("%08x", f.getEntryPoint().getOffset());
				String text;
				if (results.decompileCompleted() && results.getDecompiledFunction() != null) {
					text = results.getDecompiledFunction().getC();
				} else {
					text = "// Ghidra could not decompile this function: " + results.getErrorMessage() + "\n";
					failed.incrementAndGet();
				}
				Files.write(new File(outDir, name + ".c").toPath(), text.getBytes("UTF-8"));
				int n = done.incrementAndGet();
				if (n % 1000 == 0) println("Decompiled " + n);
				return null;
			}
		};
		callback.setTimeout(120);
		ParallelDecompiler.decompileFunctions(callback, todo, monitor);
		callback.dispose();
		println("Dumped " + done.get() + " functions, " + failed.get() + " failed");
	}
}
