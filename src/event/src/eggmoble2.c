#include "decls.h"
extern struct task *DAT_060ccdc8;

// FUNCTION: SADX 0x007de470
void eggmoble2_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float ans[16];

	___dsSetPalette(2);
	___njSetTexture(&texlist_ev_eggmoble2);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	late_ActionClipMesh((struct NJS_ACTION *)&action_egm02jump_egm2_body, var1->counter.f, 1, 1.0f);
	___njSetTexture(&texlist_ev_eggman_body);
	CalcMMMatrix((float (*)[16])_nj_unit_matrix_, (struct NJS_ACTION *)&action_egm02jump_egm2_body, var1->counter.f, 3, (float (*)[16])ans);
	njMultiMatrix(NULL, (NJS_MATRIX (*))ans);
	ds_DrawObjectClip((struct obj *)&_object_egman_body_body, 1.0f);
	njPopMatrix(1);
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x007de620
void __fastcall FUN_007de620(void *param_1)
{
	float var1 = *(float *)((char *)param_1 + 0xc) + 0.09000000357627869;

	*(float *)((char *)param_1 + 0xc) = var1;
	*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_1 + 0x24) - var1;
	if (*(float *)((char *)param_1 + 0x24) < *(float *)((char *)param_1 + 0x10))
	{
		*(char *)param_1 = 2;
		*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_1 + 0x10);
	}
}

// FUNCTION: SADX 0x007de960
void EV_eggmoble2(float x, float y, float z, long ax, long ay, long az)
{
	struct task *var1;
	struct taskwk *var2;
	struct motionwk *var3;

	var1 = CreateElementalTask(3, 5, eggmoble2_exec);
	if (var1)
	{
		var2 = var1->twp;
		var2->pos.x = x;
		var2->ang.x = ax;
		var2->pos.y = y;
		var2->ang.y = ay;
		var2->pos.z = z;
		var2->mode = 0;
		var2->btimer = 1;
		var2->ang.z = az;
		var3 = var1->mwp;
		var3->work.f = 0.0f;
		DAT_060ccdc8 = var1;
		var3->rad = 0.0f;
	}
}

// FUNCTION: SADX 0x007de9c0
void ChgEgg2Mod(signed char mode)
{
	DAT_060ccdc8->twp->mode = mode;
}

// FUNCTION: SADX 0x007de9d0
void EV_deleggmoble2()
{
	if (DAT_060ccdc8)
	{
		FreeTask(DAT_060ccdc8);
		DAT_060ccdc8 = 0;
	}
}

// STUB: SADX 0x007de9f0
void ShadowEggmoble2(float size, float hight)
{
}
