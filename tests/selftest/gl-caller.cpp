// Built with /GL into both the original and its twin, like gl-callee.cpp.
// Whole-program optimization passes Mix its arguments in registers, though
// Mix is in another file: the case that docs/PORTING.md says proves /GL.

int Mix(const int* values, int count);

// Exact match with /GL.
// FUNCTION: SELFTEST 0x401000
__declspec(noinline) int Total(const int* values, int count)
{
	return Mix(values, count) + 1;
}
