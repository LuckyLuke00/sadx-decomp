#include "decls.h"
extern int DAT_05b9d838;
void HitMirror(struct task *tp);
extern unsigned char DAT_060d12bb;
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// STUB: SADX 0x0084f940
void HitMirror(struct task *tp)
{
}

// STUB: SADX 0x0084fa30
void DrawMirror(struct task *tp)
{
}

// FUNCTION: SADX 0x0084fb20
void DrawMrSnake(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawModelClip(model_lwobj_snake02_snake02, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0084ff90
void ChangeFogDensity(float dist, float density_speed, struct task *tp)
{
}

// STUB: SADX 0x00850010
void FogEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x008502d0
void DrawFogHasira(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	if (*(float *)((char *)var1 + 0x30) == (float)DAT_060d12bb)
	{
		___njFogDisable();
	}
	else
	{
		___njFogEnable();
	}
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (*(int *)((char *)var1 + 0x1c))
	{
		njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
	}
	if (var1->ang.x)
	{
		njRotateX(0, var1->ang.x);
	}
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawModelClip(model_l02_lightway_h_lightway_h, 1.0f);
	njPopMatrix(1);
	___njFogEnable();
}

// STUB: SADX 0x00850850
void ObjectRuinBigMirror(struct task *tp)
{
}

// STUB: SADX 0x00850b90
void ObjectRuinFogHasira(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			var1->mode = 1;
			CCL_Init(tp, (struct CCL_INFO *)0x043ac2ec, 1, 4);
			tp->disp = DrawFogHasira;
			break;
		case 1:
			if (FUN_004c39c0(tp) != 0)
			{
				njPrintC(0x110014, "<-AIM ID");
			}
			DrawFogHasira(tp);
			EntryColliList(var1);
			break;
	}
}
