#include "decls.h"
extern int DAT_05b92e28;
extern int DAT_05b9d838;
extern int DAT_05b42c24[4];
extern char DAT_05b42c1c;
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

// FUNCTION: SADX 0x004c1800
int FUN_004c1800(const unsigned char *param_1)
{
	int local_8g;
	int local_cj;
	int local_10;
	unsigned char local_11l;

	local_cj = 0;
	for (local_8g = 0; local_8g < 0x18; local_8g++)
	{
		local_10 = 0;
		local_11l = *param_1;
		param_1 += 3;
		while (local_11l)
		{
			local_11l = local_11l << 1;
			local_10++;
		}
		if (local_cj < local_10)
		{
			local_cj = local_10;
		}
	}
	return local_cj;
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

// FUNCTION: SADX 0x004c1cf0
void MSG_Close(struct MSGC *msgc)
{
	if (msgc->texlist.textures != NULL)
	{
		FUN_004c1b70((char *)msgc);
	}
	if (msgc->bitmap != NULL)
	{
		if (msgc->bitmap < (void *)0x5b42e20 || msgc->bitmap > (void *)0x5b92e20)
		{
			Free(msgc->bitmap);
		}
		msgc->bitmap = NULL;
	}
}

// FUNCTION: SADX 0x004c1d50
void MSG_Disp(struct MSGC *msgc)
{
	if (msgc == 0)
	{
		DAT_05b92e28 = 0;
		return;
	}
	if (DAT_05b92e28 >= 4)
	{
		return;
	}
	if (msgc->kind == 1 && DAT_05b42c1c == 0)
	{
		return;
	}
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	DAT_05b42c24[DAT_05b92e28] = (int)msgc;
	DAT_05b92e28 = DAT_05b92e28 + 1;
}

// FUNCTION: SADX 0x004c3170
int MSG_CheckMainMessage()
{
	return DAT_05b42c1d;
}
