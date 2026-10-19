#include "decls.h"

extern unsigned char DAT_05b92ec8[768];
extern unsigned char *DAT_05b92e30;
extern unsigned char DAT_05b92e54;
extern unsigned char DAT_05b92e55;
extern unsigned char DAT_05b92e56;

// FUNCTION: SADX 0x004c4e50
void FUN_004c4e50()
{
	int local_8;

	for (local_8 = 0; local_8 < 256; local_8++)
	{
		DAT_05b92ec8[local_8 * 3 + 1] = DAT_05b92ec8[local_8 * 3];
		DAT_05b92ec8[local_8 * 3] = 0;
	}
	for (local_8 = 0; local_8 < 6; local_8++)
	{
		DAT_05b92ec8[DAT_05b92e30[local_8 + 2] * 3] = 1;
	}
	for (local_8 = 0; local_8 < 256; local_8++)
	{
		DAT_05b92ec8[local_8 * 3 + 2] = (DAT_05b92ec8[local_8 * 3] ^ DAT_05b92ec8[local_8 * 3 + 1]) & DAT_05b92ec8[local_8 * 3];
	}
	DAT_05b92e55 = DAT_05b92e54;
	DAT_05b92e54 = *DAT_05b92e30;
	DAT_05b92e56 = (DAT_05b92e54 ^ DAT_05b92e55) & DAT_05b92e54;
}

// FUNCTION: SADX 0x004c4f60
void FUN_004c4f60()
{
	if (NP_ChkStageChaoGarden() == 1)
	{
		action_button = 2;
		hold_button = 0x402;
	}
	else
	{
		action_button = 0x402;
		hold_button = 0x402;
	}
}
