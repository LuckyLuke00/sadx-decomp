#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x0081a250
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0081a3b0
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x0081a8a0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0081a920
void Bg_Highway(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
