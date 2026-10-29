#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00811f30
void effectTwinkle(struct sp_task *tp, struct sp_link *lp)
{
	float *var1;

	var1 = (float *)tp->work[0].l;
	tp->no = (short)(long)(tp->frame);
	if (tp->no > 2)
	{
		tp->no = 2;
		SpFreeTask(tp);
		return;
	}
	tp->frame = var1[2] + tp->frame;
	tp->spd.x = tp->spd.x * var1[3];
	tp->spd.y = var1[3] * tp->spd.y + var1[4];
	tp->spd.z = tp->spd.z * var1[3];
	tp->pos.x = tp->spd.x + tp->pos.x;
	tp->pos.y = tp->pos.y + tp->spd.y;
	tp->pos.z = tp->spd.z + tp->pos.z;
	tp->scl = var1[1] * tp->scl;
}

// FUNCTION: SADX 0x00812090
void dispTPCoaster(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
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
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetObjectTexture();
		ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
		njPopMatrix(1);
	}
}
