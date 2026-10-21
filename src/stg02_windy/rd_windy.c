#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x00803fa0
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x008044d0
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x00804a50
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x00804ad0
void Bg_Windy(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
