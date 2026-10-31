#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern int DAT_05b9d838;
extern struct obj object_windobj_bridge_a2_bridge_a2[];
extern struct obj object_windobj_bridge_a3_bridge_a3[];
extern struct obj object_windobj_bridge_a4_bridge_a4[];
extern void ds_DrawObjectClip(struct obj *, float);
extern struct obj object_windobj_bridge_a1_bridge_a1[1];

// FUNCTION: SADX 0x0080d5c0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
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
		switch ((int)var1->scl.x)
		{
			case 0:
				ds_DrawObjectClip(&object_windobj_bridge_a1_bridge_a1[0], 1.0f);
				break;
			case 1:
				ds_DrawObjectClip(&object_windobj_bridge_a2_bridge_a2[0], 1.0f);
				break;
			case 2:
				ds_DrawObjectClip(&object_windobj_bridge_a3_bridge_a3[0], 1.0f);
				break;
			case 3:
				ds_DrawObjectClip(&object_windobj_bridge_a4_bridge_a4[0], 1.0f);
				break;
			default:
				ds_DrawObjectClip(&object_windobj_bridge_a1_bridge_a1[0], 1.0f);
				break;
		}
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0080d6a0
void DrawTest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
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
	___dsDrawObject(&object_windobj_bridge_a1_bridge_a1[0]);
	njPopMatrix(1);
}

// STUB: SADX 0x0080d9f0
void PieceInit(struct task *tp)
{
}

// STUB: SADX 0x0080dca0
void BrokenBridgePos(struct NJS_POINT3 *pos, int flag, struct task *tp)
{
}

// STUB: SADX 0x0080dfc0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0080e1a0
void ObjectWindyBridge(struct task *tp)
{
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = ExplosionRockDestructor;
}
