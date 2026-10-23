#include "decls.h"

// STUB: SADX 0x00467500
long ALBHV_Greet(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00467590
long ALBHV_CalcMeetPlayer(struct task *tp)
{
	AL_KW_MeetPlayer(tp);
	return 1;
}

// FUNCTION: SADX 0x004675b0
long ALBHV_SuriSuri(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLinkStep(tp, 0x193, 0x14);
		AL_FaceChangeEye(tp, (enum eAL_EYE_NUM)3);
		AL_FaceChangeMouth(tp, (enum eAL_MOUTH_NUM)3);
		(*(unsigned short *)((char *)var1 + 0x1c6))++;
		break;
	case 1:
		break;
	default:
		return 0;
	}
	if (AL_IsMotionEnd(tp) != 0)
	{
		if (MOV_Dist2FromPlayer(tp, 0) < 25.0)
		{
			AL_EmotionAdd(tp, 0, 0xa);
			AL_SetBehavior(tp, ALBHV_SuriSuri);
			if (AL_EmotionGetValue(tp, 0) > 0x8c)
			{
				AL_EmotionAdd(tp, 0xd, 0xffffe890);
				return 1;
			}
		}
		else
		{
			AL_SetBehavior(tp, ALBHV_SuriSuriPlayer);
		}
	}
	return 0;
}
