// Stand-in for a retail binary. tools/check.py builds it without a PDB and
// without relocations, as most old exes are, and scores decomp.cpp against it.
// Do not edit: reccmp-project.yml pins its SHA-256.

struct Vec3 {
	float x, y, z;
};

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

__declspec(noinline) float Dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

__declspec(noinline) int CountAbove(const int* values, int count, int limit)
{
	int result = 0;
	for (int i = 0; i < count; i++) {
		if (values[i] > limit) {
			result++;
		}
	}
	return result;
}

__declspec(noinline) int Scramble(int value)
{
	return value * 7 + 3;
}

__declspec(noinline) float Scale(float value)
{
	return value * 400.0f;
}

__declspec(noinline) const char* Name(int index)
{
	return index > 1 ? "selftest" : "original";
}

__declspec(noinline) int Combine(int a, int b)
{
	__asm {
		mov ecx, a
		mov edx, b
		add ecx, edx
		mov eax, ecx
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
