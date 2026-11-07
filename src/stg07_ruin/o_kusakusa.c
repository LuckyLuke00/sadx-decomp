#include "decls.h"

// FUNCTION: SADX 0x00855620
void Disp2(struct task *tp)
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
