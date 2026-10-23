#include "decls.h"
extern unsigned short DAT_05cd296c;
extern int DAT_05cd297c;

// STUB: SADX 0x009058b0
void FUN_009058b0(struct task *tp)
{
}

// FUNCTION: SADX 0x00906150
void FUN_00906150(void)
{
	DAT_05cd297c += 1;
	if (DAT_05cd296c & 0x20)
	{
		DAT_05cd297c += 1;
	}
}

// STUB: SADX 0x00906200
void FUN_00906200(struct task *param_1)
{
}

// STUB: SADX 0x00906290
void FUN_00906290(struct task *tp)
{
}

// FUNCTION: SADX 0x00906cc0
void sakana00(struct task *tp)
{
	SakanaGenerater(tp);
}
