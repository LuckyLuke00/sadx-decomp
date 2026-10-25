#include "decls.h"
void ObjectBeachWaveBG2(struct task *tp);
void Exec2(struct task *tp);
extern struct task *DAT_060ce9f4;

// FUNCTION: SADX 0x007f62d0
void DestructBeachWaveBG()
{
	FreeTask(DAT_060ce9f4);
}

// STUB: SADX 0x007f63b0
void Disp3(struct task *tp)
{
}

// STUB: SADX 0x007f6480
void Exec2(struct task *tp)
{
}

// STUB: SADX 0x007f6690
void ObjectBeachWaveBG2(struct task *tp)
{
}

// STUB: SADX 0x007f66d0
void ObjectBeachWaveBG3(struct task *tp)
{
}

// FUNCTION: SADX 0x007f6720
void CreateBeachWaveBG(long act)
{
	struct task *var1;
	struct taskwk *var2;
	if (act == 2)
	{
		var1 = CreateElementalTask(6, 6, ObjectBeachWaveBG2);
		DAT_060ce9f4 = var1;
		var2 = var1->twp;
		var2->mode = 2;
	}
	else if (act == 3)
	{
		var1 = CreateElementalTask(2, 6, ObjectBeachWaveBG3);
		var2 = var1->twp;
		DAT_060ce9f4 = var1;
		var2->mode = 3;
	}
}
