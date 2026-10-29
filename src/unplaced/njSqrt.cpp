#include "decls.h"
extern "C" double sqrt(double param_1);

// FUNCTION: SADX 0x00431900
Float njSqrt(Float n)
{
	if (n < 0.0)
	{
		n = n * -1.0;
		n = sqrt(n);
		n = -n;
	}
	else
	{
		n = sqrt(n);
	}
	return n;
}
