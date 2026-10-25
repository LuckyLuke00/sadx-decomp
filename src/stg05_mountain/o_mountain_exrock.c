#include "decls.h"

// FUNCTION: SADX 0x00828d40
void ExplosionRockDestructor(struct task *_this)
{
	FreeTaskC(_this);
}

// STUB: SADX 0x00828d50
void MiddleRockDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x00828e10
void EffectSteam(struct sp_task *tp, struct sp_link *lp)
{
	float *var1;
	float var2;

	var1 = (float *)tp->work[0].l;
	tp->no = (short)(long)(tp->frame);
	if (tp->no >= 8)
	{
		tp->no = 7;
		SpFreeTask(tp);
		return;
	}
	tp->frame = var1[2] + tp->frame;
	tp->scl = var1[1] + tp->scl;
	if (tp->argb.g < 1.0)
	{
		tp->argb.g = tp->argb.g + 0.07000000029802322;
		tp->argb.b = tp->argb.b + 0.07000000029802322;
	}
	var2 = 1.0 - var1[3];
	tp->spd.x = tp->spd.x * var2;
	tp->spd.y = tp->spd.y * var2;
	tp->spd.z = tp->spd.z * var2;
	tp->spd.y = tp->spd.y + var1[4];
	tp->pos.x = tp->pos.x + tp->spd.x;
	tp->pos.y = tp->pos.y + tp->spd.y;
	tp->pos.z = tp->pos.z + tp->spd.z;
}

// FUNCTION: SADX 0x00829bb0
void SetUpExplosionRock()
{
	CreateElementalTask(2, 3, ObjectMountainExplosionRock1);
	CreateElementalTask(2, 3, ObjectMountainExplosionRock2);
}
