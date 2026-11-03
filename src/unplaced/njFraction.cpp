#include "decls.h"
#include <math.h>

// FUNCTION: SADX 0x0067d9b0
Float njFraction(Float n)
{
	double local_c;
	return (Float)modf(n, &local_c);
}
