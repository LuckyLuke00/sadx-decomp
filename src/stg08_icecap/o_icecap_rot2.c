#include "decls.h"
static void Exec(struct task *tp);
static void Draw(struct task *tp);
extern struct obj object_green_ki_drya_ki_drya[];
extern struct obj object_green_moku_b_moku_b[];
extern struct obj object_green_moku_a_moku_a[];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00866240
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		late_DrawObjectClipEx((struct obj *)var1->timer.ptr, 1, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008662c0
static void Exec(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		Draw(tp);
	}
}

// FUNCTION: SADX 0x008662e0
void ObjectGreenMokuA(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = Exec;
	tp->disp = Draw;
	tp->twp->timer.l = (long)object_green_moku_a_moku_a;
}

// FUNCTION: SADX 0x00866310
void ObjectGreenMokuB(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = Exec;
	tp->disp = Draw;
	tp->twp->timer.ptr = &object_green_moku_b_moku_b[0];
}

// FUNCTION: SADX 0x00866370
void ObjectGreenKiDryA(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = Exec;
	tp->disp = Draw;
	tp->twp->timer.l = (long)&object_green_ki_drya_ki_drya;
}

// STUB: SADX 0x008663a0
void ObjectGreenKiDryB(struct task *tp)
{
}
