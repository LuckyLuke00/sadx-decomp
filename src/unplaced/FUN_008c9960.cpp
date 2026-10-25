#include "decls.h"
#include <math.h>
struct taskwk;
void njPushMatrix(float *param_1);
void njRotateZ(float *param_1, int param_2);
void njRotateX(float *param_1, unsigned short param_2);
void njRotateY(float *param_1, unsigned short param_2);
void njPopMatrix(int param_1);
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
int FUN_008c9a00(struct task *tp)
{
	return (int)0;
}

// STUB: SADX 0x008c9a60
int FUN_008c9a60(struct task *tp)
{
	return (int)0;
}

// STUB: SADX 0x008c9ae0
void FUN_008c9ae0(struct NJS_POINT3 *param_1, struct Angle3 *param_2, int param_3)
{
}

// STUB: SADX 0x008c9c00
void FUN_008c9c00(struct NJS_POINT3 *param_1, struct taskwk *param_2)
{
}
