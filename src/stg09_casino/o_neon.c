#include "decls.h"
static void Disp1(struct task *tp);
static void Normal1(struct task *tp);
extern struct NJS_MODEL model_casi_nc_neoor_neoor[1];
extern struct NJS_MODEL model_casi_nc_neoor_b_neoor_b[1];
extern struct NJS_MODEL model_casi_nc_neoor_c_neoor_c[1];
void cNormal2(struct task *ctp);

// FUNCTION: SADX 0x00882ef0
static void Disp1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njPushMatrix(0);
	FUN_0067d830(0, -9.8377f, 0.0f, -2.053f);
	njRotateY(0, 0x6c1);
	late_DrawModel((struct NJS_MODEL *)var1->counter.ptr, 9);
	njPopMatrix(1);
	njPushMatrix(0);
	FUN_0067d830(0, 9.2365f, 0.0f, 3.961f);
	njRotateY(0, 0xe05b);
	late_DrawModel((struct NJS_MODEL *)var1->timer.ptr, 9);
	njPopMatrix(1);
	njRotateY(0, 0xf38f);
	late_DrawModel((struct NJS_MODEL *)var1->value.ptr, 9);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00883010
static void Normal1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->btimer++;
	if (var1->btimer == 6)
	{
		long var2 = var1->counter.l;
		var1->counter.l = var1->timer.l;
		var1->timer.l = var1->value.l;
		var1->btimer = 0;
		var1->value.l = var2;
	}
	Disp1(tp);
}

// FUNCTION: SADX 0x00883050
void cNormal2(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	struct task *var2 = ctp->ptp;

	if (var2->twp->flag & 0x100)
	{
		var1->btimer++;
	}
	if (var1->btimer < 0x64)
	{
		if ((int)var1->btimer % 0x19 > 0xa)
		{
			___dsDrawModel((struct NJS_MODEL *)var1->counter.ptr);
			return;
		}
		___dsDrawModel((struct NJS_MODEL *)var1->timer.ptr);
		return;
	}
	___dsDrawModel((struct NJS_MODEL *)var1->value.ptr);
}

// FUNCTION: SADX 0x008831a0
void ObjectNeon(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = &model_casi_nc_neoor_neoor;
	var1->timer.ptr = &model_casi_nc_neoor_b_neoor_b;
	var1->value.ptr = &model_casi_nc_neoor_c_neoor_c;
	tp->exec = Normal1;
	tp->disp = Disp1;
	tp->dest = ExplosionRockDestructor;
}
