#include "decls.h"
extern unsigned char DAT_05b92e54;
extern unsigned char DAT_05b92e55;
extern unsigned char DAT_05b92e56;
extern int DAT_05b93284;
extern int DAT_05b93288;
extern int DAT_05b9328c;
extern int DAT_05b93290;
extern int DAT_05b93294;
extern unsigned char DAT_05b92ec8[0x300];
extern int DAT_05b93248;
extern char DAT_05b9358c;
extern int DAT_05cc3628;
extern unsigned char ucInputStatusForEachPlayer[2];
extern int DAT_05b93588;
extern unsigned char ucInputStatus;
extern unsigned char DAT_05b92ec8[768];

// STUB: SADX 0x004c3340
void mouseshot()
{
}

// STUB: SADX 0x004c3770
void SaveKeyCheckData(int sw)
{
}

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
int FUN_004c39c0(...)
{
	return 0;
}

// FUNCTION: SADX 0x004c39d0
void CheckSoftResetTiming()
{
	char local_9;
	int local_8g;

	local_9 = 0;
	local_8g = DAT_05b93248;
	if (DAT_05b9358c)
	{
		if (DAT_05cc3628 == 0)
		{
			DAT_05b9358c |= 1;
		}
	}
	else
	{
		if (KeyGetPress(0x3b) && (FUN_004c38d0() & 0x44))
		{
			DAT_05b9358c |= 4;
		}
		else
		{
			DAT_05b9358c &= ~4;
		}
	}
}

// FUNCTION: SADX 0x004c4240
void input_init()
{
	int local_8;
	for (local_8 = 0; 0x100 > local_8; local_8++)
	{
		DAT_05b92ec8[local_8 * 3 + 2] = 0;
		DAT_05b92ec8[local_8 * 3 + 1] = 0;
		DAT_05b92ec8[local_8 * 3] = 0;
	}
	DAT_05b92e56 = 0;
	DAT_05b92e55 = DAT_05b92e56;
	DAT_05b92e54 = DAT_05b92e55;
	DAT_05b9328c = 0;
	DAT_05b93290 = 0;
	DAT_05b93294 = 0;
	DAT_05b93284 = 0;
	DAT_05b93288 = 0;
}
