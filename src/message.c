#include "decls.h"
int FUN_004c2610(int param_1);
void FUN_004c2a30(struct MSGC *param_1, char *param_2);
extern unsigned char DAT_05b42e20[0x50000];
extern struct MSGC *DAT_05b92e20;
extern int DAT_05cd14d4;
extern unsigned int *DAT_05b93264;
extern int DAT_05b42c34;
extern int DAT_05b42c38;
extern int DAT_05b3ebbc;
struct BMPLANG {
	const unsigned char *transtable;
	const char *pitchdata;
	const char *bmpdata;
	const char *sbmpdata;
	unsigned char shifton;
	unsigned char shiftoff;
};
// GLOBAL: SADX 0x025d5978
static struct BMPLANG DAT_025d5978[6];
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
// GLOBAL: SADX 0x05b42e20
unsigned char DAT_05b42e20[0x50000] = {0};

// GLOBAL: SADX 0x05b92e20
struct MSGC *DAT_05b92e20 = 0;

// STUB: SADX 0x004c16c0
void FontInitialLoading()
{
}

// STUB: SADX 0x004c1790
int FPpCalcProp(const unsigned char *patt)
{
	return (int)0;
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

// STUB: SADX 0x004c1870
struct MSGC *MSG_Open(struct MSGC *msgc, int x, int y, int width, int height, unsigned long globalindex)
{
	return (struct MSGC *)0;
}

// FUNCTION: SADX 0x004c1a60
void MSG_LoadTexture(struct MSGC *msgc)
{
	msgc->msgc_flag |= 2;
}

// STUB: SADX 0x004c1a80
void MSG_LoadTexture2(struct MSGC *msgc)
{
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

// FUNCTION: SADX 0x004c22f0
void MSG_Cls(struct MSGC *msgc)
{
	unsigned short *local_8g;
	int local_cg;

	if (0 != msgc->bitmap)
	{
		local_8g = (unsigned short *)msgc->bitmap;
		for (local_cg = 0; local_cg < (msgc->buf_width2 * msgc->buf_height2); local_cg++)
		{
			*local_8g = 0;
			local_8g++;
		}
	}
	msgc->ly = 0;
	msgc->lx = 0;
	msgc->msgc_flag |= 1;
	DAT_05cd14d4 = 1;
	FUN_005a4d70();
	DAT_05cd14d4 = 0;
}

// STUB: SADX 0x004c2390
void *MSG_Font(int c)
{
	return (void *)0;
}

// FUNCTION: SADX 0x004c24e0
void *SOCMSG_Font(int c)
{
	int local_ci;
	int local_10m;
	int local_14;
	int local_8g;

	local_ci = DAT_025d5978[DAT_05b3ebbc].shifton & 0xff;
	local_8g = DAT_025d5978[DAT_05b3ebbc].shiftoff & 0xff;
	if (c < 0x100)
	{
		if (c > local_8g)
		{
			c -= local_8g - local_ci;
		}
		c -= 0x20;
		if (c < 0)
		{
			c = 0;
		}
		if (DAT_025d5978[DAT_05b3ebbc].transtable != 0)
		{
			c = DAT_025d5978[DAT_05b3ebbc].transtable[c] - 0x20;
		}
		return (void *)(DAT_05b42c34 + 0x9000 + c * 0x480);
	}
	else
	{
		if (DAT_025d5978[DAT_05b3ebbc].sbmpdata != 0)
		{
			local_10m = ((c >> 8) & 0xff);
			local_14 = (int)(c & 0xff);
			local_10m = local_10m - 0x81;
			if (local_14 <= 0x7e)
			{
				local_14 -= 0x40;
			}
			else
			{
				local_14 = local_14 - 0x41;
			}
			c = local_10m * 0xbc + local_14;
			return (void *)(c * 0x480 + DAT_05b42c38);
		}
		else
		{
			return (void *)DAT_05b42c34;
		}
	}
}

// FUNCTION: SADX 0x004c2610
int FUN_004c2610(int param_1)
{
	int local_cg;
	int local_8g;

	local_cg = DAT_025d5978[DAT_05b3ebbc].shifton & 0xff;
	local_8g = DAT_025d5978[DAT_05b3ebbc].shiftoff & 0xff;
	if (param_1 < 0x100)
	{
		if (param_1 > local_8g)
		{
			param_1 -= local_8g - local_cg;
		}
		if (DAT_025d5978[DAT_05b3ebbc].transtable != 0)
		{
			param_1 = DAT_025d5978[DAT_05b3ebbc].transtable[param_1 - 0x20];
		}
		return DAT_025d5978[DAT_05b3ebbc].pitchdata[param_1 - 0x20] + 1;
	}
	else
	{
		return 0x18;
	}
}

// FUNCTION: SADX 0x004c26c0
void MSG_LF(struct MSGC *msgc)
{
	msgc->lx = 0;
	msgc->ly += msgc->sy + 0x18;
}

// STUB: SADX 0x004c2940
void MSG_Puts(struct MSGC *msgc, char *str)
{
}

// STUB: SADX 0x004c2a30
void FUN_004c2a30(struct MSGC *param_1, char *param_2)
{
}

// STUB: SADX 0x004c2ad0
void MSG_PutsCenter(struct MSGC *msgc, char *str)
{
}

// STUB: SADX 0x004c2be0
void MSG_PutsBlockCenter(struct MSGC *msgc, char *str)
{
}

// FUNCTION: SADX 0x004c2d60
void MSG_WinFadeIn(struct MSGC *msgc)
{
	int local_8g;
	int local_cg;

	*(unsigned char *)((char *)msgc + 0x23) = 0;
	*(unsigned char *)((char *)msgc + 0x1f) = 0;
	local_8g = 0xa;
	for (; local_8g != 0; local_8g--)
	{
		*(unsigned char *)((char *)msgc + 0x23) = FUN_004c2e10(*(unsigned char *)((char *)msgc + 0x23) + 0xc);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
	*(unsigned char *)((char *)msgc + 0x23) = 0x80;
	local_cg = 0xa;
	for (; local_cg != 0; local_cg--)
	{
		*(unsigned char *)((char *)msgc + 0x1f) = FUN_004c2e10(*(unsigned char *)((char *)msgc + 0x1f) + 0x18);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
	*(unsigned char *)((char *)msgc + 0x1f) = 0xff;
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

// FUNCTION: SADX 0x004c2e40
void MSG_WinFadeOut(struct MSGC *msgc)
{
	int local_8g;
	int local_cg;

	local_8g = 0xa;
	for (; local_8g != 0; local_8g--)
	{
		*(unsigned char *)((char *)msgc + 0x1f) = FUN_004c2e10(*(unsigned char *)((char *)msgc + 0x1f) - 0x18);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
	*(unsigned char *)((char *)msgc + 0x1f) = 0;
	local_cg = 0xa;
	for (; local_cg != 0; local_cg--)
	{
		*(unsigned char *)((char *)msgc + 0x23) = FUN_004c2e10(*(unsigned char *)((char *)msgc + 0x23) - 0xc);
		MSG_Disp(msgc);
		FUN_005a4d70();
	}
	*(unsigned char *)((char *)msgc + 0x23) = 0;
	FUN_004c2fa0(msgc, 2);
}

// FUNCTION: SADX 0x004c2ef0
void MSG_FadeIn(struct MSGC *msgc)
{
	int local_8;

	for (local_8 = 8; local_8 != 0; local_8--)
	{
		msgc->fc.argb.a = FUN_004c2e10(msgc->fc.argb.a + 0x20);
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

// FUNCTION: SADX 0x004c2fe0
void MSG_WaitC(struct MSGC *msgc, int time)
{
	int local_8;
	for (local_8 = time; local_8 != 0; local_8 = local_8 + -1)
	{
		MSG_Disp(msgc);
		FUN_005a4d70();
		if ((DAT_05b93264[4] & 2) != 0)
		{
			break;
		}
	}
}

// FUNCTION: SADX 0x004c3030
struct MSGC *NH_MSG_OpenMain(struct MSGC *msgc)
{
	return NH_MSG_Open(msgc, 0x46, 0x180, 0x1f4, 0x34, 0xd0000004, (char *)DAT_05b42e20);
}

#pragma optimize("", off)
// STUB: SADX 0x004c3060
void MSG_ThreadMainMessages(char * *message)
{
}
#pragma optimize("", on)

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

#pragma optimize("", off)
// STUB: SADX 0x004c3180
struct MSGC *NH_MSG_Open(struct MSGC *msgc, int x, int y, int width, int height, unsigned long globalindex, char *buf)
{
	return (struct MSGC *)0;
}
#pragma optimize("", on)
