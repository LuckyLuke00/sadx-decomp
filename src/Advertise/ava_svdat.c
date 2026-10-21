#include "decls.h"

// STUB: SADX 0x005a42f0
void AvaSetTextSettei(signed char bit)
{
}

// STUB: SADX 0x005a4490
unsigned char AvaGetStartChiten(enum AvaCharEnum chnum)
{
	return (unsigned char)0;
}

// FUNCTION: SADX 0x005a4500
unsigned char AvaGetSaishuuClear()
{
	struct SAVE_DATA *local_8g;
	unsigned char local_9;
	local_8g = GetSDp();
	local_9 = *(unsigned char *)((char *)local_8g + 0x25c);
	return local_9;
}

// FUNCTION: SADX 0x005a4530
long AvaGetPlayTime()
{
	struct SAVE_DATA *local_8g;
	int local_cg;

	local_8g = GetSDp();
	local_cg = *(int *)((char *)local_8g + 4);
	local_cg /= 0xe10;
	return local_cg;
}

// STUB: SADX 0x005a45d0
unsigned char serch_stg_from_stgactprm(unsigned char stg, enum AvaCharEnum chnum)
{
	return (unsigned char)0;
}

// STUB: SADX 0x005a46d0
long AvaGetTrialWeight(unsigned char stg)
{
	return (long)0;
}

// STUB: SADX 0x005a47b0
short AvaGetTrialBestRing(enum AvaCharEnum chnum, unsigned char stg)
{
	return (short)0;
}

// STUB: SADX 0x005a4900
void AvaGetMiniGameCartTime(struct CLEAR_TIME *ctp, enum AvaCharEnum chnum, unsigned char stg, int rank)
{
}

// STUB: SADX 0x005a4970
void AvaGetMiniGameBossTime(struct CLEAR_TIME *ctp, enum AvaCharEnum chnum, unsigned char stg, int rank)
{
}
