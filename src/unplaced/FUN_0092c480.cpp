#include "decls.h"
#include <string>
extern "C" double pow(double param_1, double param_2);

// STUB: SADX 0x0092c480
int __fastcall FUN_0092c480(int param_1, int param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x0092c9e0
float FUN_0092c9e0(float param_1)
{
	float var1 = param_1 / 20.0;
	float var2 = pow(10.0, (double)var1);
	return var2;
}

// STUB: SADX 0x0092ca10
double FUN_0092ca10(double param_1)
{
	return (double)0;
}

// STUB: SADX 0x0092cd20
std::string FUN_0092cd20(const std::string& param_1)
{
	return std::string();
}
