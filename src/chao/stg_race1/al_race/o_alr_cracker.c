#include "decls.h"
extern struct NJS_POINT3 unitVecCracker;
extern struct NJS_POINT3 startPosCracker;
extern float _nj_unit_matrix_[16];
extern int DAT_05b35c44;
extern int DAT_05b35c48;

// FUNCTION: SADX 0x00489c90
void ObjectAlrCracker_Start()
{
	DAT_05b35c48 = 1;
	DAT_05b35c44 = GetGoalProductionLevel();
}

// FUNCTION: SADX 0x00489cb0
long ObjectAlrCracker_GetFlag()
{
	return DAT_05b35c48;
}

// STUB: SADX 0x00489cd0
void shotConfetti(struct task *pTask)
{
}

// FUNCTION: SADX 0x00489dd0
void shotTape(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;
	njPushMatrix(_nj_unit_matrix_);
	if (var1->ang.x)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	if (var1->ang.z)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	njCalcVector(0, &startPosCracker, &local_20);
	FUN_0067d2d0(0, var1->scl.x, var1->scl.x, var1->scl.x);
	njCalcVector(0, &unitVecCracker, &local_14);
	njPopMatrix(1);
	local_20.x += var1->pos.x;
	local_20.y += var1->pos.y;
	local_20.z += var1->pos.z;
	ObjectAlrTape(&local_20, &local_14);
}

// STUB: SADX 0x0048a000
void ObjectAlrCracker_Init()
{
}
