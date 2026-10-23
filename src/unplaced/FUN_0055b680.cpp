#include "decls.h"
extern char score_sc[32];
extern short DAT_05b3ebb8;
extern float ScreenRaitoX;
extern float ScreenRaitoY;
void DisplayCalcTime(struct task *tp);
void FUN_0055de60(struct _SC_NUMBERS *param_1);

// FUNCTION: SADX 0x0055b680
void FUN_0055b680(struct task *param_1)
{
	DisplayCalcTime(param_1);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (int)DAT_05b3ebb8;
	*(float *)(score_sc + 0xc) = 320.0f;
	*(float *)(score_sc + 0x10) = 156.0f;
	*(float *)(score_sc + 0xc) = *(float *)(score_sc + 0xc) - 320.0 + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = *(float *)(score_sc + 0x10) - 240.0 + ScreenRaitoY * 240.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}
