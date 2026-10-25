#include "decls.h"

// FUNCTION: SADX 0x00903040
void EvChaos7Howl1()
{
	if (*(unsigned char *)((char *)DAT_05edd128) != 0xd)
	{
		DAT_05edd13c = 0xd;
		DAT_05edd131 = *(unsigned char *)((char *)DAT_05edd128);
	}
}

// FUNCTION: SADX 0x00903060
void EvChaos7Breath(float len)
{
	if (*(char *)DAT_05edd128 != 0x10)
	{
		DAT_05edd13c = 0x10;
		DAT_05edd131 = *(char *)DAT_05edd128;
		*(float *)((char *)DAT_05edd128 + 8) = len;
	}
}
