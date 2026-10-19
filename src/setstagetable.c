#include "decls.h"
extern unsigned char DAT_0098fcf0[3];
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
	unsigned long local_ci;
	unsigned long local_1c;
	unsigned long local_10m;
	unsigned long local_18;
	unsigned long local_14;
	unsigned long local_8g;
	local_ci = (unsigned long)(DAT_0098fcf0[u32StageNo] & 0xf);
	DAT_05cd2948 = DAT_05b3e320[local_ci];
	local_1c = (unsigned long)((DAT_0098fcf0[u32StageNo] >> 4) & 0xf);
	DAT_05cd294c = DAT_05b3e320[local_1c];
	local_10m = (unsigned long)(DAT_0098fcf0[u32StageNo + 1] & 0xf);
	DAT_05cd2950 = DAT_05b3e320[local_10m];
	local_18 = (unsigned long)((DAT_0098fcf0[u32StageNo + 1] >> 4) & 0xf);
	DAT_05cd2954 = DAT_05b3e320[local_18];
	local_14 = (unsigned long)(DAT_0098fcf0[u32StageNo + 2] & 0xf);
	DAT_05cd2958 = DAT_05b3e320[local_14];
	local_8g = (unsigned long)((DAT_0098fcf0[u32StageNo + 2] >> 4) & 0xf);
	DAT_05cd295c = DAT_05b3e320[local_8g];
}
