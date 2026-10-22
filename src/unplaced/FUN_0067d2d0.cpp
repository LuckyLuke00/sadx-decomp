#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d2d0
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4)
{
	if (param_1 == NULL)
	{
		param_1 = (float *)DAT_0629c518;
	}
	param_1[0] *= param_2;
	param_1[1] *= param_2;
	param_1[2] *= param_2;
	param_1[3] *= param_2;
	param_1[4] *= param_3;
	param_1[5] *= param_3;
	param_1[6] *= param_3;
	param_1[7] *= param_3;
	param_1[8] *= param_4;
	param_1[9] *= param_4;
	param_1[10] *= param_4;
	param_1[11] *= param_4;
}
