#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006e78e0
void Chaos2BallExplode(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->counter.f = 0.0f;
		tp->disp = Chaos2BallExplodeDisplay;
		local_8->mode = 1;
	case 1:
		local_8->counter.f = local_8->counter.f + 0.2666666805744171f;
		if (local_8->counter.f >= 8.0f)
		{
			DestroyTask(tp);
			return;
		}
	}
	Chaos2BallExplodeDisplay(tp);
}

// FUNCTION: SADX 0x006e7c60
void Chaos2ColumnMain(struct task *tp)
{
	if (DAT_05b9d838 == 0)
	{
		Chaos2ColumnDispay(tp);
	}
}

// STUB: SADX 0x006e7c70
void Chaos2Column(struct task *tp)
{
}
