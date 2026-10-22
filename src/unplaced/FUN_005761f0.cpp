#include "decls.h"
void FUN_00422560(int param_1);
void FUN_00576c10(struct task *param_1);
extern struct task *DAT_05cd2600;

// FUNCTION: SADX 0x005761f0
void FUN_005761f0(void)
{
	if (DAT_05cd2600)
	{
		FUN_00422560(7);
		FUN_00576c10(DAT_05cd2600);
		FUN_00422560(1);
	}
}
