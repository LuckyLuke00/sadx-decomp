#include "decls.h"
void FUN_00450fc0(struct task *param_1, short param_2);
void FUN_00450fc0(struct task *param_1, short param_2);

// STUB: SADX 0x00450e60
float AL_CalcScoreTypeA(long value, long trigger)
{
	return (float)0;
}

// FUNCTION: SADX 0x00450ea0
float FUN_00450ea0(int param_1, int param_2)
{
	float var1 = (float)param_2;
	if (param_1 < param_2)
	{
		return (var1 - (float)param_1) / var1;
	}
	else
	{
		return 0.0f;
	}
}

// STUB: SADX 0x00450ed0
float AL_CalcMoodScoreTypeA(long value, long trigger)
{
	return (float)0;
}

// STUB: SADX 0x00450f10
void AL_ScoreRandomise(float *pScore)
{
}

// FUNCTION: SADX 0x00450f70
unsigned long AL_GetIntervalTimer(struct task *tp, unsigned short TimerKind)
{
	return *(unsigned long *)((char *)tp->twp + 0x1e8 + TimerKind * 4);
}

// FUNCTION: SADX 0x00450f90
unsigned long AL_SetIntervalTimer(struct task *tp, unsigned short TimerKind, unsigned long timer)
{
	*(unsigned long *)((char *)tp->twp + 0x1e8 + TimerKind * 4) = timer;
	return 0;
}

// FUNCTION: SADX 0x00450fb0
unsigned short AL_GetIntention(struct task *tp)
{
	return *(unsigned short *)((char *)tp->twp + 0x1e0);
}

// STUB: SADX 0x00450fc0
void FUN_00450fc0(struct task *tp, short value)
{
}

// FUNCTION: SADX 0x00450fe0
void AL_IntervalTimerControl(struct task *tp)
{
	int *var1 = (int *)((char *)tp->twp + 0x1ec);
	int var2 = 4;
	while (var2 != 0)
	{
		if (var1[-1] != 0)
		{
			var1[-1]--;
		}
		if (var1[0] != 0)
		{
			var1[0]--;
		}
		if (var1[1] != 0)
		{
			var1[1]--;
		}
		if (var1[2] != 0)
		{
			var1[2]--;
		}
		var1 += 4;
		var2--;
	}
}

// FUNCTION: SADX 0x00451030
void AL_ClearIntention(struct task *tp)
{
	FUN_00450fc0(tp, 0);
}
