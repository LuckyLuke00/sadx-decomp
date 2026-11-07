#include "decls.h"

// GLOBAL: SADX 0x043ac900
static struct CCL_INFO object_c_info[2];

static void Normal(struct task *tp);
extern struct obj object_togedai_togedai_togedai[];
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00855c40
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)(short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)&object_togedai_togedai_togedai, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00855cd0
static void Normal(struct task *tp)
{
}

// STUB: SADX 0x00856090
void ObjectTogedai1(struct task *tp)
{
}

// FUNCTION: SADX 0x008560f0
void ObjectTogedai2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	CCL_Init(tp, (struct CCL_INFO *)&object_c_info, 2, 4);
	var1->scl.z = 0.0f;
	tp->exec = Normal;
	var1->counter.f = var1->pos.x;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->timer.f = var1->pos.y;
	var1->value.f = var1->pos.z;
	tp->twp->flag |= 0x100;
}
