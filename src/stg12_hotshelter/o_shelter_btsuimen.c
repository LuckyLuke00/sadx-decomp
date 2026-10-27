#include "decls.h"
extern struct obj object_suimen_wt_j2h_wt_j2h[];
extern float DAT_05b3df40;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008b5090
void SideExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckCollisionCylinderP(&var1->pos, 150.0f, 50.0f))
	{
		var1->flag |= 0x100;
		return;
	}
	var1->flag &= 0xfeff;
}

// FUNCTION: SADX 0x008b50e0
void TubeDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_shelter_suimen);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	DAT_05b3df40 = -17952.0f;
	late_DrawObjectClipMS(object_suimen_wt_j2h_wt_j2h, 0, 1.0f);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

// STUB: SADX 0x008b5170
void SideInit(struct task *tp)
{
}

// STUB: SADX 0x008b5230
void SideInit2(struct task *tp)
{
}

// STUB: SADX 0x008b52f0
void TubeExec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b5370
void TubeInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct forcewk *var2 = tp->fwp;
	struct obj *var3;

	var1->pos.x = 750.0f;
	var1->pos.y = 52.0f;
	var1->btimer = 0;
	var1->smode = 0;
	var1->pos.z = -272.5f;
	var1->value.f = 31.0f;
	var1->timer.f = 31.0f;
	var2->ang_spd.x = 0;
	var2->ang_spd.y = 0;
	var2->ang_spd.z = 0;
	var2->pos_spd.x = 0.0f;
	var2->pos_spd.y = 0.0f;
	var2->pos_spd.z = 0.0f;
	var3 = GetMobileLandObject();
	var1->counter.ptr = var3;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->evalflags = 0x34;
	var3->ang[0] = 0;
	var3->ang[1] = 0;
	var3->ang[2] = 0;
	var3->pos[0] = var1->pos.x;
	var3->pos[1] = 52.0f;
	var3->pos[2] = var1->pos.z;
	var3->model = object_suimen_wt_j2h_wt_j2h[0].model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x28000002, tp, var3);
	var1->flag &= 0xfeff;
	tp->exec = TubeExec;
	tp->disp = TubeDisp;
	tp->dest = FUN_00825de0;
}

// STUB: SADX 0x008b55d0
void ObjShelterBtsuimen(struct task *tp)
{
}
