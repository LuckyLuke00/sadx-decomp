#include "decls.h"
extern struct obj object_fun_test_funkaball_funkaball;
extern void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
extern void njRotateZ(float *param_1, int param_2);

// STUB: SADX 0x00828ab0
void DisplayStone(struct task *tp)
{
}

// FUNCTION: SADX 0x00832500
void DisplayLavaBall(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	struct motionwk *local_c = tp->mwp;
	if (dsCheckViewV(&local_8->pos, 8.0f) != 0)
	{
		SetMaterial(1.0f, local_c->acc.x, local_c->acc.y, local_c->acc.z);
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &local_8->pos);
		if (local_8->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)local_8->ang.z);
		}
		if (local_8->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)local_8->ang.x);
		}
		if (local_8->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)local_8->ang.y);
		}
		FUN_0067d2d0(NULL, local_c->rad, local_c->rad, local_c->rad);
		ds_DrawObjectClip(&object_fun_test_funkaball_funkaball, local_c->rad);
		njPopMatrix(1);
		SetMaterial(1.0f, 0.0f, 0.0f, 0.0f);
	}
}

// STUB: SADX 0x00832a30
void ColliEruptExplosion(struct task *tp)
{
}
