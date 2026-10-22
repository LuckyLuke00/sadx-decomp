#include "decls.h"

// FUNCTION: SADX 0x007e6e70
void FUN_007e6e70(void)
{
	SetInputP(0, 0x2c);
	switch (GetPlayerNumber())
	{
	case 2:
		CreateElementalTask(3, 2, MilesSnowBoard);
		break;
	case 0:
		CreateElementalTask(3, 2, SonicSnowBoard);
		break;
	}
}

// STUB: SADX 0x007e6fd0
void Rd_SandBoard(struct task *task_p)
{
}
