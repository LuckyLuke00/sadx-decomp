#include "decls.h"
extern struct obj *DAT_045b2db0;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00862f90
void Object_IcecapIta02Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000100.0) == 0 && DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		ds_DrawModelClip((struct NJS_MODEL *)DAT_045b2db0, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00863020
void Object_IcecapIta02Exec(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1000100.0f) == 0)
	{
		Object_IcecapIta02Draw(tp);
	}
}

// FUNCTION: SADX 0x00863050
void ObjectIcecapIta02(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1000100.0) == 0)
	{
		tp->disp = Object_IcecapIta02Draw;
		tp->exec = Object_IcecapIta02Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
