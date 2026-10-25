#include "decls.h"
extern struct CHAO_GLOBAL ChaoGlobal;
extern long ALBHV_Pain(struct task *tp);

// FUNCTION: SADX 0x00468760
void AL_CalcIntentionScore_Pain(struct task *tp, float *pMaxScore)
{
	float score;

	score = 0.0;
	if (AL_EmotionGetValue(tp, 5) > *(unsigned int *)((char *)&ChaoGlobal + 0x1dc))
	{
		score = 1.0f - (float)(100 - AL_EmotionGetValue(tp, 0x15)) * 0.004999999888241291 * (1.0f - *(float *)((char *)&ChaoGlobal + 0x1e0));
		AL_ScoreRandomise(&score);
		if (score > *pMaxScore)
		{
			AL_SetBehavior(tp, ALBHV_Pain);
			AL_ClearIntention(tp);
			*pMaxScore = score;
		}
	}
}
