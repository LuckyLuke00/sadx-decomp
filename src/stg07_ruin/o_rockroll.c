#include "decls.h"
void CreateSmoke(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl);

// FUNCTION: SADX 0x008587a0
void Exit(struct task *tp)
{
	SetFreeCameraMode(1);
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x008587b0
void C_Fire(struct task *cTask)
{
	struct taskwk *var1 = cTask->twp;
	struct taskwk *var2 = cTask->ptp->twp;
	struct NJS_POINT3 PointTmp;

	var1->btimer++;
	if ((var1->btimer & 7) == 0)
	{
		PointTmp.x = njCos(var2->ang.z + var1->ang.z) * 52.0f + var2->pos.x;
		PointTmp.y = njSin(var2->ang.z + var1->ang.z) * 52.0f + var2->pos.y;
		PointTmp.z = var2->pos.z + var1->timer.f;
		var1->scl.x = var2->scl.x;
		CreateFire(&PointTmp, &var1->scl, *(float *)((char *)var2 + 0x34));
	}
}

// FUNCTION: SADX 0x008588b0
void C_Smoke(struct task *cTask)
{
	struct taskwk *var1 = cTask->twp;
	struct taskwk *var2 = cTask->ptp->twp;
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;

	if (var1->btimer == 8)
	{
		var1->btimer = 0;
		local_14.x = var2->pos.x + 45.0f;
		local_14.y = var2->pos.y - 40.0f;
		local_14.z = var2->pos.z + var1->scl.x;
		local_20.x = 3.0f;
		local_20.y = var1->scl.y;
		local_20.z = var1->scl.z;
		CreateSmoke(&local_14, &local_20, 2.0f);
	}
	else
	{
		var1->btimer++;
	}
}

// STUB: SADX 0x00858960
void cSmokeInit(struct taskwk *cTaskWork, float FF, long AA)
{
}

// STUB: SADX 0x00858990
void SmokeInit(struct taskwk *twp, float FF, long AA)
{
}

// STUB: SADX 0x00858ea0
void ObjectRockRoll(struct task *tp)
{
}
