#include "decls.h"
extern "C" int rand(void);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00818f40
void dispTPBarrel(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	FUN_0067d2d0(0, 3.0f, 3.0f, 3.0f);
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 3.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00819000
void destTPBarrel(struct task *tp)
{
	dsStop_num(0x3bf);
}

// FUNCTION: SADX 0x00819010
void dispTPBrokenBarrel(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
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
	FUN_0067d2d0((float *)0, 3.0f, 3.0f, 3.0f);
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 3.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00819230
void createBarrelSpark(struct task *tp)
{
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;

	local_20 = tp->twp->pos;
	local_20.y += 20.0;
	local_14.x = (float)rand() * 0.000030517578125;
	local_14.x = (local_14.x - 0.5f) * 1.2f;
	local_14.y = (float)rand() * 0.000030517578125;
	local_14.y = (local_14.y + 0.2f) * 0.9f;
	local_14.z = (float)rand() * 0.000030517578125;
	local_14.z = (local_14.z - 0.5f) * 1.2f;
	CreateSpark(&local_20, &local_14, 1.0f);
}
