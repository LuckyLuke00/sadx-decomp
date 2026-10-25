#include "decls.h"
extern struct obj object_youUPan_yogun_yogun;
extern struct obj object_fujiyou_fujiy_fujiy[1];
extern struct NJS_TEXLIST texlist_yougan_anim;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00829c50
void YougunSetDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_yougan_anim);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	FUN_0067d2d0(0, var1->scl.x + 1.0f, 1.0f, var1->scl.z + 1.0f);
	ds_DrawModelClip(object_fujiyou_fujiy_fujiy[0].model, FUN_00500c70(var1->scl.x + 1.0f, 1.0f, var1->scl.z + 1.0f));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00829d10
void YougunSetDisplayE102(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_yougan_anim);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawModelClip(object_youUPan_yogun_yogun.model, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00829fe0
void ObjectMountainSetYougan(struct task *tp)
{
}

// STUB: SADX 0x0082a0d0
void ObjectMountainSetYouganE102(struct task *tp)
{
}
