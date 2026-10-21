#include "decls.h"

// FUNCTION: SADX 0x00547070
void FUN_00547070(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	SonicChangeWaitingMotion(param_1, param_2, param_3);
}
