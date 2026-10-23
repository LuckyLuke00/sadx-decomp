#include "decls.h"
extern struct TENSHOUSEINFO tensinfo[];

// FUNCTION: SADX 0x00876f00
void ObjectCasinoTensS(struct task *tp)
{
	Init(tp, &tensinfo[0]);
}

// FUNCTION: SADX 0x00876f20
void ObjectCasinoTensC(struct task *tp)
{
	Init(tp, (struct TENSHOUSEINFO *)0x480b7f8);
}
