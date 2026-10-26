#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067daf0
void njSubMatrix(float *param_1, float *param_2)
{
	if (param_1 == NULL)
	{
		param_1 = (float *)DAT_0629c518;
	}
	param_1[0] -= param_2[0];
	param_1[1] -= param_2[1];
	param_1[2] -= param_2[2];
	param_1[3] -= param_2[3];
	param_1[4] -= param_2[4];
	param_1[5] -= param_2[5];
	param_1[6] -= param_2[6];
	param_1[7] -= param_2[7];
	param_1[8] -= param_2[8];
	param_1[9] -= param_2[9];
	param_1[10] -= param_2[10];
	param_1[11] -= param_2[11];
	param_1[12] -= param_2[12];
	param_1[13] -= param_2[13];
	param_1[14] -= param_2[14];
	param_1[15] -= param_2[15];
}
