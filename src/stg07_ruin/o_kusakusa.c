#include "decls.h"

// FUNCTION: SADX 0x00855620
void Disp2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		ds_DrawModelClip((struct NJS_MODEL *)&model_los_nc_happa_nc_happa, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00855c20
void ObjectGakekusa(struct task *tp)
{
	tp->twp->counter.ptr = object_los_nc_gakeshoku_nc_gakeshoku;
	ObjectNormal(tp);
}
