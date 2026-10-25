#include "decls.h"
static void Init(struct task *param_1, struct TENSHOUSEINFO *param_2);
extern struct TENSHOUSEINFO tensinfo[];

#pragma optimize("", off)
// STUB: SADX 0x00876e20
static void Init(struct task *tp, struct TENSHOUSEINFO *tensinfo)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00876f00
void ObjectCasinoTensS(struct task *tp)
{
	Init(tp, &tensinfo[0]);
}

// STUB: SADX 0x00876f20
void ObjectCasinoTensC(struct task *tp)
{
}
