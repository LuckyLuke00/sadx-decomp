#include "decls.h"

// FUNCTION: SADX 0x004318d0
double njTan(Angle n)
{
	double var1;
	var1 = (double)njSin(n) / (double)njCos(n);
	return (double)(float)var1;
}
