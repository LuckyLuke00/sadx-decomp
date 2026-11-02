#include "decls.h"
extern int DAT_060eeaac;
extern int DAT_060eeac8;
void late_ActionMesh(NJS_ACTION *action, float frame, int flgs);

// FUNCTION: SADX 0x006bb980
void FUN_006bb980(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct forcewk *var2 = param_1->fwp;
	struct obj *var3;
	struct obj *var4;

	var2->pos_spd.x = 0.0f;
	var2->pos_spd.y = 0.0f;
	var2->pos_spd.z = 0.0f;
	((int *)var2)[1] = 0;
	((int *)var2)[2] = 0;
	((int *)var2)[3] = 0;
	var4 = *(struct obj **)((char *)DAT_060eea9c + 0xcc);
	var3 = GetMobileLandObject();
	var1->counter.ptr = var3;
	var3->evalflags = var4->evalflags;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->ang[0] = 0;
	var3->ang[1] = var1->ang.y;
	var3->ang[2] = 0;
	var3->pos[0] = var4->pos[0] + var1->pos.x;
	var3->pos[1] = var4->pos[1] + var1->pos.y;
	var3->pos[2] = var4->pos[2] + var1->pos.z;
	var3->model = var4->model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x40000000, param_1, var3);
	var4 = *(struct obj **)((char *)DAT_060eea9c + 0xdc);
	var3 = GetMobileLandObject();
	var1->timer.ptr = var3;
	var3->evalflags = var4->evalflags;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->ang[0] = 0;
	var3->ang[1] = var1->ang.y;
	var3->ang[2] = 0;
	var3->pos[0] = var4->pos[0] + var1->pos.x;
	var3->pos[1] = var4->pos[1] + var1->pos.y;
	var3->pos[2] = var4->pos[2] + var1->pos.z;
	var3->model = var4->model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x40000100, param_1, var3);
}

// FUNCTION: SADX 0x006bbbd0
void FUN_006bbbd0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckCollisionP(&var1->pos, 500.0f))
	{
		___njSetTexture(*(struct NJS_TEXLIST **)((char *)DAT_060eeac8 + 0x54));
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		late_ActionMesh(*(NJS_ACTION **)((char *)DAT_060eeaac + 0x40), *(float *)((char *)var1 + 0x10), 1);
		njPopMatrix(1);
	}
}
