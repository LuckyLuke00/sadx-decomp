#include "decls.h"
extern int DAT_05b3e05c;
extern unsigned char DAT_05cd14e1;
void FUN_00554ca0(int param_1);

// FUNCTION: SADX 0x00547040
void FUN_00547040(int param_1)
{
	if ((DAT_05b3e05c == 9) && (DAT_05cd14e1 == 1))
	{
		FUN_00554ca0(param_1);
	}
}

// FUNCTION: SADX 0x00547070
void FUN_00547070(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	SonicChangeWaitingMotion(param_1, param_2, param_3);
}
