#include "decls.h"
extern int DAT_060bb24c;
extern int DAT_060bb1d0;
extern long adx_table[10];
void Serif_Play(int no);

// FUNCTION: SADX 0x006cdd40
void __fastcall FUN_006cdd40(int param_1)
{
	if (DAT_060bb24c == 0)
	{
		DAT_060bb1d0 |= 1 << param_1;
		Serif_Play(adx_table[param_1]);
	}
}

// FUNCTION: SADX 0x006cdd70
void __fastcall FUN_006cdd70(int param_1)
{
	if (DAT_060bb24c == 0)
	{
		int var1 = 1 << param_1;
		if ((DAT_060bb1d0 & var1) == 0)
		{
			DAT_060bb1d0 = DAT_060bb1d0 | var1;
			Serif_Play(adx_table[param_1]);
		}
	}
}
