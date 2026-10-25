#include "decls.h"
void FUN_0043a4d0(void *param_1, int param_2);
void FUN_0043a600(float *param_1, float param_2);
extern struct MOTION_TABLE al_motion_table[1];

// FUNCTION: SADX 0x00438750
void AL_MotionInit(struct task *tp)
{
	MotionInit((struct MOTION_CTRL *)((char *)tp->twp + 0xbc), &al_motion_table[0]);
}

// FUNCTION: SADX 0x00438770
void AL_MotionControl(struct task *tp)
{
	if (*(unsigned char *)((char *)tp->twp + 0xb0) & 4)
	{
		MotionControl((struct MOTION_CTRL *)((char *)tp->twp + 0xbc));
	}
}

// FUNCTION: SADX 0x00438790
void AL_SetMotionLink(struct task *tp, long MtnNum)
{
	SetMotionLink((struct MOTION_CTRL *)((char *)tp->twp + 0xbc), MtnNum);
}

// FUNCTION: SADX 0x004387b0
void AL_SetMotionLinkStep(struct task *tp, long MtnNum, unsigned short step)
{
	SetMotionLinkStep((struct MOTION_CTRL *)((char *)tp->twp + 0xbc), MtnNum, step);
}

// FUNCTION: SADX 0x004387d0
void AL_SetMotionLinkSync(struct task *tp, long MtnNum)
{
	SetMotionLinkSync((struct MOTION_CTRL *)((char *)tp->twp + 0xbc), MtnNum);
}

// FUNCTION: SADX 0x004387f0
void AL_SetMotionSkip(struct task *tp, long MtnNum)
{
	FUN_0043a4d0((void *)((char *)tp->twp + 0xbc), MtnNum);
}

// FUNCTION: SADX 0x00438810
void AL_SetMotionSpd(struct task *tp, float Spd)
{
	FUN_0043a600((float *)((char *)tp->twp + 0xbc), Spd);
}

// FUNCTION: SADX 0x00438830
void AL_SetMotionFrame(struct task *tp, float Frame)
{
	SetMotionFrame((struct MOTION_CTRL *)((char *)tp->twp + 0xbc), Frame);
}

// STUB: SADX 0x00438850
float AL_GetMotionFrame(struct task *tp)
{
	return (float)0;
}

// STUB: SADX 0x00438870
long AL_GetMotionNum(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00438890
long AL_GetMotionPosture(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004388b0
long AL_IsMotionEnd(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004388d0
long AL_IsMotionStop(struct task *tp)
{
	return (long)0;
}
