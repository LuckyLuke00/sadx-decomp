#include "decls.h"
extern struct CHAO_GLOBAL ChaoGlobal;

// FUNCTION: SADX 0x0044a9d0
long AL_CanIWakeUp(struct task *tp)
{
	if (AL_EmotionGetValue(tp, 8) < 0x3e8)
	{
		if (AL_EmotionGetValue(tp, 9) < *(unsigned short *)((char *)&ChaoGlobal + 0x15a))
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x0044aa10
void AL_SleepControl(struct task *tp)
{
}

// STUB: SADX 0x0044af50
long ALBHV_Tron(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0044b1f0
void AL_CalcIntentionScore_Tron(struct task *tp, float *pMaxScore)
{
	float score;
	unsigned long var1;

	score = 0.0;
	var1 = AL_EmotionGetValue(tp, 9);
	if (var1 > 0x1f4)
	{
		score = AL_CalcScoreTypeA((long)var1, 0x1f4) * 0.5 + 0.5;
		AL_ScoreRandomise(&score);
	}
	if (score > *pMaxScore)
	{
		AL_SetBehavior(tp, ALBHV_Tron);
		AL_ClearIntention(tp);
		*pMaxScore = score;
	}
}

// STUB: SADX 0x0044b9d0
long ALBHV_SleepSelect(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x0044bab0
void AL_CalcIntentionScore_Sleep(struct task *tp, float *pMaxScore)
{
}
