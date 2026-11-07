#include "decls.h"
void __fastcall FUN_00713b10(enum eCHAO_STAGE_NUMBER param_1);

// FUNCTION: SADX 0x00713ab0
int AL_SeqGetPlayerId()
{
	struct taskwk *var1 = DAT_05baf368[0];
	int var2 = -1;
	switch (var1->counter.b[1])
	{
	case 0:
		var2 = 0;
		break;
	case 2:
		var2 = 1;
		break;
	case 3:
		var2 = 2;
		break;
	case 5:
		var2 = 3;
		break;
	case 6:
		var2 = 4;
		break;
	case 7:
		var2 = 5;
		break;
	}
	return var2;
}

#pragma optimize("", off)
// STUB: SADX 0x00713b10
void __fastcall FUN_00713b10(enum eCHAO_STAGE_NUMBER param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00713b30
void FUN_00713b30()
{
	FUN_00713b10(AL_GetStageNumber());
}

// STUB: SADX 0x00713b40
long AL_SeqCanIWarp(enum eCHAO_STAGE_NUMBER stage)
{
	return (long)0;
}

// STUB: SADX 0x00713b90
void AL_SeqArrive()
{
}
