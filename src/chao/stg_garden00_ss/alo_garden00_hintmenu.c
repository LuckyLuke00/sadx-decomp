#include "decls.h"
void FUN_00479000();
void ALO_XYButtonShow(int id);
void FUN_00479840(void);
void Free(void *mp);

// FUNCTION: SADX 0x00479840
void FUN_00479840(void)
{
	FUN_00479000();
	ALO_XYButtonShow(1);
}

// FUNCTION: SADX 0x00479910
void FUN_00479910(int param_1)
{
	int *var1;

	var1 = *(int **)((char *)param_1 + 0x2c);
	FUN_00479840();
	Free((void *)var1);
	*(int *)((char *)param_1 + 0x2c) = 0;
}

// FUNCTION: SADX 0x00479ac0
long AloG00HintmenuOver(struct task *tp)
{
	if ((tp->awp != 0) && (*(int *)tp->awp == 3))
	{
		return 1;
	}
	return 0;
}
