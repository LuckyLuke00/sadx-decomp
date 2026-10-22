#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d490
void njGetTranslation(int param_1, float *param_2)
{
	if (param_1 == 0)
	{
		param_1 = DAT_0629c518;
	}
	*param_2 = *(float *)((char *)param_1 + 0x30);
	param_2[1] = *(float *)((char *)param_1 + 0x34);
	param_2[2] = *(float *)((char *)param_1 + 0x38);
}
