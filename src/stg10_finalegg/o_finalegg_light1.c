#include "decls.h"
static void DispATask(struct task *tp);
extern struct obj object_ligpfr_light01_light01[];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008913b0
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		late_DrawObjectClipEx(&object_ligpfr_light01_light01[0], 4, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00891440
void ObjectFinalEggLight1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			switch (var1->mode)
			{
			case 0:
				tp->disp = DispATask;
				tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
				tp->twp->mode = 1;
				break;
			case 1:
				DispATask(tp);
				break;
			}
		}
		else
		{
			switch (var1->mode)
			{
			case 1:
				DebPrintf(0x110010, "-> ROTATE X");
				DebPrintf(0x110011, "-> ROTATE Y");
				DebPrintf(0x110012, "-> ROTATE Z");
				DispATask(tp);
				break;
			case 0:
				tp->disp = DispATask;
				tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
				tp->twp->mode = 1;
				break;
			}
		}
	}
}
