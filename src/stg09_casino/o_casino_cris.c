#include "decls.h"

// GLOBAL: SADX 0x0480c704
static struct CCL_INFO object_c_info[1];

extern struct obj object_cas_obj_cris_cris;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x0087e360
void ObjectCasinoCrisDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (CheckRangeOutWithR(tp, 360010.0f))
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 8) + *(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, (Uint16)(*(unsigned short *)((char *)var1 + 8) + *(unsigned short *)((char *)var1 + 0x18)));
	}
	ds_DrawModelClip(object_cas_obj_cris_cris.model, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0087e3f0
void ObjectCasinoCrisExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0087e470
void ObjectCasinoCris(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		struct taskwk *var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			*(int *)((char *)var1 + 0x14) = 0;
			*(int *)((char *)var1 + 0x1c) = 0;
			CCL_Init(tp, &object_c_info[0], 1, 4);
		}
		tp->disp = ObjectCasinoCrisDraw;
		tp->exec = ObjectCasinoCrisExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
