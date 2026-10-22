#include "decls.h"

// FUNCTION: SADX 0x004318d0
double njTan(int param_1)
{
	double var1;
	var1 = (double)njSin(param_1) / (double)njCos(param_1);
	return (double)(float)var1;
}
