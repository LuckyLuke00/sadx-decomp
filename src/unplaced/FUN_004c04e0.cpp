#include "decls.h"

extern float DAT_025d5968;
extern float DAT_025d596c;
extern float DAT_025d5970;
extern float DAT_025d5974;

// FUNCTION: SADX 0x004c04e0
void FUN_004c04e0(float *param_1)
{
	___njSetTexture(&texlist_ava_title);
	ghSetPvrTexMaterial(-1);
	((void (*)(int, float, float, float, float, float))ghDrawPvrTexture)(0x4000006, (float)(param_1[3] * 10.0 + param_1[0]) * ScreenRaitoX, (float)(param_1[4] * 10.0 + param_1[1]) * ScreenRaitoY, param_1[2] - -0.30000001192092896, ScreenRaitoX * 0.9922500252723694 * param_1[3], ScreenRaitoY * 0.7422500252723694 * param_1[4]);
}

// FUNCTION: SADX 0x004c05b0
void FUN_004c05b0(float *param_1)
{
	___njSetTexture(&texlist_ava_title);
	ghSetPvrTexMaterial(-1);
	((void (*)(int, float, float, float, float, float))ghDrawPvrTexture)(0x4000006, (float)(DAT_025d5968 * param_1[3] + param_1[0]) * ScreenRaitoX, (float)(DAT_025d596c * param_1[4] + param_1[1]) * ScreenRaitoY, param_1[2] - -0.30000001192092896, DAT_025d5970 * ScreenRaitoX * param_1[3], DAT_025d5974 * ScreenRaitoY * param_1[4]);
}
