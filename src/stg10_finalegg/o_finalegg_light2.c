#include "decls.h"

// GLOBAL: SADX 0x048a5750
static struct CCL_INFO ColliInfo[1];

static void InitATask(struct task *tp);
static void DispATask(struct task *tp);

// FUNCTION: SADX 0x00891240
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (Uint16)var1->ang.y);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (Uint16)var1->ang.x);
		}
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (Uint16)var1->ang.z);
		}
		late_DrawObjectClipEx(&object_bl_nc_bllight_nc_bllight[0], 4, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008912d0
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->disp = DispATask;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	CCL_Init(tp, ColliInfo, 1, 4);
	var1->mode = 1;
}

// FUNCTION: SADX 0x00891300
void ObjectFinalEggLight2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			switch (var1->mode)
			{
			case 0:
				InitATask(tp);
				break;
			case 1:
				DispATask(tp);
				EntryColliList(tp->twp);
				break;
			}
		}
		else
		{
			switch (var1->mode)
			{
			case 0:
				InitATask(tp);
				break;
			case 1:
				DebPrintf(0x110010, "-> ROTATE X");
				DebPrintf(0x110011, "-> ROTATE Y");
				DebPrintf(0x110012, "-> ROTATE Z");
				DispATask(tp);
				EntryColliList(tp->twp);
				break;
			}
		}
	}
}
