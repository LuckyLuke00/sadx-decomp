#include "decls.h"
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
