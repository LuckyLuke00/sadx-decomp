#include "decls.h"
extern unsigned long DAT_05b3e308[16];
extern unsigned long DAT_05cda1b0;
extern unsigned long DAT_05cda1b4;
extern unsigned long DAT_05cda1b8;
extern unsigned long DAT_05cda1bc;
extern unsigned long DAT_05cda1c0;
extern unsigned long DAT_05cda1c4;
extern unsigned long DAT_05cda1c8;
extern struct u4s DAT_009921c0[];

// FUNCTION: SADX 0x005a4b20
void Init_objCameraEntryTable(unsigned long u32StageNo)
{
	DAT_05cda1b0 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT1];
	DAT_05cda1b4 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT2];
	DAT_05cda1b8 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT3];
	DAT_05cda1bc = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT4];
	DAT_05cda1c0 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT5];
	DAT_05cda1c4 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT6];
	DAT_05cda1c8 = DAT_05b3e308[DAT_009921c0[u32StageNo].u4_ACT7];
}
