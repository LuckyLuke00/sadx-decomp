#include "decls.h"
extern void *DAT_05cda188;
extern struct MSGC *DAT_05b92e20;
extern int DAT_05b3e388;
extern short DAT_05ccde90;
extern int DAT_05b3e0e0;
extern void voicevolresume();
extern void npSetZCompareMode(int flag);
extern void late_execCancel();
extern void BGM_RequestClear();
extern void Serif_RequestClear();
extern int dsStop_all();
extern void StopPCM(int ch);
extern void wmastop(int ch);
extern void Draw_Reset();
extern void InitMemory();
extern void InitTask();
extern void ReleaseModule(unsigned long u32ModuleType);
extern void l_edit_Init();
extern void ___njFogEnable();
extern "C" void srand(unsigned int param_1);
extern void MSG_Disp(struct MSGC *msgc);
extern int DAT_05b3e05c;
extern int DAT_05b3e070;
void FUN_004addf0();
void ADX_Init();
int le_load_stagelight();
void FUN_004c3310(int *param_1);
extern int DAT_05b3e38c;
extern int DAT_05b3e06c;
extern unsigned short DAT_05b3e00e;
extern unsigned short DAT_05b3e010;
extern int DAT_05b3e018;
extern int DAT_05b3e390;
extern int DAT_05b3dff8[4];

// FUNCTION: SADX 0x004ac820
void DialogJimakuInit()
{
	if (DAT_05b3e38c == 0)
	{
		DAT_05b3e38c = (int)syMalloc(0x40040);
		DAT_05b3e06c = 0;
		NH_MSG_Open((struct MSGC *)DAT_05b3dff8, 0x40, 0x190, 0x200, 0x28, 0xd0000030, (char *)DAT_05b3e38c);
		DAT_05b3e00e = 0;
		DAT_05b3e010 = 0;
		DAT_05b3e018 = 0x80000000;
		DAT_05b3e390 = 1;
	}
}

// FUNCTION: SADX 0x004ac8a0
void DialogJimakuEnd()
{
	if (DAT_05b3e390 > 0)
	{
		DAT_05b3e390 = DAT_05b3e390 - 1;
	}
	if (DAT_05b3e38c != 0 && DAT_05b3e390 == 0)
	{
		FUN_004c3310(DAT_05b3dff8);
		syFree((void *)DAT_05b3e38c);
		DAT_05b3e38c = 0;
	}
}

// FUNCTION: SADX 0x004ac900
void DialogJimakuPut(char *str)
{
	if (!DAT_05b3e38c)
	{
		return;
	}
	if (!str)
	{
		return;
	}
	if (!*str)
	{
		return;
	}
	DAT_05b3e390 = 2;
	if ((char *)DAT_05b3e06c != str)
	{
		MSG_Cls((struct MSGC *)&DAT_05b3dff8[0]);
		MSG_Puts((struct MSGC *)&DAT_05b3dff8[0], str);
		MSG_LoadTexture((struct MSGC *)&DAT_05b3dff8[0]);
		DAT_05b3e06c = (int)str;
	}
	MSG_Disp((struct MSGC *)&DAT_05b3dff8[0]);
}

// FUNCTION: SADX 0x004ac980
void njUserInit()
{
	FUN_004addf0();
	DAT_05b3e05c = 0;
	ADX_Init();
	DAT_05b3e070 = 0;
	le_load_stagelight();
}

// FUNCTION: SADX 0x004adc90
void FUN_004adc90(void)
{
	EndPlaySound();
	Clear();
}

// FUNCTION: SADX 0x004adca0
void Clear()
{
	ReleaseTextureForEachGameMode();
	ReleaseAllPlayersTexture();
	njExitTexture();
}

// FUNCTION: SADX 0x004adcc0
void Reset()
{
	unsigned int local_8;
	voicevolresume();
	npSetZCompareMode(1);
	pdVibMxStop(0);
	DAT_05b3e388 = 0;
	DAT_05ccde90 = 0;
	late_execCancel();
	BGM_RequestClear();
	Serif_RequestClear();
	dsStop_all();
	StopPCM(-1);
	wmastop(0);
	wmastop(1);
	Draw_Reset();
	MSG_Disp(0);
	InitMemory();
	InitTask();
	for (local_8 = 0; local_8 <= 9; local_8++)
	{
		ReleaseModule(local_8);
	}
	l_edit_Init();
	if (DAT_05cda188 != 0)
	{
		syFree(DAT_05cda188);
		DAT_05cda188 = 0;
	}
	if (DAT_05b92e20 != 0)
	{
		syFree(DAT_05b92e20);
		DAT_05b92e20 = 0;
	}
	FUN_005b5aa0(-1);
	FUN_005b5aa0(0xff12);
	FUN_005b5aa0(&DAT_05b3e0e0);
	FUN_005b5aa0(&DAT_05b3e0e0);
	___njFogEnable();
	srand(0xdead0cab);
}
