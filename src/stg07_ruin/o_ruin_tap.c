#include "decls.h"
static void Draw(struct task *tp);
extern struct CCL_INFO tap_c_info[1];
void FUN_00853a90();
extern int DAT_05b9d838;
extern struct NJS_MODEL model_lwobj_snake00_snake00[];
extern struct obj object_lwobj_s_water_s_water[];
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00853ae0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
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
		ds_DrawModelClip((struct NJS_MODEL *)&model_lwobj_snake00_snake00, 1.0f);
		late_DrawObjectClipMesh((struct obj *)&object_lwobj_s_water_s_water, 0, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00853ba0
void ObjectRuinTap(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			CCL_Init(tp, &tap_c_info[0], 1, 4);
			var1->mode = 1;
			break;
		case 1:
			FUN_00853a90();
			Draw(tp);
			EntryColliList(var1);
			break;
		}
	}
}
