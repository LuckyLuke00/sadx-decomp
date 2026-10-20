#include "decls.h"
extern struct u4s DAT_0098fcf0[];
extern int DAT_05b3e320[16];
extern int DAT_05cd2948;
extern int DAT_05cd294c;
extern int DAT_05cd2950;
extern int DAT_05cd2954;
extern int DAT_05cd2958;
extern int DAT_05cd295c;

// FUNCTION: SADX 0x0058b920
void Init_objEditTable(unsigned long u32StageNo)
{
	DAT_05cd2948 = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT1];
	DAT_05cd294c = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT2];
	DAT_05cd2950 = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT3];
	DAT_05cd2954 = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT4];
	DAT_05cd2958 = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT5];
	DAT_05cd295c = DAT_05b3e320[DAT_0098fcf0[u32StageNo].u4_ACT6];
}
