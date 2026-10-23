#include "decls.h"

// STUB: SADX 0x0043b220
long AL_IconNormal(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x0043b490
long AL_IconHirameki(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x0043bc50
void AL_IconShapeControl(struct task *tp)
{
}

// STUB: SADX 0x0043bcf0
void AL_IconResetPos(struct task *tp)
{
}

// STUB: SADX 0x0043c180
float CalcCamDist(struct task *tp)
{
	return (float)0;
}

// FUNCTION: SADX 0x0043cb70
void AL_IconSet(struct task *tp, signed char Type, long Timer)
{
	struct taskwk *var1;

	var1 = tp->twp;
	*(short *)((char *)var1 + 0x702) = Type;
	*(int *)((char *)var1 + 0x704) = 0;
	*(int *)((char *)var1 + 0x708) = Timer;
}

// STUB: SADX 0x0043cba0
void AL_IconReset(struct task *tp)
{
}

// STUB: SADX 0x0043cd40
void AL_IconDraw(struct task *tp)
{
}
