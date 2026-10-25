#include "decls.h"
struct playerwk *GetPlayerWorkPointer(unsigned char pno);
void PadReadOffP(unsigned char pno);
void FUN_004e2f70(int param_1, int param_2);
extern int DAT_05ba3328[8];

// FUNCTION: SADX 0x008c9d30
void MirenPlyInitPlayerPos(signed char player)
{
	struct taskwk *local_8;
	local_8 = (struct taskwk *)DAT_05baf368[player];
	if (local_8 != 0)
	{
		SetPlayerInitialPosition(local_8);
	}
}

// FUNCTION: SADX 0x008c9d60
void MirenPlyStopPlayer(signed char player)
{
	struct playerwk *local_8;
	PadReadOffP(player);
	local_8 = GetPlayerWorkPointer(player);
	FUN_004e2f70(DAT_05ba3328[player], (int)local_8);
}
