#include "decls.h"

// FUNCTION: SADX 0x004622c0
long ALBHV_Notice(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
		case 0:
			*(int *)((char *)var1 + 0x1d8) = 0x708;
			AL_IconSet(tp, 1, 0xb4);
			*(short *)((char *)var1 + 0x1c6) = *(short *)((char *)var1 + 0x1c6) + 1;
			*(int *)((char *)var1 + 0x1d0) = 0;
			*(int *)((char *)var1 + 0x1d4) = 0;
			break;
		case 1:
			{
				int var2 = *(int *)((char *)var1 + 0x1d0);
				*(int *)((char *)var1 + 0x1d0) = var2 + 1;
				if (var2 > 0x78)
				{
					return 1;
				}
			}
			break;
	}
	*(int *)((char *)var1 + 0x1d8) = *(int *)((char *)var1 + 0x1d8) - 1;
	if (*(int *)((char *)var1 + 0x1d8) <= 0)
	{
		AL_SetBehavior(tp, ALBHV_Think);
	}
	return 0;
}

// FUNCTION: SADX 0x00462350
long ALBHV_TurnToAim(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLinkStep(tp, 0x64, 0xf);
		*(short *)((char *)var1 + 0x1c6) = *(short *)((char *)var1 + 0x1c6) + 1;
		*(int *)((char *)var1 + 0x1d0) = 0x3c;
	}
	return MOV_TurnToAim2(tp, 0x200) < 0xb6;
}

// STUB: SADX 0x004624c0
long ALBHV_TurnToLockOn(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00462780
long ALBHV_GoToLockOn(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00462880
long ALBHV_Touch(struct task *tp)
{
	return (long)0;
}
