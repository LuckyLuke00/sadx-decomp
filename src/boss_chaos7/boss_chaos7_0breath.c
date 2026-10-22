#include "decls.h"

// STUB: SADX 0x006fedd0
void Chaos7BreathRipple(struct task *tp)
{
}

// FUNCTION: SADX 0x006ff2f0
void Chaos7BreathTame(struct task *tp)
{
	tp->exec = objNormalBT;
	tp->disp = objDisplayBT;
}
