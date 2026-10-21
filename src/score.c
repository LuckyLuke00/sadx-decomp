#include "decls.h"
extern unsigned char DAT_05b3ea15;
extern unsigned char DAT_05b3ea17;
extern unsigned char DAT_05b3ea27;
extern int DAT_05b3ebd8;
extern char DAT_05b3ea24;
extern char DAT_05b3ebba;
void FUN_00554d30(void);
void FUN_00554ce0(long param_1);
extern int DAT_05b3e05c;
extern unsigned char DAT_05cccc6a[];
extern unsigned char DAT_05b3ea14;
extern unsigned long DAT_05b3ec08;
extern int DAT_05ccdab8;
extern int DAT_05ccda98;
extern long DAT_05ccca10;
extern short DAT_05b3ebb8;
extern int DAT_05b3ec18;
extern int DAT_05b3ebd4;
extern unsigned long DAT_05b3ec04;
void FUN_00554a50(void);
void FUN_00554c80(void);
extern unsigned long DAT_05b3ea20;
void FUN_00554a10();

// FUNCTION: SADX 0x00554a00
void InitScore()
{
	FUN_00554a70();
	FUN_00554a10();
}

// FUNCTION: SADX 0x00554a10
void FUN_00554a10()
{
	DAT_05b3ea20 = 0;
}

// FUNCTION: SADX 0x00554a20
void FUN_00554a20()
{
	FUN_00554a50();
	FUN_00554c80();
	InitActionScore();
}

// FUNCTION: SADX 0x00554a40
void InitActionScore()
{
	DAT_05b3ec04 = 0;
}

// FUNCTION: SADX 0x00554a50
void FUN_00554a50(void)
{
	DAT_05b3ec18 = 0;
	DAT_05b3ebd4 = 0;
}

// FUNCTION: SADX 0x00554a70
void FUN_00554a70()
{
	DAT_05b3ebb8 = 0;
}

// FUNCTION: SADX 0x00554a80
long FUN_00554a80()
{
	return DAT_05ccca10;
}

// STUB: SADX 0x00554a90
void SetTotalRing(unsigned long num)
{
}

// FUNCTION: SADX 0x00554ab0
void ResetNumPlayer()
{
	DAT_05b3ea14 = 4;
}

// FUNCTION: SADX 0x00554ac0
void SetDefaultNumPlayer(void)
{
	int local_8;
	if (DAT_05b3e05c == 9)
	{
		local_8 = GetPlayerNumber();
		if (local_8 > 4)
			local_8 -= 1;
		if (local_8 > 1)
			local_8 -= 1;
		DAT_05b3ea14 = DAT_05cccc6a[local_8];
	}
}

// STUB: SADX 0x00554b10
void AddNumPlayer(short ssNumber)
{
}

// STUB: SADX 0x00554b80
void MomentaryDisplayPlayerNumber(struct task *tp)
{
}

// STUB: SADX 0x00554bc0
void AddNumRing(short ssNumber)
{
}

// STUB: SADX 0x00554c40
void MomentaryDisplayRingNumber(struct task *tp)
{
}

// FUNCTION: SADX 0x00554c80
void FUN_00554c80(void)
{
	DAT_05ccdab8 = 0;
	DAT_05ccda98 = 0;
}

// FUNCTION: SADX 0x00554ca0
void FUN_00554ca0(int param_1)
{
	DAT_05b3ec18 = DAT_05b3ec18 + param_1;
}

// FUNCTION: SADX 0x00554cc0
void AddEnemyScore(long add)
{
	FUN_00554ce0(add);
	DAT_05b3ebd4 = DAT_05b3ebd4 + add;
}

// FUNCTION: SADX 0x00554ce0
void FUN_00554ce0(long param_1)
{
	if (DAT_05ccdab8 > 0)
	{
		param_1 += DAT_05ccda98;
		if (param_1 > 0x1f4)
		{
			param_1 = 0x1f4;
		}
		DAT_05ccda98 = param_1;
	}
	else
	{
		DAT_05ccda98 = 0;
	}
	FUN_00554d30();
}

// FUNCTION: SADX 0x00554d30
void FUN_00554d30(void)
{
	DAT_05ccdab8 = 0x78;
}

// FUNCTION: SADX 0x00554d40
short GetNumRing()
{
	return DAT_05b3ebb8;
}

// FUNCTION: SADX 0x00554d50
void DisplayScore()
{
	if (DAT_05b3ea16 < 0)
		return;
	if (MirenScoreCheckDisplayCartTime() != 0)
		return;
	if (GetPlayerNumber() == 7)
		return;
	DisplayScoreAction();
	if (GM_CheckMode() == 1)
	{
		DAT_05b3ea24 = -1;
		DAT_05b3ebba = -1;
	}
	else
	{
		DAT_05b3ebba = DAT_05b3ea16;
		DAT_05b3ea24 = DAT_05b3ebba;
	}
}

// FUNCTION: SADX 0x00555490
short GetNumPlayer()
{
	return (short)(char)DAT_05b3ea14;
}

// FUNCTION: SADX 0x005554a0
void InitTime()
{
	DAT_05b3ec08 = 0;
	InitTimer();
}

// FUNCTION: SADX 0x005554c0
void InitTimer(void)
{
	DAT_05b3ea15 = 0;
	DAT_05b3ea27 = 0;
	DAT_05b3ea17 = 0;
	if (GetPlayerNumber() == 6)
	{
		DAT_05b3ea17 = 3;
		DAT_05b3ea27 = 0;
	}
	DAT_05b3ebd8 = 0;
}

// FUNCTION: SADX 0x00555500
void WakeTimer()
{
	bWake = 1;
}

// FUNCTION: SADX 0x00555510
void SleepTimer()
{
	bWake = 0;
}

// FUNCTION: SADX 0x00555520
void AdvanceGlobalTime()
{
	DAT_05b3ec08 = DAT_05b3ec08 + DAT_05b9d834;
}

// FUNCTION: SADX 0x005556f0
unsigned long GetGlobalTime()
{
	return DAT_05b3ec08;
}

// FUNCTION: SADX 0x00556070
void GetTime(unsigned char *minutes, unsigned char *second)
{
	*second = DAT_05b3ea27;
	*minutes = DAT_05b3ea17;
}

// FUNCTION: SADX 0x00556090
void SetTime(unsigned char minutes, unsigned char second)
{
	DAT_05b3ea27 = second;
	DAT_05b3ea17 = minutes;
	DAT_05b3ea15 = 0;
}

// FUNCTION: SADX 0x005560b0
void SetTimeFrame(unsigned char minutes, unsigned char second, unsigned char frame)
{
	DAT_05b3ea27 = second;
	DAT_05b3ea17 = minutes;
	DAT_05b3ea15 = frame;
}

// FUNCTION: SADX 0x005560d0
void GetTimeFrame(unsigned char *minutes, unsigned char *second, unsigned char *frames)
{
	*second = DAT_05b3ea27;
	*minutes = DAT_05b3ea17;
	*frames = DAT_05b3ea15;
}

// FUNCTION: SADX 0x00556100
void AddTime(int sec)
{
	sec = (char)DAT_05b3ea27 + sec;
	while (sec >= 0x3c)
	{
		sec -= 0x3c;
		DAT_05b3ea17++;
		if ((char)DAT_05b3ea17 >= 0x64)
		{
			DAT_05b3ea17 = 0x63;
			sec = 0x3b;
		}
	}
	DAT_05b3ea27 = (char)sec;
}

// FUNCTION: SADX 0x005561a0
void CalcTotalScore(struct task *tp)
{
	late_DisplayTotalScore(tp);
}

// FUNCTION: SADX 0x0055af20
double FUN_0055af20()
{
	return (double)DAT_05b3ebd4;
}

// FUNCTION: SADX 0x0055afd0
float FUN_0055afd0(void)
{
	int local_8g;
	float local_cg;
	local_8g = DAT_05b3ebb8;
	local_cg = local_8g * 10.0;
	return local_cg;
}

// STUB: SADX 0x0055b450
void DisplayCalcTime(struct task *tp)
{
}

// STUB: SADX 0x0055c7f0
int FUN_0055c7f0(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0055e200
void InitBossTrialScore(void)
{
}
