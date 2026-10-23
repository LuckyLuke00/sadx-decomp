#include "decls.h"
extern struct task *DAT_060cca28;

// FUNCTION: SADX 0x007d9540
void CE101Factory_Draw(struct task *tp)
{
	njPushMatrix(0);
	FUN_0067d830(0, 0.0, 500.0, 0.0);
	draw_e101factory();
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007d9580
void E101Factory_Create()
{
	if (DAT_060cca28 == 0)
	{
		DAT_060cca28 = CreateElementalTask(0, 5, CE101Factory_Draw);
	}
}

// FUNCTION: SADX 0x007d95a0
void E101Factory_Delete()
{
	if (DAT_060cca28)
	{
		FreeTask(DAT_060cca28);
		DAT_060cca28 = 0;
	}
}
