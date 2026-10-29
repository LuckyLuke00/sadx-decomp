#include "decls.h"
static void Wait1(struct task *tp);
void BombDown(struct task *tp);
extern int DAT_060dbbe8;
extern void FUN_007d21b0(...);
extern void Wait1(struct task *tp);
extern struct NJS_MODEL model_jt_all1_bmjet_bmjet;

// FUNCTION: SADX 0x00868400
void BombExp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	long var2;

	var2 = var1->timer.l;
	var1->timer.l = var2 - 1;
	if (var2 == 0)
	{
		DestroyTask(tp);
	}
	else
	{
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x00868430
void DispBomb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip(model_bm_all1_bomb_bomb, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008684a0
void BombDown(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->pos.y <= *(float *)((char *)var1 + 8))
	{
		dsPlay_oneshot_v(0xe9, 0, 0, 0x60, var1->pos.x, var1->pos.y, var1->pos.z);
		CreateJetBomb(&var1->pos);
		VibShot(0, 0);
		*(int *)((char *)var1 + 0xc) = 0x28;
		CCL_Init(tp, (struct CCL_INFO *)&colli_bomb, 1, 4);
		tp->exec = BombExp;
		tp->disp = 0;
	}
	DispBomb(tp);
	var1->pos.y = var1->pos.y - 10.0;
}

// FUNCTION: SADX 0x00868540
void DispBmjet(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
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
	late_DrawModel(&model_jt_all1_bmjet_bmjet, 4);
	njPopMatrix(1);
}

// STUB: SADX 0x00868ae0
void Wait2(struct task *tp)
{
}

// STUB: SADX 0x00868e30
static void Wait1(struct task *tp)
{
}

// FUNCTION: SADX 0x00868f00
void ObjSnowBmjet(struct task *tp)
{
	DAT_060dbbe8 = 1;
	tp->exec = Wait1;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
