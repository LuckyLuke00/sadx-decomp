#include "decls.h"

// GLOBAL: SADX 0x0480d720
static struct CCL_INFO object_c_info[2];

static void NormalR(struct task *tp);
static void Disp(struct task *tp);
extern struct obj object_casi_fulip02a_fulip02a[];

// FUNCTION: SADX 0x00887060
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) + *(int *)((char *)var1 + 0xc) != 0)
		{
			njRotateY(NULL, (unsigned short)(*(short *)((char *)var1 + 0x18) + *(short *)((char *)var1 + 0xc)));
		}
		late_DrawModelClipEx((NJS_MODEL *)var1->counter.ptr, 1, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00887ac0
static void NormalR(struct task *tp)
{
}

// FUNCTION: SADX 0x00887c80
void ObjectFlipperR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 2, 4);
	var1->timer.l = 0;
	var1->value.l = 0x9b60;
	var1->flag = 0x8000;
	var1->counter.ptr = object_casi_fulip02a_fulip02a[0].model;
	tp->exec = NormalR;
	tp->disp = Disp;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
