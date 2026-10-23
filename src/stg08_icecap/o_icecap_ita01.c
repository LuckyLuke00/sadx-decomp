#include "decls.h"
extern struct NJS_MODEL *DAT_045b3108;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00863090
void Object_IcecapIta01Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000100.0f) == 0)
	{
		if (DAT_05b9d838 == 0)
		{
			SetObjectTexture();
			njPushMatrix((float *)0);
			njTranslateV((float *)0, &var1->pos);
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
			}
			ds_DrawModelClip(DAT_045b3108, 1.0f);
			njPopMatrix(1);
		}
	}
}

// FUNCTION: SADX 0x00863120
void Object_IcecapIta01Exec(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1000100.0f) == 0)
	{
		Object_IcecapIta01Draw(tp);
	}
}

// FUNCTION: SADX 0x00863150
void ObjectIcecapIta01(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1000100.0f) == 0)
	{
		tp->disp = Object_IcecapIta01Draw;
		tp->exec = Object_IcecapIta01Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
