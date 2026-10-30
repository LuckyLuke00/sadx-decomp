#include "decls.h"
static void NormalL(struct task *tp);

// GLOBAL: SADX 0x0480d5d0
static struct CCL_INFO object_c_info[3];

static void Exit(struct task *tp);
extern struct NJS_MODEL model_casi_stop01a_stop01a[];
extern struct NJS_MODEL model_casi_stop01a_k_stop01a_k[];
extern struct NJS_MODEL model_casi_stop02a_k_stop02a_k[];
extern int DAT_05b9d838;
extern int DAT_060dbcb0;

// FUNCTION: SADX 0x00886060
static void Exit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->mode == 0)
	{
		struct obj *var2 = (struct obj *)var1->counter.ptr;

		WithdrawCollisionEntry(tp, var2);
		ReleaseMobileLandObject(var2);
	}
	else
	{
		FreeTaskC(tp);
	}
}

// FUNCTION: SADX 0x00886090
void DispC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (!(DAT_060dbcb0 & 1))
	{
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop02b_k_stop02b_k, 1, 1.0f);
		FUN_0067d830(0, 0.0f, var1->timer.f, 0.0f);
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop01b_k_stop01b_k, 1, 1.0f);
	}
	else
	{
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop02b_stop02b, 1, 1.0f);
		FUN_0067d830(0, 0.0f, var1->timer.f, 0.0f);
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop01b_stop01b, 1, 1.0f);
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00886150
void DispLR(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if ((var1->mode == 1 && (DAT_060dbcb0 & 2) == 0) || (var1->mode == 2 && (DAT_060dbcb0 & 4) == 0))
		{
			late_DrawModelClip(&model_casi_stop02a_k_stop02a_k[0], 1, 1.0f);
			if (var1->ang.x != 0)
			{
				njRotateX(NULL, (unsigned short)var1->ang.x);
			}
			late_DrawModelClip(&model_casi_stop01a_k_stop01a_k[0], 1, 1.0f);
		}
		else
		{
			late_DrawModelClip(&model_casi_stop01a_k_stop01a_k[0], 1, 1.0f);
			if (var1->ang.x != 0)
			{
				njRotateX(NULL, (unsigned short)var1->ang.x);
			}
			late_DrawModelClip(&model_casi_stop01a_stop01a[0], 1, 1.0f);
		}
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00886240
void cNormalLR(struct task *ctp)
{
}

// STUB: SADX 0x008862e0
void NormalC(struct task *tp)
{
}

// FUNCTION: SADX 0x008863a0
static void NormalL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 Velo;
	long Ang[3];
	if (DAT_060dbcb0 & 2)
	{
		if (var1->cwp->flag & 1)
		{
			Velo.x = 5.0f;
			Velo.y = 0.0f;
			Velo.z = 0.0f;
			Ang[0] = 0;
			Ang[1] = 0x8000;
			Ang[2] = 0;
			SetVelocityAndRotationAndNoconTimeP(0, &Velo, Ang, 0);
			dsPlay_oneshot(9, 0, 0, 0);
			SetGetRing(8);
			DAT_060dbcb0 &= 0xfffffffd;
		}
		if (var1->ang.x != 0)
		{
			var1->ang.x += 0x100;
			if (var1->ang.x > 0)
			{
				var1->ang.x = 0;
			}
		}
	}
	else
	{
		if (var1->ang.x != 0xffffedde)
		{
			var1->ang.x -= 0x100;
			if (var1->ang.x < (long)0xffffedde)
			{
				var1->ang.x = 0xffffedde;
			}
		}
	}
	EntryColliList(var1);
	ObjectSetupInput(var1, 0);
	DispLR(tp);
	LoopTaskC(tp);
}

// FUNCTION: SADX 0x008864a0
void NormalR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 Velo;
	long Ang[3];
	if (DAT_060dbcb0 & 4)
	{
		if (var1->cwp->flag & 1)
		{
			Velo.x = 5.0f;
			Velo.y = 0.0f;
			Velo.z = 0.0f;
			Ang[0] = 0;
			Ang[1] = 0x8000;
			Ang[2] = 0;
			SetVelocityAndRotationAndNoconTimeP(0, &Velo, Ang, 0);
			dsPlay_oneshot(9, 0, 0, 0);
			SetGetRing(8);
			DAT_060dbcb0 &= 0xfffffffb;
		}
		if (var1->ang.x != 0)
		{
			var1->ang.x += 0x100;
			if (var1->ang.x > 0)
			{
				var1->ang.x = 0;
			}
		}
	}
	else
	{
		if (var1->ang.x != 0xffffedde)
		{
			var1->ang.x -= 0x100;
			if (var1->ang.x < (long)0xffffedde)
			{
				var1->ang.x = 0xffffedde;
			}
		}
	}
	EntryColliList(var1);
	ObjectSetupInput(var1, 0);
	DispLR(tp);
	LoopTaskC(tp);
}

// FUNCTION: SADX 0x008865f0
void ObjectStoperL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2;
	struct taskwk *var3;

	var1->mode = 1;
	CCL_Init(tp, &object_c_info[0], 1, 4);
	var2 = CreateChildTask(2, cNormalLR, tp);
	var3 = var2->twp;
	var3->pos.x = var1->pos.x;
	var3->pos.y = var1->pos.y;
	var3->pos.z = var1->pos.z - 40.0f;
	var3->ang.x = var1->ang.x;
	var3->ang.y = var1->ang.y;
	var3->ang.z = var1->ang.z;
	CCL_Init(var2, &object_c_info[1], 1, 4);
	DAT_060dbcb0 &= 0xfffffffd;
	tp->exec = NormalL;
	tp->disp = DispLR;
	tp->dest = Exit;
}
