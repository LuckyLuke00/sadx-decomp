#include "decls.h"
#include <math.h>
extern float _nj_unit_matrix_[16];
struct taskwk;
struct Angle3;
void FUN_008c9ae0(struct NJS_POINT3 *param_1, struct Angle3 *param_2, int param_3);
extern struct obj object_hakoirimusume[1];

// FUNCTION: SADX 0x008c9960
void FUN_008c9960(struct NJS_POINT3 *param_1, struct Angle3 *param_2)
{
	njPushMatrix(0);
	FUN_0067d830(0, param_1->x, param_1->y, param_1->z);
	if (param_2->z != 0)
	{
		njRotateZ(0, (unsigned short)param_2->z);
	}
	if (param_2->x != 0)
	{
		njRotateX(0, (unsigned short)param_2->x);
	}
	if (param_2->y != 0)
	{
		njRotateY(0, (unsigned short)param_2->y);
	}
	___dsDrawObject(&object_hakoirimusume[0]);
	njPopMatrix(1);
}

// STUB: SADX 0x008c9a00
int FUN_008c9a00(struct task *param_1)
{
	return (int)0;
}

// STUB: SADX 0x008c9a60
int FUN_008c9a60(struct task *param_1)
{
	return (int)0;
}

// STUB: SADX 0x008c9ae0
void FUN_008c9ae0(struct NJS_POINT3 *param_1, struct Angle3 *param_2, int param_3)
{
}

// FUNCTION: SADX 0x008c9c00
void FUN_008c9c00(struct NJS_POINT3 *param_1, struct taskwk *param_2, int param_3)
{
	struct NJS_POINT3 local_14;
	local_14.x = 0.0;
	local_14.y = 0.0;
	local_14.z = 0.0;
	local_14.z = (float)((double)njCos((long)((double)param_3 * 360.0 / (double)param_2->scl.x * 65536.0 / 360.0)) * (double)param_2->scl.y);
	local_14.x = (float)((double)njSin((long)((double)param_3 * 360.0 / (double)param_2->scl.x * 65536.0 / 360.0)) * (double)param_2->scl.y);
	njPushMatrix(&_nj_unit_matrix_);
	njTranslateV(0, &param_2->pos);
	if (param_2->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)param_2->ang.z);
	}
	if (param_2->ang.x != 0)
	{
		njRotateX(0, (unsigned short)param_2->ang.x);
	}
	if (param_2->ang.y != 0)
	{
		njRotateY(0, (unsigned short)param_2->ang.y);
	}
	njCalcVector(0, &local_14, param_1);
	njAddVector(param_1, &param_2->pos);
	njPopMatrix(1);
}
