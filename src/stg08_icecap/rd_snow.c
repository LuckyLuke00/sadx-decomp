#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x0085af40
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0085b150
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x0085bae0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0085bb60
void Bg_Snow(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
