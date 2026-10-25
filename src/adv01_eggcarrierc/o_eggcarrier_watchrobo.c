#include "decls.h"
static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x006a3ca0
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006a4110
void ExecOnEdit(struct task *tp)
{
	struct taskwk *var1;
	float var2;
	var1 = tp->twp;
	var2 = *(float *)((char *)var1 + 0x34) + var1->counter.f;
	var1->counter.f = var2;
	if (var2 >= 13.989999771118164)
	{
		var1->counter.f = 0.0f;
	}
	njPrintC(0x110013, "-> MOVE RANGE");
	njPrintC(0x110014, "-> MOVE SPEED");
	njPrintC(0x110015, "-> ANIME SPEED");
	Draw(tp);
}
