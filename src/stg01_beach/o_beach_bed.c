#include "decls.h"
static void Disp(struct task *tp);

// GLOBAL: SADX 0x03a0c260
static struct CCL_INFO object_c_info[2];

static void Exec(struct task *tp);

// FUNCTION: SADX 0x007f9370
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
		ds_DrawObjectClip((struct obj *)&object_seaobj_beachbed_beachbed, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x007f9400
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut_L(tp))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
	Disp(tp);
}

// FUNCTION: SADX 0x007f9440
void ObjectBeachBed(struct task *tp)
{
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 2, 4);
	}
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
