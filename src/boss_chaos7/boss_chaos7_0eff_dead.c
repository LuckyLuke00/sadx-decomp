#include "decls.h"
static void Normal2(struct task *tp);
static void Normal1(struct task *pTask);

// STUB: SADX 0x00700f90
void Display1(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00701080
static void Normal1(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00701110
void Chaos7DeadEffect1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->value.f = 0.0f;
	var1->counter.f = 0.0f;
	tp->exec = Normal1;
	tp->disp = Display1;
}

// STUB: SADX 0x00701130
void Display2(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00701220
static void Normal2(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007012b0
void Chaos7DeadEffect2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->value.f = 0.0f;
	var1->counter.f = 0.0f;
	tp->exec = Normal2;
	tp->disp = Display2;
}

#pragma optimize("", off)
// STUB: SADX 0x007012d0
void Display3(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007013d0
void Normal3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.f < 8.0f)
	{
		var1->value.f = var1->counter.f * 0.125f;
	}
	else if (var1->counter.f > 20.0f)
	{
		var1->value.f = (31.0f - var1->counter.f) / 11.0f;
	}
	else
	{
		var1->value.f = 1.0f;
	}
	var1->timer.b[0]++;
	if (var1->timer.b[0] >= 2)
	{
		var1->timer.b[1]++;
		var1->timer.b[0] = 0;
		if (var1->timer.b[1] >= 8)
		{
			var1->timer.b[1] = 0;
		}
	}
	var1->counter.f += 0.25833332f;
	if (var1->counter.f >= 31.0f)
	{
		var1->timer.b[2]--;
		if (var1->timer.b[2] > 0)
		{
			var1->counter.f = 0.0f;
		}
		else
		{
			FreeTask(tp);
			return;
		}
	}
	*(long *)((char *)var1 + 0x18) += 0x100;
	Display3(tp);
}

// FUNCTION: SADX 0x00701480
void Chaos7DeadEffect3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->exec = Normal3;
	tp->disp = Display3;
	var1->value.f = 0.0f;
	*(float *)((char *)var1 + 8) = 0.0f;
	var1->timer.b[2] = 2;
}
