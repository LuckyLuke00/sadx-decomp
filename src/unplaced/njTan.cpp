#include "decls.h"

// FUNCTION: SADX 0x004318d0
double njTan(Angle n)
{
	double var1;
	var1 = UNKNOWN_DOUBLE_MACRO(njSin(n)) / njCos(n);
	return (float)var1;
}
