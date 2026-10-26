#include "decls.h"

// FUNCTION: SADX 0x00817870
void dispPin(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(char *)var1 == 2)
		{
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
			}
		}
		if (var1->ang.y != 0)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00817ca0
void dispDoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_MODEL *var2 = (struct NJS_MODEL *)var1->counter.ptr;

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
	ds_DrawModelClip((struct NJS_MODEL *)var2->normals, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00818100
void dispPanel(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_MODEL *var2;
	struct NJS_MODEL *var3;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		SaveControl3D();
		njControl3D(0x10);
		SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
		FUN_00422560(3);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		njPushMatrix(NULL);
		var2 = (struct NJS_MODEL *)var1->counter.ptr;
		njTranslateV(NULL, (struct NJS_POINT3 *)((char *)var2 + 8));
		ds_DrawModelClip((struct NJS_MODEL *)var2->normals, 1.0f);
		njPopMatrix(1);
		njPushMatrix(NULL);
		var3 = (struct NJS_MODEL *)(*(int *)((char *)var2 + 0x2c));
		njTranslateV(NULL, (struct NJS_POINT3 *)((char *)var3 + 8));
		if (var1->value.ptr != 0)
		{
			njRotateY(NULL, (unsigned short)var1->value.ptr);
		}
		ds_DrawModelClip((struct NJS_MODEL *)var3->normals, 1.0f);
		njPopMatrix(1);
		njPopMatrix(1);
		npSetZCompare();
		ResetMaterial();
		LoadControl3D();
	}
}

// FUNCTION: SADX 0x00818850
void dispTPBall(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		___dsDrawObject((struct obj *)var1->counter.ptr);
		njPopMatrix(1);
	}
}
