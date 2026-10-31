#include "decls.h"
static void Init(struct task *tp);
static void Exec(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060dd3c0;
extern int DAT_060dd3c4;

// STUB: SADX 0x008a2ee0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008a3100
static void Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->wtimer = (DAT_05b9d724 << 8) | DAT_05b9d744;
	tp->exec = Exec;
	tp->dest = Exec;
}

// FUNCTION: SADX 0x008a3130
void InitTunnelManager()
{
	DAT_060dd3c0 = 0;
	FUN_0058b860(0x10, 0);
	DAT_060dd3c4 = 0;
	CreateElementalTask(2, 3, Init);
}
