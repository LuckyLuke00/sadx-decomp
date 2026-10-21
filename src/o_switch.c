#include "decls.h"
extern unsigned char DAT_05cd290c[1024];
void FUN_0058b160(struct task *);

// FUNCTION: SADX 0x0058b140
void FUN_0058b140(struct task *param_1)
{
	FUN_0058b160(param_1);
}

// FUNCTION: SADX 0x0058b630
void FUN_0058b630(struct task *param_1)
{
	GetSwitchOnOff(*(short *)((char *)param_1->twp + 0xe));
}

// FUNCTION: SADX 0x0058b8b0
int GetSwitchOnOff(unsigned int ID)
{
	if ((DAT_05cd290c[ID] & 1) != 0)
		return 1;
	else
		return 0;
}

// STUB: SADX 0x0058b8d0
int FUN_0058b8d0(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x0058b8f0
void ClearAllSwitches()
{
	int local_8;
	for (local_8 = 0; local_8 < 0x30; local_8 = local_8 + 1)
	{
		DAT_05cd290c[local_8] = 0;
	}
}
