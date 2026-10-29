#include "decls.h"
extern struct u4s DAT_0098fcf0[];
extern int DAT_05b3e320[16];
extern int DAT_05cd2948[8];

// FUNCTION: SADX 0x0058b920
void Init_objEditTable(unsigned long u32StageNo)
{
	DAT_05cd2948[0] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT1];
	DAT_05cd2948[1] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT2];
	DAT_05cd2948[2] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT3];
	DAT_05cd2948[3] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT4];
	DAT_05cd2948[4] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT5];
	DAT_05cd2948[5] = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT6];
}
