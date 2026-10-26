#include "decls.h"
void FUN_00422560(int param_1);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void FUN_004a0520(float param_1, float param_2);
float FUN_00500c70(float param_1, float param_2, float param_3);
extern struct NJS_TEXLIST texlist_egg_missile;
extern struct obj _object_missile_body_body;
extern struct NJS_POINT2 DAT_05b3e050;

// FUNCTION: SADX 0x007dec40
void eggmissile_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	FUN_00422560(3);
	___njSetTexture(&texlist_egg_missile);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	FUN_0067d2d0((float *)0, var1->scl.x, var1->scl.y, var1->scl.z);
	FUN_004a0520(-1.0f, -65535.0f);
	ds_DrawObjectClip(&_object_missile_body_body, FUN_00500c70(var1->scl.x, var1->scl.y, var1->scl.z));
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	njPopMatrix(1);
	npSetZCompare();
}

// STUB: SADX 0x007ded40
void FUN_007ded40(struct NJS_MESHSET *param_1)
{
}

// STUB: SADX 0x007def30
void SetEggMissileParam(struct task *tp, float scl)
{
}

// FUNCTION: SADX 0x007def50
void SetMissileEffect(struct task *tp, unsigned char attr)
{
	if (tp != 0)
	{
		tp->twp->btimer = attr;
	}
}

// STUB: SADX 0x007def70
void ExecEggmissileFire(struct sp_task *tp, struct sp_link *lp)
{
}

// STUB: SADX 0x007df210
void eggmissile_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007df270
struct task *Create_EV_Eggmissile()
{
	return CreateElementalTask(2, 3, eggmissile_init);
}
