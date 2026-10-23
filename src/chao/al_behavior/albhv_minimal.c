#include "decls.h"
extern "C" int rand(void);

// STUB: SADX 0x004553b0
long ALBHV_Kaoarau(struct task *tp)
{
	return (long)0;
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

// STUB: SADX 0x00455f80
long ALBHV_Fukkin2(struct task *tp)
{
	return (long)0;
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

// STUB: SADX 0x00456230
long ALBHV_HaraSuberi(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004562f0
long ALBHV_Shippo(struct task *tp)
{
	return (long)0;
}
