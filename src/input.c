#include "decls.h"
extern unsigned char ucInputStatusForEachPlayer[2];
extern int DAT_05b93588;
extern unsigned char ucInputStatus;
extern unsigned char DAT_05b92ec8[768];

// FUNCTION: SADX 0x004c3890
int KeyGetPress(int keycode)
{
	return DAT_05b92ec8[keycode * 3 + 2];
}

// FUNCTION: SADX 0x004c38e0
void PadReadOn()
{
	ucInputStatus = 1;
}

// FUNCTION: SADX 0x004c38f0
void PadReadOn(int counter)
{
	if (counter == 0)
	{
		ucInputStatus = 1;
	}
	else
	{
		DAT_05b93588 = counter;
	}
}

// FUNCTION: SADX 0x004c3910
void PadReadOff()
{
	ucInputStatus = 0;
}

// FUNCTION: SADX 0x004c3920
long CheckPadReadMode()
{
	return ucInputStatus;
}

// FUNCTION: SADX 0x004c3930
void PadReadOnP(unsigned char pno)
{
	if (pno != 0 && pno != 1)
	{
		ucInputStatusForEachPlayer[0] = 1;
		ucInputStatusForEachPlayer[1] = 1;
	}
	else
	{
		ucInputStatusForEachPlayer[pno] = 1;
	}
}

// FUNCTION: SADX 0x004c3970
void PadReadOffP(unsigned char pno)
{
	if (pno != 0 && pno != 1)
	{
		ucInputStatusForEachPlayer[0] = 0;
		ucInputStatusForEachPlayer[1] = 0;
	}
	else
	{
		ucInputStatusForEachPlayer[pno] = 0;
	}
}

// FUNCTION: SADX 0x004c39b0
long CheckPadReadModeP(unsigned char pno)
{
	return ucInputStatusForEachPlayer[pno];
}

// FUNCTION: SADX 0x004c39c0
int FUN_004c39c0(int param_1)
{
	return 0;
}

// STUB: SADX 0x004c39d0
void CheckSoftResetTiming()
{
}
