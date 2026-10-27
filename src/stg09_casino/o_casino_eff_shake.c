#include "decls.h"
static void ObjectCasinoEarthShakeExec(struct task *tp);

// STUB: SADX 0x0088d7c0
static void ObjectCasinoEarthShakeExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0088d8a0
void ObjectCasinoEarthShake(struct task *tp)
{
	tp->exec = ObjectCasinoEarthShakeExec;
}

// FUNCTION: SADX 0x0088d8b0
struct task *CreateEarthShake_Casino(struct NJS_POINT3 *pos, float rad, float shake)
{
	struct task *var1;
	struct taskwk *var2;
	struct taskwk *var3;
	float var4;

	var3 = DAT_05baf368[0];
	var4 = njSqrt((pos->x - var3->pos.x) * (pos->x - var3->pos.x) + (pos->y - var3->pos.y) * (pos->y - var3->pos.y) + (pos->z - var3->pos.z) * (pos->z - var3->pos.z));
	if (var4 < rad)
	{
		var1 = CreateElementalTask(2, 3, ObjectCasinoEarthShake);
		if (var1 != NULL)
		{
			var2 = var1->twp;
			var2->scl.x = 0.0f;
			var2->scl.y = shake;
			var2->scl.z = 1.0f - var4 / rad;
			VibShot(0, 0);
			return var1;
		}
	}
	return NULL;
}
