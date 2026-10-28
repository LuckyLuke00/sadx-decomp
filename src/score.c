#include "decls.h"
extern long bWake;
void FUN_0055de60(struct _SC_NUMBERS *param_1);
extern signed char DAT_05b3ea16;
long GetPlayerNumber();
void FUN_0055de60(struct _SC_NUMBERS *);
void DisplayCalcEnemyScore(struct task *tp);
extern int DAT_05b3ea78[15];
void DisplayCalcLettersSC(struct task *tp);
extern float ScreenRaitoX;
extern float ScreenRaitoY;
void DisplayCalcRingScoreSB(struct task *tp);
void DisplayCalcBoardScoreSB(struct task *tp);
int FUN_0055c7f0(int param_1, int param_2);
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
extern char score_sc[32];

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

// STUB: SADX 0x005551a0
void DisplaySNumbers(struct NJS_SPRITE *spp, long number, unsigned char fig)
{
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

// STUB: SADX 0x00555540
void AdvanceTime()
{
}

// FUNCTION: SADX 0x005556f0
unsigned long GetGlobalTime()
{
	return DAT_05b3ec08;
}

// STUB: SADX 0x00555700
void DisplayTimer()
{
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

// FUNCTION: SADX 0x00556160
int CheckTimeOver(void)
{
	int local_8;
	if (((char)DAT_05b3ea15 == 0) && ((char)DAT_05b3ea27 == 0) && ((char)DAT_05b3ea17 == 0))
	{
		local_8 = 1;
	}
	else
	{
		local_8 = 0;
	}
	return local_8;
}

// FUNCTION: SADX 0x005561a0
void CalcTotalScore(struct task *tp)
{
	late_DisplayTotalScore(tp);
}

#pragma optimize("", off)
// STUB: SADX 0x005561c0
void late_DisplayTotalScore(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00559b60
int FUN_00559b60(int param_1, int param_2, int param_3)
{
	return (int)0;
}

// STUB: SADX 0x00559c40
void DisplayCalcLettersHH(struct task *tp)
{
}

// STUB: SADX 0x00559fa0
void DisplayCalcSonicScoreHH(struct task *tp)
{
}

// STUB: SADX 0x0055a030
void DisplayCalcSuperSonicScoreHH(struct task *tp)
{
}

// STUB: SADX 0x0055a0c0
void DisplayCalcEggManScoreHH(struct task *tp)
{
}

// FUNCTION: SADX 0x0055a160
void FUN_0055a160(struct task *param_1)
{
	DisplayCalcEggManScoreHH(param_1);
	*(int *)(score_sc + 4) = 0xf4240;
	{
		*(int *)(score_sc + 8) = (unsigned int)param_1->twp->timer.f;
	}
	*(float *)(score_sc + 0xc) = 0.0f + ScreenRaitoX * 320.0f;
	*(float *)(score_sc + 0x10) = ScreenRaitoY * 240.0f + 96.0f;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// FUNCTION: SADX 0x0055af20
double FUN_0055af20()
{
	return (double)DAT_05b3ebd4;
}

// STUB: SADX 0x0055af30
float FUN_0055af30()
{
	return (float)0;
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

// STUB: SADX 0x0055b000
int FUN_0055b000(int param_1, char param_2)
{
	return (int)0;
}

#pragma optimize("", off)
// STUB: SADX 0x0055b0b0
void DisplayCalcLetters(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0055b450
void DisplayCalcTime(struct task *tp)
{
	DisplayCalcLetters(tp);
	DrawSNumbersTime(ScreenRaitoX * 320.0 + -32.0, ScreenRaitoY * 240.0 + -144.0);
}

#pragma optimize("", off)
// STUB: SADX 0x0055b4b0
void DrawSNumbersTime(float h, float v)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0055b680
void FUN_0055b680(struct task *param_1)
{
	DisplayCalcTime(param_1);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (int)DAT_05b3ebb8;
	*(float *)(score_sc + 0xc) = 320.0f;
	*(float *)(score_sc + 0x10) = 156.0f;
	*(float *)(score_sc + 0xc) = *(float *)(score_sc + 0xc) - 320.0 + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = *(float *)(score_sc + 0x10) - 240.0 + ScreenRaitoY * 240.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// FUNCTION: SADX 0x0055b710
void DisplayCalcEnemyScore(struct task *tp)
{
	FUN_0055b680(tp);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (unsigned int)tp->twp->scl.x;
	*(float *)(score_sc + 0xc) = 320.0f;
	*(float *)(score_sc + 0x10) = 228.0f;
	*(float *)(score_sc + 0xc) = *(float *)(score_sc + 0xc) - 320.0 + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = *(float *)(score_sc + 0x10) - 240.0 + ScreenRaitoY * 240.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// STUB: SADX 0x0055b7c0
void DisplayCalcTimeScore(struct task *tp)
{
}

// FUNCTION: SADX 0x0055b870
void DisplayCalcRingScore(struct task *tp)
{
	if (GetPlayerNumber() == 7)
		DisplayCalcTimeScore(tp);
	else
		DisplayCalcTimeScore(tp);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (unsigned int)*(float *)((char *)tp->twp + 0x34);
	*(float *)(score_sc + 0xc) = 320.0f;
	*(float *)(score_sc + 0x10) = 320.0f;
	*(float *)(score_sc + 0xc) = *(float *)(score_sc + 0xc) - 320.0 + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = *(float *)(score_sc + 0x10) - 240.0 + ScreenRaitoY * 240.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// FUNCTION: SADX 0x0055b940
void FUN_0055b940(struct task *param_1)
{
	DisplayCalcRingScore(param_1);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (unsigned int)param_1->twp->timer.f;
	*(float *)(score_sc + 0xc) = 320.0f;
	*(float *)(score_sc + 0x10) = 384.0f;
	*(float *)(score_sc + 0xc) = *(float *)(score_sc + 0xc) - 320.0 + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = *(float *)(score_sc + 0x10) - 240.0 + ScreenRaitoY * 240.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// STUB: SADX 0x0055c250
void DisplayCalcLettersSB(struct task *tp)
{
}

// STUB: SADX 0x0055c5b0
void DisplayCalcBoardScoreSB(struct task *tp)
{
}

// STUB: SADX 0x0055c640
void DisplayCalcTimeScoreSB(struct task *tp)
{
}

// FUNCTION: SADX 0x0055c6d0
void DisplayCalcRingScoreSB(struct task *tp)
{
	DisplayCalcTimeScoreSB(tp);
	*(int *)(score_sc + 4) = 0xf4240;
	*(int *)(score_sc + 8) = (unsigned int)tp->twp->scl.z;
	*(float *)(score_sc + 0xc) = 0.0f + ScreenRaitoX * 320.0;
	*(float *)(score_sc + 0x10) = ScreenRaitoY * 240.0 + 32.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// STUB: SADX 0x0055c760
void FUN_0055c760(struct task *tp)
{
}

// STUB: SADX 0x0055c7f0
int FUN_0055c7f0(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0055cd10
void DisplayCalcLettersSC(struct task *tp)
{
}

// STUB: SADX 0x0055cee0
void DisplayCalcEnemyScoreSC(struct task *tp)
{
}

// FUNCTION: SADX 0x0055cf70
void FUN_0055cf70(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	DisplayCalcEnemyScoreSC(param_1);
	*(int *)(score_sc + 4) = 0x64;
	*(int *)(score_sc + 8) = (unsigned int)local_8->scl.y;
	*(float *)(score_sc + 0xc) = ScreenRaitoY * 240.0 + 144.0;
	*(float *)(score_sc + 0x10) = ScreenRaitoY * 240.0 + 32.0;
	FUN_0055de60((struct _SC_NUMBERS *)score_sc);
}

// STUB: SADX 0x0055d510
void DisplayCalcLettersTC(struct task *tp)
{
}

// STUB: SADX 0x0055db30
int FUN_0055db30(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0055dbd0
void InitTotalRingDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x0055e200
void InitBossTrialScore()
{
	int local_8;
	for (local_8 = 0; local_8 < 5; local_8++)
	{
		*(int *)((char *)DAT_05b3ea78 + local_8 * 0xc) = 0;
		*(int *)((char *)DAT_05b3ea78 + local_8 * 0xc + 4) = 0;
		*(int *)((char *)DAT_05b3ea78 + local_8 * 0xc + 8) = 0;
	}
}
