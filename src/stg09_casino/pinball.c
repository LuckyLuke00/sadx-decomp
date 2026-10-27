#include "decls.h"
extern int DAT_060dbcb0;

// STUB: SADX 0x0086ae40
void SetReplayNow()
{
}

// STUB: SADX 0x0086af00
void GetRingNow(struct task *tp)
{
}

// FUNCTION: SADX 0x0086af90
void SetGetRing(unsigned char RingCount)
{
	struct task *var1;
	var1 = CreateElementalTask(2, 3, GetRingNow);
	var1->twp->wtimer = 5;
	var1->twp->btimer = RingCount;
}

// STUB: SADX 0x0086afc0
void SetDropRing(unsigned char RingCount)
{
}

// FUNCTION: SADX 0x0086aff0
float CheckBallSpeed(float NowSpeed)
{
	if (NowSpeed > 8.0f)
	{
		NowSpeed = 8.0f;
	}
	return NowSpeed;
}

// FUNCTION: SADX 0x0086b020
float GetBallSpeed()
{
	struct playerwk *var1;
	float local_8;
	var1 = GetPlayerWorkPointer(0);
	local_8 = var1->spd.x;
	if (local_8 < 0.0f)
	{
		local_8 = -local_8;
	}
	return local_8;
}

// FUNCTION: SADX 0x0086b800
void CardCombinationDestructor(struct task *tp)
{
	DAT_060dbcb0 &= 0xfff0ffff;
}
