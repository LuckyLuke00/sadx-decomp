#include "decls.h"

// FUNCTION: SADX 0x00687c80
void exitSSCard(struct task *tp)
{
	tp->ocp->ssCondition &= 0xbfff;
}
