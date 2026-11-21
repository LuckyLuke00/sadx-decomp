#include "decls.h"
#include <windows.h>
#include "advertise.h"
extern int DAT_05a92378;
extern unsigned char DAT_05ab834c;
extern float DAT_05ab4248;
extern int DAT_05b9d854;
extern unsigned char DAT_05cc3636;
extern unsigned char DAT_05cc3631;
extern unsigned long DAT_05b3e338;
extern unsigned long DAT_05b3e33c;
extern unsigned char DAT_05b3e354;
extern unsigned char DAT_05b3e357;
extern struct MSGC DAT_05b3e088;
extern Magic::RenderCore::Texture *DAT_05b3e360;
extern Magic::RenderCore::Texture *DAT_05b3e364;
extern Magic::RenderCore::Texture *DAT_05b3e368;
extern Magic::RenderCore::Texture *DAT_05b3e370;
extern Magic::RenderCore::Texture *DAT_05b3e374;
extern Magic::RenderCore::Texture *DAT_05b3e380;
extern int DAT_05b3e058;
extern int DAT_05b3e060;
void FUN_007d21b0(...);
void FUN_004cb840();
void FUN_0056a5d0();
void FUN_00573280(int param_1);
void FUN_004ade40();
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

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004abe70
void _prolog()
{
	njUserInit();
	DAT_05b3e0d8 = 0;
	FUN_005b5aa0();
	if (!DAT_05b3e370)
	{
		SOCFileStream local_b4;

		if (local_b4.ReadFile("system\\DC\\DC_Title2.dds"))
		{
			DAT_05b3e370 = new Magic::RenderCore::Texture;
			DAT_05b3e370->Load(local_b4.FUN_00424960(), 1, local_b4.FUN_0040b8a0(), 0, 1, 0);
		}
	}
	if (!DAT_05b3e374)
	{
		SOCFileStream local_bc;

		if (local_bc.ReadFile("system\\DC\\DC_Title0.dds"))
		{
			DAT_05b3e374 = new Magic::RenderCore::Texture;
			DAT_05b3e374->Load(local_bc.FUN_00424960(), 1, local_bc.FUN_0040b8a0(), 0, 1, 0);
		}
	}
	npSetZCompareMode(1);

	const int local_a0h = 45;
	const int local_ac = 16;
	const int local_50p = 356;
	int local_9c = 0;
	int local_54h = 0;
	int local_a4k = 0;
	int local_a8i = 0;
	int local_98g[16] = { 0 };

	while (1)
	{
		MSG local_d8;

		if (DAT_05b3e384)
			break;
		if (PeekMessageA(&local_d8, 0, 0, 0, 1))
		{
			TranslateMessage(&local_d8);
			DispatchMessageA(&local_d8);
		}
		else if (DAT_05a92378 || !DAT_05ab834c)
		{
			FUN_004b5ad0();
			local_54h = FUN_0041a800()->FUN_004caf80();
			if (local_9c)
			{
				local_a8i -= local_98g[local_a4k];
				local_98g[local_a4k] = local_54h - local_9c;
				local_a8i += local_98g[local_a4k];
				local_a4k++;
				if (local_a4k == 16)
					local_a4k = 0;
			}
			local_9c = local_54h;
			DAT_05ab4248 = 16000.0 / local_a8i;
			if (UNKNOWN_CONDITION)
			{
				UNKNOWN_NO_CODE();
			}
			DAT_05b9d854 = 1;
			FUN_007d21b0();
			input_padUpdate();
			if (!DAT_05a92378)
			{
				FUN_00422e20();
				FUN_00422e70();
				continue;
			}
			FUN_00598b90();
			FUN_004a27c0();
			FUN_00422560(3);
			njUserMain();
			FUN_004af7e0();
			if ((DAT_025acd84 & 2) >> 1 && DAT_025acd84 & 1 && DAT_05b3e065)
			{
				FUN_00573280(0);
				FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
			}
			late_exec();
			if ((DAT_025acd84 & 2) >> 1 && DAT_025acd84 & 1 && DAT_05b3e065)
				FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
			if (DAT_05cc3631)
			{
				DAT_05cc3636++;
				DAT_05cc3628 = 1;
				DAT_05b3e354 = 1;
			}
			if (DAT_05cc3628 == 1 || DAT_05cc3628 == -1)
			{
				UNKNOWN_NO_CODE();
			}
			else if (DAT_05b3e357)
			{
				FUN_004c3310((int *)&DAT_05b3e088);
				DAT_05b3e357 = 0;
			}
			if (DAT_05b3e388)
				FUN_005761f0();
			MSG_Disp2();
			FUN_004c3560();
			FUN_0056a5d0();
			FUN_004c1c20();
			FUN_00598ba0();
			FUN_004cb840();
			if (DAT_05b3e354)
			{
				DAT_05b3e354 = 0;
				FUN_00503160();
			}
			if (DAT_05cc3628 == 0)
			{
				if (DAT_05b3e357)
				{
					FUN_004c3310((int *)&DAT_05b3e088);
					DAT_05b3e357 = 0;
				}
				if (DAT_05cd14d4 == 2)
					DAT_05cd14d4 = 1;
			}
			DAT_05b3e338++;
			if (DAT_05b9d73c != 16)
				DAT_05b3e33c++;
			if (FUN_004c38d0() & 0x44 && FUN_004c38b0(0x3d))
				DAT_05b3e384 = 1;
		}
		else if (DAT_05ab834c)
			DAT_05ab39ac->FUN_004207c0();
	}
	if (DAT_05b3e360)
	{
		delete DAT_05b3e360;
		DAT_05b3e360 = 0;
	}
	if (DAT_05b3e368)
	{
		FUN_0041c2d0(DAT_05b3e368);
		delete DAT_05b3e368;
		DAT_05b3e368 = 0;
	}
	if (DAT_05b3e36c)
	{
		FUN_004b5e70(&DAT_05b3e36c);
		FUN_0041c2d0(DAT_05b3e36c);
		delete DAT_05b3e36c;
		DAT_05b3e36c = 0;
	}
	if (DAT_05b3e364)
	{
		FUN_0041c2d0(DAT_05b3e364);
		delete DAT_05b3e364;
		DAT_05b3e364 = 0;
	}
	if (DAT_05b3e370)
	{
		FUN_0041c2d0(DAT_05b3e370);
		delete DAT_05b3e370;
		DAT_05b3e370 = 0;
	}
	if (DAT_05b3e374)
	{
		FUN_0041c2d0(DAT_05b3e374);
		delete DAT_05b3e374;
		DAT_05b3e374 = 0;
	}
	if (DAT_05b3e378)
	{
		FUN_0041c2d0(DAT_05b3e378);
		delete DAT_05b3e378;
		DAT_05b3e378 = 0;
	}
	if (DAT_05b3e37c)
	{
		FUN_0041c2d0(DAT_05b3e37c);
		delete DAT_05b3e37c;
		DAT_05b3e37c = 0;
	}
	if (DAT_05b3e380)
	{
		FUN_0041c2d0(DAT_05b3e380);
		delete DAT_05b3e380;
		DAT_05b3e380 = 0;
	}
	njDirectReleaseAll();
	if (DAT_060ce75c)
		FUN_007f2150();
	FUN_004adc90();
}

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

// FUNCTION: SADX 0x004addf0
void FUN_004addf0()
{
	DAT_05b3e060 = 0;
	DAT_05b3e058 = DAT_05b3e060;
	InitSystemTV();
	FUN_007d21b0(0);
	dsInitInt(1, 1);
	FUN_004ade40();
	Reset();
	input_reset();
}
