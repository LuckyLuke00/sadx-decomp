#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00894590
void pin_side_search_obj(struct obj *obj_p, struct obj *target_obj_p, struct NJS_POINT3 *pos_p)
{
	struct obj *var1;

	do
	{
		njPushMatrix(0);
		FUN_0067d830(0, obj_p->pos[0], obj_p->pos[1], obj_p->pos[2]);
		njRotateXYZ(0, obj_p->ang[0], obj_p->ang[1], obj_p->ang[2]);
		if (obj_p == target_obj_p)
		{
			njGetTranslation(0, pos_p);
		}
		else if (obj_p->child != 0)
		{
			pin_side_search_obj(obj_p->child, target_obj_p, pos_p);
		}
		njPopMatrix(1);
		var1 = obj_p->sibling;
		obj_p = var1;
	} while (obj_p != 0);
}

// STUB: SADX 0x00894620
void pin_side_lamp_exec(struct task *task_p)
{
}
