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

// STUB: SADX 0x0044b1f0
void AL_CalcIntentionScore_Tron(struct task *tp, float *pMaxScore)
{
}
