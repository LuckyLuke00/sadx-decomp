#include "decls.h"

// GLOBAL: SADX 0x048a5bfc
static struct CCL_INFO ColliInfo[1];

static void InitATask(struct task *tp);
static void DispATask(struct task *tp);

// FUNCTION: SADX 0x00897110
static void DispATask(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawObjectClipMesh(object_hakidasi_hakidasi_hakidasi, 0, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00897180
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->disp = DispATask;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	CCL_Init(tp, ColliInfo, 1, 4);
	var1->mode = 1;
}

// FUNCTION: SADX 0x008971b0
void ObjectFinalEggHakidashi(struct task *tp)
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
