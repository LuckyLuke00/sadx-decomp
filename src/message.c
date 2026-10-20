#include "decls.h"
extern void MSG_ThreadMainMessages(char **message);
extern struct thread *TH_Create(void *func, void *pParam, unsigned int stack_size);
void FUN_004c2fa0(struct MSGC *param_1, int param_2);
void FUN_005a4d70();
extern int DAT_05b92e28;
extern int DAT_05b9d838;
extern int DAT_05b42c24[4];
extern char DAT_05b42c1c;
int FUN_004c1800(const unsigned char *param_1);

extern signed char DAT_05b42c1d;
extern unsigned char DAT_05b42e20[0x50000];

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
	unsigned char local_11l;
	int local_10;

	local_cj = 0;
	for (local_8g = 0; local_8g < 0x18; local_8g++)
	{
		local_10 = 0;
		local_11l = *param_1;
		param_1 += 3;
		while (local_11l)
		{
			local_11l <<= 1;
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
		if (msgc->bitmap < DAT_05b42e20 || msgc->bitmap >= DAT_05b42e20 + sizeof(DAT_05b42e20))
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

// FUNCTION: SADX 0x004c26c0
void MSG_LF(struct MSGC *msgc)
{
	msgc->lx = 0;
	msgc->ly += msgc->sy + 0x18;
}

// FUNCTION: SADX 0x004c2e10
int FUN_004c2e10(int param_1)
{
	if (param_1 < 0)
	{
		param_1 = 0;
	}
	if (param_1 > 0xff)
	{
		param_1 = 0xff;
	}
	return param_1;
}

// FUNCTION: SADX 0x004c2ef0
void MSG_FadeIn(struct MSGC *msgc)
{
	int local_8;

	for (local_8 = 8; local_8 != 0; local_8--)
	{
		msgc->fc.argb.b = FUN_004c2e10(msgc->fc.argb.b + 0x20);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
}

// FUNCTION: SADX 0x004c2f40
void MSG_FadeOut(struct MSGC *msgc)
{
	int local_8;

	for (local_8 = 8; local_8 != 0; local_8--)
	{
		*(unsigned char *)((char *)msgc + 0x1f) = FUN_004c2e10(*(unsigned char *)((char *)msgc + 0x1f) - 0x20);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
	FUN_004c2fa0(msgc, 2);
}

// FUNCTION: SADX 0x004c2fa0
void FUN_004c2fa0(struct MSGC *param_1, int param_2)
{
	int local_8;
	for (local_8 = param_2; local_8 != 0; local_8 = local_8 + -1)
	{
		MSG_Disp(param_1);
		FUN_005a4d70();
	}
}

// STUB: SADX 0x004c2fe0
void MSG_WaitC(struct MSGC *msgc, int time)
{
}

// FUNCTION: SADX 0x004c3030
struct MSGC *NH_MSG_OpenMain(struct MSGC *msgc)
{
	return NH_MSG_Open(msgc, 0x46, 0x180, 0x1f4, 0x34, 0xd0000004, (char *)DAT_05b42e20);
}

// FUNCTION: SADX 0x004c3150
void MSG_MainMessages(char **message)
{
	DAT_05b42c1d = 1;
	TH_Create(MSG_ThreadMainMessages, message, 0);
}

// FUNCTION: SADX 0x004c3170
int MSG_CheckMainMessage()
{
	return DAT_05b42c1d;
}
