#include "decls.h"
extern struct CHAO_GLOBAL ChaoGlobal;

// STUB: SADX 0x00468800
long ALBHV_Tameiki(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00468d10
long ALBHV_Sorrow(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00468db0
void AL_CalcIntentionScore_Sorrow(struct task *tp, float *pMaxScore)
{
	if (AL_EmotionGetValue(tp, 2) > *(unsigned int *)((char *)&ChaoGlobal + 0x1d0))
	{
		float local_8 = 1.0f - (float)(AL_EmotionGetValue(tp, 0x15) + 100) * 0.004999999888241291 * (1.0f - *(float *)((char *)&ChaoGlobal + 0x1d4));
		if (local_8 > *pMaxScore)
		{
			AL_SetBehavior(tp, ALBHV_Sorrow);
			AL_ClearIntention(tp);
			*pMaxScore = local_8;
		}
	}
}
