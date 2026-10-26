#include "decls.h"
extern struct CHAO_GLOBAL ChaoGlobal;

// FUNCTION: SADX 0x0045da00
long ALBHV_DakkoNormal(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLink(tp, 0x104);
		*(int *)((char *)tp->twp + 0xb0) &= 0xfffffff7;
		*(short *)((char *)var1 + 0x1c6) += 1;
	}
	DakkoControl(tp);
	return 0;
}

// STUB: SADX 0x0045e190
long ALBHV_DakkoTron(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0045e250
long ALBHV_Dakko(struct task *tp)
{
	int var1;

	if (AL_EmotionGetValue(tp, 9) > 0x1f4)
	{
		AL_SetBehavior(tp, ALBHV_DakkoTron);
	}
	else
	{
		var1 = AL_KW_GetPlayerLike(tp);
		if (var1 > 0x32)
		{
			AL_SetBehavior(tp, ALBHV_DakkoLike);
		}
		else if (var1 < -0x32)
		{
			AL_SetBehavior(tp, ALBHV_DakkoDislike);
		}
		else
		{
			AL_SetBehavior(tp, ALBHV_DakkoNormal);
		}
		if (AL_EmotionGetValue(tp, 6) < 0xa)
		{
			AL_ParameterAddUserLike(tp, 1, *(float *)((char *)&ChaoGlobal + 0xf0));
		}
	}
	*(int *)((char *)tp->twp + 0xb0) &= 0xfffffff7;
	DakkoControl(tp);
	return 0;
}

// STUB: SADX 0x0045e2f0
long AL_CheckDakko(struct task *tp)
{
	return (long)0;
}
