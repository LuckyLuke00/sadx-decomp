#include "decls.h"
struct SAVE_DATA *GetSDp();
extern int DAT_05cccef4[7];
extern unsigned char DAT_05cd14ed;
extern char DAT_05ccca18;

// FUNCTION: SADX 0x005a4170
struct SAVE_DATA *GetSDp()
{
	return (struct SAVE_DATA *)&DAT_05ccca18;
}

// FUNCTION: SADX 0x005a4180
signed char AvaGetOnseiSettei()
{
	struct SAVE_DATA *local_8g;
	local_8g = GetSDp();
	return (signed char)((*(char *)((char *)local_8g + 0x251) & 2) >> 1);
}

// FUNCTION: SADX 0x005a41a0
void AvaSetOnseiSettei(signed char bit)
{
	struct SAVE_DATA *local_8g;

	local_8g = GetSDp();
	if (bit)
	{
		*(signed char *)((char *)local_8g + 0x251) |= 2;
	}
	else
	{
		*(signed char *)((char *)local_8g + 0x251) &= 0xfd;
	}
}

// STUB: SADX 0x005a41f0
signed char AvaGetVoiceSettei()
{
	return (signed char)0;
}

// FUNCTION: SADX 0x005a4240
void AvaSetVoiceSettei(signed char bit)
{
	struct SAVE_DATA *local_8g;

	local_8g = GetSDp();
	*(char *)((char *)local_8g + 0x251) = *(char *)((char *)local_8g + 0x251) & (char)0xf3;
	if (bit == 0)
	{
		*(char *)((char *)local_8g + 0x251) = *(char *)((char *)local_8g + 0x251) | 4;
	}
	else
	{
		*(char *)((char *)local_8g + 0x251) = *(char *)((char *)local_8g + 0x251) | 8;
	}
}

// STUB: SADX 0x005a42a0
signed char AvaGetTextSettei()
{
	return (signed char)0;
}

// FUNCTION: SADX 0x005a42f0
void AvaSetTextSettei(signed char bit)
{
	struct SAVE_DATA *local_8;
	local_8 = GetSDp();
	bit++;
	bit = (signed char)(bit & 7);
	bit = (signed char)(bit << 4);
	*(char *)((char *)local_8 + 0x251) &= (char)0x8f;
	*(char *)((char *)local_8 + 0x251) |= bit;
}

// STUB: SADX 0x005a4350
enum AvaSerifuChEnum AvaGetLastPlayerForSerifu()
{
	return (enum AvaSerifuChEnum)0;
}

// STUB: SADX 0x005a4400
enum AvaCharEnum AvaGetlastPlayer()
{
	return (enum AvaCharEnum)0;
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

// FUNCTION: SADX 0x005a4560
long AvaGetTrialBestScore(enum AvaCharEnum chnum, unsigned char stg)
{
	struct SAVE_DATA *local_8g;
	int local_cj;
	long local_10;

	local_8g = GetSDp();
	if (DAT_05cd14ed == 6)
	{
		local_10 = DAT_05cccef4[stg];
	}
	else
	{
		local_cj = serch_stg_from_stgactprm(stg, chnum);
		local_cj = FUN_005a4640(chnum) + local_cj;
		local_10 = *(int *)((char *)local_8g + 8 + local_cj * 4);
	}
	return local_10;
}

// STUB: SADX 0x005a45d0
unsigned char serch_stg_from_stgactprm(unsigned char stg, enum AvaCharEnum chnum)
{
	return (unsigned char)0;
}

// STUB: SADX 0x005a4640
int FUN_005a4640(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x005a46d0
long AvaGetTrialWeight(unsigned char stg)
{
	struct SAVE_DATA *local_8g;
	int local_cj;
	int local_10;

	local_8g = GetSDp();
	local_cj = serch_stg_from_stgactprm(stg, AVA_BIG);
	local_10 = *(short *)((char *)local_8g + 0xdc + local_cj * 6) * 10;
	return local_10;
}

// STUB: SADX 0x005a4720
void AvaGetTrialBestClearTime(struct CLEAR_TIME *ctp, enum AvaCharEnum chnum, unsigned char stg)
{
}

// STUB: SADX 0x005a47b0
short AvaGetTrialBestRing(enum AvaCharEnum chnum, unsigned char stg)
{
	return (short)0;
}

// FUNCTION: SADX 0x005a4820
enum AvaMiniStgAtrEnum AvaIsMiniGameStgTime(enum AvaCharEnum chnum, unsigned char stg)
{
	int local_8g;

	local_8g = 0;
	if (stg == 0x23)
	{
		local_8g = 1;
	}
	switch (chnum)
	{
	case AVA_SONIC:
		if (stg == 0x16)
		{
			local_8g = 2;
		}
		break;
	case AVA_MILES:
		if (stg == 0x15)
		{
			local_8g = 2;
		}
		break;
	case AVA_KNUCKLES:
		if (stg == 0x12)
		{
			local_8g = 2;
		}
		break;
	case AVA_AMY:
		if (stg == 0x17)
		{
			local_8g = 2;
		}
		break;
	case AVA_BIG:
		if (stg == 0x12)
		{
			local_8g = 2;
		}
		break;
	case AVA_E_102:
		if (stg == 0x19)
		{
			local_8g = 2;
		}
		break;
	case AVA_SUPERSONIC:
		if (stg == 0x16)
		{
			local_8g = 2;
		}
		break;
	}
	return (enum AvaMiniStgAtrEnum)local_8g;
}

// STUB: SADX 0x005a4900
void AvaGetMiniGameCartTime(struct CLEAR_TIME *ctp, enum AvaCharEnum chnum, unsigned char stg, int rank)
{
}

// STUB: SADX 0x005a4970
void AvaGetMiniGameBossTime(struct CLEAR_TIME *ctp, enum AvaCharEnum chnum, unsigned char stg, int rank)
{
}

// STUB: SADX 0x005a49e0
long AvaGetMiniGameScore(enum AvaCharEnum chnum, unsigned char stg, int rank)
{
	return (long)0;
}
