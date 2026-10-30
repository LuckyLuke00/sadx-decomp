#include "decls.h"
static void DispATask(struct task *tp);

// GLOBAL: SADX 0x026ed570
static struct CCL_INFO ColliInfo[3];


#pragma optimize("", off)
// STUB: SADX 0x00696a20
static void DispATask(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00696a90
void ObjectECLivingLight(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1 = tp->twp;
			tp->disp = DispATask;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			CCL_Init(tp, (struct CCL_INFO *)&ColliInfo, 3, 4);
			var1->mode = 1;
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
			var1 = tp->twp;
			tp->disp = DispATask;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			CCL_Init(tp, (struct CCL_INFO *)&ColliInfo, 3, 4);
			var1->mode = 1;
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
