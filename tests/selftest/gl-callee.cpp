// Built with /GL into both the original and its twin: see gl-caller.cpp.

// Exact match with /GL and a register argument.
// FUNCTION: SELFTEST 0x401020
__declspec(noinline) int Mix(const int* values, int count)
{
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += values[i] * 3;
	}
	return sum;
}
