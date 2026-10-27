#include "decls.h"
extern "C" double sqrt(double param_1);

// FUNCTION: SADX 0x00431900
float njSqrt(float param_1)
{
	if (param_1 < 0.0)
	{
		param_1 = param_1 * -1.0;
		param_1 = sqrt(param_1);
		param_1 = -param_1;
	}
	else
	{
		param_1 = sqrt(param_1);
	}
	return param_1;
}
