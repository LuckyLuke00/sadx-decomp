#include "decls.h"
extern struct NJS_MODEL model_wvobj_ha_red_ha_red[1];
extern struct NJS_MODEL model_wvobj_ha_yellow_ha_yellow[1];
extern struct NJS_MODEL model_wvobj_ha_green_ha_green[1];
extern struct NJS_TEXLIST texlist_e_sai;
extern struct obj object_rhino;
extern int DAT_05b9d838;
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);

// FUNCTION: SADX 0x00804af0
void DrawLeaf(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		int var2 = (int)*(float *)((char *)var1 + 0x34);
		switch (var2)
		{
		case 0:
			late_DrawModelClip(&model_wvobj_ha_yellow_ha_yellow[0], 1, 1.0f);
			break;
		case 1:
			late_DrawModelClip(&model_wvobj_ha_green_ha_green[0], 1, 1.0f);
			break;
		default:
			late_DrawModelClip(&model_wvobj_ha_red_ha_red[0], 1, 1.0f);
			break;
		}
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00804bc0
void DrawSai(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_e_sai);
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		late_DrawObjectClip(&object_rhino, 1, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008052e0
void ObjectWindySetSmoke(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 vec;
	struct task *var2;
	vec.x = 5.0f;
	vec.y = 4.0f;
	vec.z = 2.0f;
	switch (var1->mode)
	{
		case 0:
			var1->mode = 1;
			break;
		case 1:
			var1->btimer++;
			vec.x += var1->scl.x;
			vec.y += var1->scl.x;
			vec.z += var1->scl.x;
			if (var1->btimer > 0xf)
			{
				var1->btimer = 0;
				CreateSmoke(&var1->pos, &vec, var1->scl.y + 10.0f);
				var2 = CreateElementalTask(2, 5, ObjectWindyTorLeaf);
				if (var2 != 0)
				{
					var2->twp->pos.x = var1->pos.x;
					var2->twp->pos.y = var1->pos.y;
					var2->twp->pos.z = var1->pos.z;
				}
			}
			break;
	}
}
