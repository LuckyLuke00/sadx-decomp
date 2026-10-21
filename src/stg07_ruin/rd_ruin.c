#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// FUNCTION: SADX 0x0084ea40
void RuinBgmControl(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->btimer--;
	if (var1->btimer == 0)
	{
		ADXTaskInit();
		BGM_Play(var1->mode);
		DestroyTask(tp);
	}
}

// STUB: SADX 0x0084edb0
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0084ee80
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x0084f5c0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0084f640
void Bg_Ruin(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
