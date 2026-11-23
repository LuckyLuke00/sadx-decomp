#include "decls.h"

// GLOBAL: SADX 0x04ad7698
static struct CCL_INFO ColliInfo[1];

static void InitATask(struct task *tp);
static void DispATask(struct task *tp);

// FUNCTION: SADX 0x008a5880
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		DAT_05b3df40 = -37952.0f;
		late_DrawObjectClip((struct obj *)&object_fens_nc_fen_nc_fen, 1, 1.0f);
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008a5900
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->disp = DispATask;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	CCL_Init(tp, ColliInfo, 1, 4);
	var1->mode = 1;
}

// FUNCTION: SADX 0x008a5930
void ObjShelterFens(struct task *tp)
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
