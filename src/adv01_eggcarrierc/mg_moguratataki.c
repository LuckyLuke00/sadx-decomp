#include "decls.h"
extern int DAT_05cccbbc;
extern int DAT_05cccbc0;
extern int DAT_05cccbc4;
extern int *DAT_060b867c;
extern int DAT_05ccdaa0;
extern int DAT_05ccdaa4;
extern int DAT_05ccdaa8;
extern int DAT_05ccdaac;
extern int DAT_05ccdab0;
extern int DAT_05ccdab4;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern int DAT_060b8680;
extern int DAT_05b3e05c;
extern int DAT_05cc3574;
extern char DAT_05cc3631;
void PadReadOnP(unsigned char pno);
void Free(void *mp);
void CreateSaveData();

// FUNCTION: SADX 0x0069fb60
void moguraExit(struct task *tp)
{
	if (tp->awp->work.ptr[0] != 0)
	{
		Free(tp->awp->work.ptr[0]);
		tp->awp->work.ptr[0] = 0;
	}
	if (DAT_060b8680 != 0)
	{
		PadReadOnP(0);
	}
	DAT_060b8680 = 0;
	if (DAT_05b3e05c == 0xa)
	{
		if (DAT_05cc3574 == 0)
		{
			DAT_05cc3631 = 1;
		}
		else
		{
			CreateSaveData();
		}
	}
}

// FUNCTION: SADX 0x0069fbc0
void *FUN_0069fbc0()
{
	void *var1;
	var1 = MAlloc(0x190);
	memset(var1, 0, 0x190);
	return var1;
}

// FUNCTION: SADX 0x0069fc90
void FUN_0069fc90(unsigned char *param_1)
{
	int var1 = *DAT_060b867c;
	*DAT_060b867c = var1 - 1;
	if (var1 <= 0)
	{
		*param_1 = 3;
		dsPlay_oneshot(0x23f, 0, 0, 0);
		DAT_05ccdaa0 = 0;
		DAT_05ccdaa4 = 0x1f4;
		DAT_05ccdaa8 = 0;
		DAT_05ccdaac = 0x64;
		DAT_05ccdab0 = 0;
		DAT_05ccdab4 = -0xc8;
	}
}

// FUNCTION: SADX 0x006a0f90
void FUN_006a0f90(void)
{
	int *var1 = DAT_060b867c;
	int var2 = var1[2];
	if (DAT_05cccbbc < var2)
	{
		DAT_05cccbc4 = DAT_05cccbc0;
		DAT_05cccbc0 = DAT_05cccbbc;
		DAT_05cccbbc = var1[2];
		return;
	}
	if (DAT_05cccbc0 < var2)
	{
		DAT_05cccbc4 = DAT_05cccbc0;
		DAT_05cccbc0 = var1[2];
		return;
	}
	if (DAT_05cccbc4 < var2)
	{
		DAT_05cccbc4 = var2;
	}
}
