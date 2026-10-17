// Decompiled twin of original.cpp, scored by `python tools/check.py ci`.
// Each function covers one outcome reccmp must report. expected.json holds the scores.
// gl-caller.cpp and gl-callee.cpp are in both builds.

struct Vec3 {
	float x, y, z;
};

// Exact match.
// FUNCTION: SELFTEST 0x401070
__declspec(noinline) int Clamp(int value, int low, int high)
{
	if (value < low) {
		return low;
	}
	if (value > high) {
		return high;
	}
	return value;
}

// Exact match with x87 float code.
// FUNCTION: SELFTEST 0x401090
__declspec(noinline) float Dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Near miss: ">=" where the original has ">", so one branch differs.
// FUNCTION: SELFTEST 0x4010c0
__declspec(noinline) int CountAbove(const int* values, int count, int limit)
{
	int result = 0;
	for (int i = 0; i < count; i++) {
		if (values[i] >= limit) {
			result++;
		}
	}
	return result;
}

// Not decompiled yet.
// STUB: SELFTEST 0x4010f0
__declspec(noinline) int Scramble(int value)
{
	return 0;
}

// Exact match with a float constant. The original has no relocations, so this
// needs the constants that check.py finds.
// FUNCTION: SELFTEST 0x401110
__declspec(noinline) float Scale(float value)
{
	return value * 400.0f;
}

// Exact match with two string literals, which need the constants too.
// FUNCTION: SELFTEST 0x401130
__declspec(noinline) const char* Name(int index)
{
	return index > 1 ? "selftest" : "original";
}

// Effective match: the original's code with ecx and edx swapped. The instructions are the
// same, so reccmp scores it below 100% but flags it as an effective match.
// FUNCTION: SELFTEST 0x401150
__declspec(noinline) int Combine(int a, int b)
{
	__asm {
		mov edx, a
		mov ecx, b
		add edx, ecx
		mov eax, edx
	}
}

int Total(const int* values, int count);

int main(int argc, char** argv)
{
	Vec3 v = {(float) argc, 2.0f, 3.0f};
	int values[4] = {argc, 5, 9, 2};
	return Clamp(argc, 0, 3) + (int) Dot(v, v) + CountAbove(values, 4, argc) + Scramble(argc) + (int) Scale((float) argc)
		+ Name(argc)[0] + Combine(argc, 2) + Total(values, argc);
}
