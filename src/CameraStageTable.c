#include "decls.h"
extern struct _OBJ_CAMERAENTRYTABLE *DAT_05b3e308[6];
extern struct _OBJ_CAMERAENTRYTABLE *DAT_05cda1b0[8];
extern struct u4s DAT_009921c0[];

// FUNCTION: SADX 0x005a4b20
void Init_objCameraEntryTable(unsigned long u32StageNo)
{
	DAT_05cda1b0[0] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT1];
	DAT_05cda1b0[1] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT2];
	DAT_05cda1b0[2] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT3];
	DAT_05cda1b0[3] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT4];
	DAT_05cda1b0[4] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT5];
	DAT_05cda1b0[5] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT6];
	DAT_05cda1b0[6] = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT7];
}
