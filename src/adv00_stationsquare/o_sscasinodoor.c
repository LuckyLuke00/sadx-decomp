#include "decls.h"

// GLOBAL: SADX 0x026dd1e0
static struct CCL_INFO object_c_info[5];

static void Exec(struct task *tp);
static void Disp(struct task *tp);
static long SeqCheck();

#pragma optimize("", off)
// STUB: SADX 0x00688960
static long SeqCheck()
{
	return (long)0;
}
#pragma optimize("", on)

// STUB: SADX 0x00688b00
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00688c20
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00688d80
void ObjectSSCasinodoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if ((unsigned char)DAT_05b9d744 != 1)
	{
		njPrintC(0xa0008, "ACT CASINO ONLY !");
		return;
	}
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	var1->value.f = 0;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->smode = 0;
	var1->btimer = 0;
	if (!FUN_004c39c0(tp))
	{
		if (SeqCheck())
		{
			var1->mode = 4;
			var1->counter.f = 1;
		}
		else
		{
			var1->mode = 0;
			var1->counter.f = 0;
		}
		CCL_Init(tp, object_c_info, 5, 4);
	}
	tp->exec = Exec;
	tp->disp = Disp;
}
