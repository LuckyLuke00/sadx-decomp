#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

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
