#include "decls.h"

// STUB: SADX 0x008b3430
void Pasya0Disp(struct task *tp)
{
}

// STUB: SADX 0x008b34e0
void Pasya1Disp(struct task *tp)
{
}

// STUB: SADX 0x008b3590
void Pasya0Exec(struct task *tp)
{
}

// STUB: SADX 0x008b3670
void Pasya1Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b3740
void Pasya0Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y -= 2.0;
	var1->btimer = 0;
	var1->wtimer = 0;
	tp->exec = Pasya0Exec;
	tp->disp = Pasya0Disp;
}

// STUB: SADX 0x008b3770
void Pasya1Init(struct task *tp)
{
}
