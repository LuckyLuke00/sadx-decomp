#include "decls.h"

// FUNCTION: SADX 0x00468400
void AL_CalcIntentionScore_Pleasure(struct task *tp, float *pMaxScore)
{
	float score;

	score = 0.0;
	if (AL_EmotionGetValue(tp, 0) > *(unsigned int *)((char *)&ChaoGlobal + 0x1e8))
	{
		score = 1.0f - (float)(100 - AL_EmotionGetValue(tp, 0x1e)) * 0.004999999888241291 * (1.0f - *(float *)((char *)&ChaoGlobal + 0x1ec));
		AL_ScoreRandomise(&score);
		if (score > *pMaxScore)
		{
			AL_SetBehavior(tp, ALBHV_Pleasure);
			AL_ClearIntention(tp);
			*pMaxScore = score;
		}
	}
}
