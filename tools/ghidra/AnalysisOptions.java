// Sets Ghidra's analysis options for an exe before it is analyzed.
//
// Headless usage: -preScript AnalysisOptions.java
// @category Decomp

import ghidra.app.script.GhidraScript;

public class AnalysisOptions extends GhidraScript {

	@Override
	protected void run() throws Exception {
		// Ghidra marks some CRT functions as non-returning by mistake, and then ends
		// every caller at its call to them. With this off, callers keep their full body.
		disable("Non-Returning Functions - Discovered");
		// Ghidra takes a run of values in data that look like code addresses for a table
		// of pointers, and disassembles code at each one. Many such values in a game's
		// data are no pointers, so this turns data bytes into code. PaddedFunctions.java
		// finds the functions that real tables reach.
		disable("Create Address Tables");
		disable("Data Reference.Create Address Tables");
		disable("Reference.Create Address Tables");
		// With this on, the default, Ghidra makes a function where a jump passes over the
		// start of another function: the rest of a function after its catch block, or a
		// switch's case block that PaddedFunctions.java gives back to its function.
		disable("Shared Return Calls.Assume Contiguous Functions Only");
	}

	private void disable(String name) {
		setAnalysisOption(currentProgram, name, "false");
		if (!"false".equals(getCurrentAnalysisOptionsAndValues(currentProgram).get(name)))
			throw new IllegalStateException("Ghidra did not turn off the analysis option " + name);
	}
}
