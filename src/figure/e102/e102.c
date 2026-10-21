#include "decls.h"

// FUNCTION: SADX 0x00515a70
void FUN_00515a70(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	PGetAcceleration(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00515a90
void FUN_00515a90(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	PGetAccelerationAir(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00516260
long IsE102Whistling(struct taskwk *twp)
{
	if (twp->mode == 0x3a)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00516280
long IsE102ShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x1c)
	{
		return 1;
	}
	return 0;
}
