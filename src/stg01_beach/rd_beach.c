#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x007f5780
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x007f58d0
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x007f5d40
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x007f5dc0
void Bg_Beach(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
