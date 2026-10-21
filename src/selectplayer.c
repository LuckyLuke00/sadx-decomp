#include "decls.h"
extern short DAT_05cda184;
extern short DAT_05cda180;

// FUNCTION: SADX 0x0059bfd0
short SelectPlayer()
{
	GetSwitchData();
	LoopTask();
	if (FUN_004c39c0(0) != 0)
	{
		GenocideTask();
		return -2;
	}
	return DAT_05cda180;
}

// FUNCTION: SADX 0x0059c000
void SelectPlayerInit()
{
	InitMemory();
	InitTask();
	CreateElementalTask(2, 1, SelectPlayerManager);
	PadReadOff();
	DAT_05cda180 = 0;
	DAT_05cda184 = 6;
}

// STUB: SADX 0x0059c4e0
void DisplaySelectedCharacter(struct task *tp)
{
}
