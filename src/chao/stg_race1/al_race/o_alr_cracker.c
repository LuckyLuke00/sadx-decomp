#include "decls.h"
void FUN_0048a4d0(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2, long param_3);
void ObjectAlrCracker(struct task *pTask);
extern struct obj object_cr4_nc_crk_nc_crk[1];
extern struct obj object_cr4_nc_crk2_nc_crk2[1];
extern struct obj object_cr4_nc_crk3_nc_crk3[1];
extern struct obj object_cr4_nc_crk4_nc_crk4[1];
void shotConfetti(struct task *pTask);
void shotTape(struct task *pTask);
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

// FUNCTION: SADX 0x00489cd0
void shotConfetti(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;
	njPushMatrix(&_nj_unit_matrix_);
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
	FUN_0048a4d0(&local_20, &local_14, (long)var1->scl.y);
}

// FUNCTION: SADX 0x00489dd0
void shotTape(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;
	njPushMatrix(&_nj_unit_matrix_);
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

// FUNCTION: SADX 0x0048a000
void ObjectAlrCracker_Init()
{
	const struct obj *table[4];
	DAT_05b35c48 = 0;
	table[0] = (const struct obj *)&object_cr4_nc_crk_nc_crk;
	table[1] = (const struct obj *)&object_cr4_nc_crk2_nc_crk2;
	table[2] = (const struct obj *)&object_cr4_nc_crk3_nc_crk3;
	table[3] = (const struct obj *)&object_cr4_nc_crk4_nc_crk4;
	unsigned int var1;
	for (var1 = 0; var1 < 4; var1++)
	{
		const struct obj *var2 = table[var1];
		struct task *var3 = CreateElementalTask(2, 4, ObjectAlrCracker);
		if (var3)
		{
			struct taskwk *var4 = var3->twp;
			var4->pos.x = var2->pos[0];
			var4->pos.y = var2->pos[1];
			var4->pos.z = var2->pos[2];
			var4->ang.x = var2->ang[0];
			var4->ang.y = var2->ang[1];
			var4->ang.z = var2->ang[2];
			var4->scl.x = 1.5f;
			var4->scl.y = 15.0f;
			var4->scl.z = 0.0f;
		}
	}
}
