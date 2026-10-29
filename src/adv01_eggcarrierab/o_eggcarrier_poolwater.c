#include "decls.h"
extern float DAT_05b3df40;
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);
extern struct obj **DAT_060eea88;
extern struct NJS_TEXLIST texlist_ec_water;
void ___njSetTexture(struct NJS_TEXLIST *);
void late_DrawObjectClip(struct obj *, int, float);

// FUNCTION: SADX 0x006959f0
void WaterDisplayer(struct task *tp)
{
	struct taskwk *var2;
	struct obj *var1;
	int var3;
	var2 = tp->twp;
	if ((var2->flag & 0x400) == 0)
	{
		return;
	}
	var3 = (int)DAT_060eea88;
	var1 = (struct obj *)(*(int *)((char *)var3 + 0xcc));
	*(int *)((char *)var1->model->mats + 0xc) = var2->btimer;
	*(int *)((char *)var1->model->mats + 0x20) = var2->btimer;
	*(int *)((char *)var1->model->mats + 0x34) = var2->btimer;
	___njSetTexture(&texlist_ec_water);
	njPushMatrix(0);
	DAT_05b3df40 = -17952.0f;
	late_DrawObjectClip(var1, 0, 1.0f);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}
