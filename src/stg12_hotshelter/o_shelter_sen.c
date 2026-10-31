#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
static void ExecNotBig(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008b4340
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		FUN_0067d830(0, 750.0f, 75.5f, -650.0f);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
		}
		SaveConstantAttr();
		OnConstantAttr(0, 0x100000);
		SetMaterial(var1->counter.f, 0.0f, 0.0f, 0.0f);
		FUN_0067d830(0, 0.0f, -10.5f, 0.0f);
		ds_DrawObjectClip(object_sen_sen_sen, 1.0f);
		ResetMaterial();
		LoadConstantAttr();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008b4430
static void ExecNotBig(struct task *tp)
{
	Disp(tp);
}

// STUB: SADX 0x008b4440
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b4730
void ObjShelterSen(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->pos.x = 750.0f;
	var1->ang.x = 0;
	var1->pos.y = 75.5f;
	var1->ang.y = 0;
	var1->ang.z = 0;
	var1->pos.z = -650.0f;
	var1->counter.f = 0.0f;
	var2->spd.x = 0.0f;
	var2->spd.y = 0.0f;
	var2->spd.z = 0.0f;
	if (GetPlayerCharacterName(0) == 7)
	{
		var1->mode = 1;
		tp->exec = Exec;
		tp->disp = Disp;
	}
	else
	{
		var1->mode = 0;
		tp->exec = ExecNotBig;
		tp->disp = Disp;
	}
}
