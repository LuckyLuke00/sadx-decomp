#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x004553b0
long ALBHV_Kaoarau(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLink(tp, 0x11b);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 2.9999990463256836) + 2);
		break;
	case 1:
		break;
	default:
		return 0;
	}
	if (AL_IsMotionEnd(tp) != 0)
	{
		*(int *)((char *)var1 + 0x1d0) = *(int *)((char *)var1 + 0x1d0) - 1;
		if (*(int *)((char *)var1 + 0x1d0) <= 0)
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x00455460
long ALBHV_Bakuten(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004556c0
long ALBHV_BreakDance(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455710
long ALBHV_GoGoDanceMini(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455760
long ALBHV_Dosukoi(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455980
long ALBHV_Otakai(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455a60
long ALBHV_ShiriDance(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455b10
long ALBHV_BoxDanceDX(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455de0
long ALBHV_Fire(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00455ed0
long ALBHV_PyonPyon(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLink(tp, 0x138);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 3.9999990463256836) + 4);
		break;
	case 1:
		break;
	default:
		return 0;
	}
	if (AL_IsMotionEnd(tp) != 0)
	{
		*(int *)((char *)var1 + 0x1d0) = *(int *)((char *)var1 + 0x1d0) - 1;
		if (*(int *)((char *)var1 + 0x1d0) <= 0)
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00455f80
long ALBHV_Fukkin2(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLink(tp, 0x139);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 3.9999990463256836) + 4);
		break;
	case 1:
		break;
	default:
		return 0;
	}
	if (AL_IsMotionEnd(tp) != 0)
	{
		*(int *)((char *)var1 + 0x1d0) = *(int *)((char *)var1 + 0x1d0) - 1;
		if (*(int *)((char *)var1 + 0x1d0) <= 0)
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00456030
long ALBHV_Fukkin(struct task *tp)
{
	AL_SetBehavior(tp, ALBHV_PostureChangeSit);
	AL_SetNextBehavior(tp, ALBHV_Fukkin2);
	return 0;
}

// STUB: SADX 0x00456060
long ALBHV_Denguri(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00456150
long ALBHV_GoroGoro(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;
	int var4;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLink(tp, 0x144);
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 301.0) + 500);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		break;
	case 1:
		break;
	default:
		return 0;
	}
	var4 = *(int *)((char *)var1 + 0x1d0);
	*(int *)((char *)var1 + 0x1d0) = var4 - 1;
	if (var4 <= 0)
	{
		return 1;
	}
	*(float *)((char *)var1 + 0x20) = *(float *)((char *)var1 + 0x20) + njSin(*(int *)((char *)var1 + 0x18) - 0x4000) * 0.05000000074505806;
	*(float *)((char *)var1 + 0x28) = *(float *)((char *)var1 + 0x28) + njCos(*(int *)((char *)var1 + 0x18) - 0x4000) * 0.05000000074505806;
	return 0;
}

// FUNCTION: SADX 0x00456230
long ALBHV_HaraSuberi(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;

	var1 = tp->twp;
	switch (*(unsigned short *)((char *)var1 + 0x1c6))
	{
	case 0:
		AL_SetMotionLink(tp, 0x71);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 61.0) + 0x78);
		break;
	case 1:
		break;
	default:
		return 0;
	}
	if (AL_IsMotionEnd(tp) != 0)
	{
		*(int *)((char *)var1 + 0x1d0) = *(int *)((char *)var1 + 0x1d0) - 1;
		if (*(int *)((char *)var1 + 0x1d0) <= 0)
		{
			return 1;
		}
	}
	AL_ForwardSpd(tp, 0.15f);
	return 0;
}

// STUB: SADX 0x004562f0
long ALBHV_Shippo(struct task *tp)
{
	return (long)0;
}
