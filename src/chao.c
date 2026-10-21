#include "decls.h"
#include <string.h>
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_0049e8b0(struct task *param_1);
extern unsigned char DAT_05cbeff9;
extern int DAT_05cbf194;
extern unsigned char DAT_05cbeffb;

// STUB: SADX 0x004ff1f0
void ClearExtraDisplay()
{
}

// FUNCTION: SADX 0x004ff280
void FUN_004ff280(void)
{
	DAT_05cbeff9 = 0xff;
	DAT_05cbf194 = 0;
}

// STUB: SADX 0x004ff2a0
void FUN_004ff2a0()
{
}

// FUNCTION: SADX 0x004ff3e0
void ExtraDisplay(struct task *tp)
{
	unsigned short local_8;
	local_8 = (unsigned short)((((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744) >> 8 & 0xff);
	if (local_8 == 0x27 || local_8 == 0x28 || local_8 == 0x29)
	{
		tp->exec = FUN_0049e8b0;
	}
	else
	{
		tp->exec = ExtraDisplayExecutor;
	}
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
}

// FUNCTION: SADX 0x004ff8b0
void ExtraDisplayInit()
{
	CreateElementalTask(2, 2, ExtraDisplay);
}

// FUNCTION: SADX 0x004ff910
long GetNumOfExtra()
{
	return DAT_05cbeffb;
}
