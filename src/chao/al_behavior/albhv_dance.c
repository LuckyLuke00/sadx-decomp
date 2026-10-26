#include "decls.h"

// STUB: SADX 0x00451a80
long ALBHV_FuriFuriDance(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00451b70
long ALBHV_KuruKuruDance(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00451c60
long ALBHV_BoxDance(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_FaceSetEye(tp, (enum eAL_EYE_NUM)4, -1);
		AL_SetMotionLink(tp, 0x186);
		*(short *)((char *)var1 + 0x1c6) = *(short *)((char *)var1 + 0x1c6) + 1;
	}
	if (*(int *)((char *)var1 + 0x1dc) > 0)
	{
		if (AL_IsHitKindWithNum(tp, 1, 0xa6) == NULL)
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x00451cc0
long ALBHV_GoGoDance(struct task *tp)
{
	return (long)0;
}
