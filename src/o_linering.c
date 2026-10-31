#include "decls.h"
static void Exec(struct task *tp);
extern int DAT_05b9d838;
extern struct obj object_sphere01;

// FUNCTION: SADX 0x008b9b80
void ObjectLinering(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	*(int *)((char *)local_cg + 0x1c) = 0;
	local_cg->mode = 0;
	local_cg->wtimer = 0;
	local_cg->mode = 0;
	LineringInit(tp);
	tp->exec = Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_008b9f60;
}

// STUB: SADX 0x008b9be0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b9f60
void FUN_008b9f60(struct task *param_1, int param_2)
{
	FreeTaskC(param_1);
}

// STUB: SADX 0x008b9f80
void LineringInit(struct task *tp)
{
}

// FUNCTION: SADX 0x008ba100
void SetLineringEffect(long on)
{
	ring_kiran = on;
}

// FUNCTION: SADX 0x008ba110
void LineringDisp(struct task *tp)
{
	struct taskwk *local_10;
	struct motionwk *local_ci;
	int local_8g;

	local_10 = tp->twp;
	local_ci = tp->mwp;
	if (DAT_05b9d838 != 0)
		return;
	njPushMatrix(0);
	njTranslateV(0, &local_10->pos);
	for (local_8g = 0; local_8g < *(int *)((char *)local_10 + 0xc); local_8g++)
	{
		njPushMatrix(0);
		FUN_0067d2d0(0, 0.3f, 0.3f, 0.3f);
		late_DrawObject(&object_sphere01, 4);
		njPopMatrix(1);
		njTranslateV(0, (struct NJS_POINT3 *)((char *)local_ci + 4));
	}
	njPopMatrix(1);
}
