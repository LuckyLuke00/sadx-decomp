#include "decls.h"

// FUNCTION: SADX 0x00492c60
void ADV1_AL_InitGroundCollision(struct taskwk *twp, struct alifewk *awp)
{
	*(float *)((char *)awp + 0x140) = 0.0f;
	*(float *)((char *)awp + 0x144) = 5.0f;
	*(float *)((char *)awp + 0x148) = 0.0f;
	*(float *)((char *)awp + 0x14c) = 15.0f;
	*(float *)((char *)awp + 0x150) = 15.0f;
	*(float *)((char *)awp + 0x154) = -3.0f;
	*(float *)((char *)awp + 0x15c) = 0.23f;
	*(float *)((char *)awp + 0x170) = 1.6f;
	*(float *)((char *)awp + 0x174) = 1.0f;
}

// FUNCTION: SADX 0x004931f0
void ADV1_AL_PreserveHomePosition(struct taskwk *twp, struct alifewk *awp)
{
	awp->home = twp->pos;
}

// FUNCTION: SADX 0x00493220
void ADV1_AL_PreservePreviousPosition(struct taskwk *twp, struct alifewk *awp)
{
	awp->pre = twp->pos;
}

// STUB: SADX 0x00493250
long ADV1_AL_CalcAimAngle(struct taskwk *twp, struct alifewk *awp)
{
	return (long)0;
}

// STUB: SADX 0x004932b0
long ADV1_AL_TurnToAim(struct taskwk *twp, struct alifewk *awp)
{
	return (long)0;
}
