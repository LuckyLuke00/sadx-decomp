#include "decls.h"
int FUN_004c1800(const unsigned char *param_1);

extern signed char DAT_05b42c1d;

// FUNCTION: SADX 0x004c1790
int FPpCalcProp(const unsigned char *patt)
{
	int local_8;

	local_8 = FUN_004c1800(patt + 2);
	if (local_8 > 0)
	{
		local_8 += 0x10;
	}
	else
	{
		local_8 = FUN_004c1800(patt + 1);
		if (local_8 > 0)
		{
			local_8 += 8;
		}
		else
		{
			local_8 = FUN_004c1800(patt);
			if (local_8 > 0)
			{
			}
			else
			{
				local_8 = 0xc;
			}
		}
	}
	return local_8;
}

// FUNCTION: SADX 0x004c1a60
void MSG_LoadTexture(struct MSGC *msgc)
{
	msgc->msgc_flag |= 2;
}

// FUNCTION: SADX 0x004c1c10
void MSG_CloseRequestCls()
{
	FUN_004c1b70(0);
}

// FUNCTION: SADX 0x004c3170
int MSG_CheckMainMessage()
{
	return DAT_05b42c1d;
}
