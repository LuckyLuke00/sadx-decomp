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
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
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
	*(float *)((char *)var1 + 0x34) = 0.0f;
	tp->exec = Normal;
	*(float *)((char *)var1 + 8) = *(float *)((char *)var1 + 0x20);
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	*(float *)((char *)var1 + 0xc) = *(float *)((char *)var1 + 0x24);
	*(float *)((char *)var1 + 0x10) = *(float *)((char *)var1 + 0x28);
	*(short *)((char *)tp->twp + 4) |= 0x100;
}
