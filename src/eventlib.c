#include "decls.h"
#include <string.h>
extern int DAT_05ccde18;
extern int DAT_05ccde00;
extern int DAT_05ccde0c;
extern signed char DAT_05baf900[0x200];
extern int DAT_05ccddf8;
extern char DAT_05ccddfd;
extern char DAT_05ccddfe;
extern char DAT_05b42c1c;
extern int DAT_05cd14d4;
extern int DAT_05b9d728;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05ccde10;
extern int DAT_05ccde14;
extern void *DAT_05eda1d8;
extern int DAT_05b42a80;
extern unsigned char DAT_05ad95e1;
extern int DAT_05ccde04;
extern int DAT_05ccde08;
extern int DAT_05ccddf4;
extern int DAT_05cda168;
extern short DAT_05b9d73c;
extern int DAT_02603708[0x200];
int FUN_0056ab50(int *param_1);
void FUN_005a4d70();
void FUN_0056a970(unsigned long param_1);
void FUN_004c3310(int *param_1);
void FUN_0056aa50(int *param_1);
void FUN_0056ab30();
void FUN_0056ab80(int *param_1, void (*param_2)(void (*)(int)));
void FUN_0056bcd0();
void FUN_0056aea0(int param_1);
void FUN_0056b2f0(struct task **param_1);
static void dsEventFinish();
static void dsEventADXReinit(struct task *tp);
static void EV_CanselThread(void (*func)(int));

// FUNCTION: SADX 0x0056a250
void EV_Init()
{
	memset(DAT_05baf900, 0, 0x200);
	DAT_05ccddf8 = 0;
	DAT_05ccde0c = 0;
	DAT_05ccddfd = 0;
	DAT_05b42c1c = 1;
	DAT_05ccddfe = 0;
	current_event = -1;
}

// FUNCTION: SADX 0x0056a2f0
void dsFadeout_flgend(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (local_8->mode == 0)
	{
		local_8->wtimer = 0;
		local_8->mode = 1;
	}
	else
	{
		local_8->wtimer++;
		if (local_8->wtimer == 7)
		{
			DAT_05cd14d4 = 0;
		}
		else if (local_8->wtimer == 8)
		{
			DAT_05b9d728 = 0;
			DestroyTask(tp);
		}
	}
}

// FUNCTION: SADX 0x0056a370
void dsEventBGMRestart(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	int local_cj;
	int local_10;
	if (local_8g->mode == 0)
	{
		local_8g->wtimer = 0;
		local_8g->mode = 1;
		local_8g->smode = (DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff;
	}
	else
	{
		local_8g->wtimer++;
		if (local_8g->wtimer == 8)
		{
			if (current_event < 0 && local_8g->smode == ((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff))
			{
				local_cj = DAT_05b9d724 << 8 | DAT_05b9d744;
				local_10 = local_cj & 0xff;
				local_cj >>= 8;
				switch (local_cj)
				{
				case 0x1a:
					ADXTaskInit();
					BGM_Play(0x4c);
					break;
				case 0x1d:
				case 0x1e:
				case 0x1f:
				case 0x20:
					ADXTaskInit();
					BGM_Play(0x1f);
					break;
				case 0x21:
					switch (local_10)
					{
					case 0:
					case 1:
					case 2:
						ADXTaskInit();
						BGM_Play(0x43);
						break;
					case 3:
						ADXTaskInit();
						BGM_Play(0x2a);
						break;
					}
					break;
				case 0x22:
					ADXTaskInit();
				}
			}
			DestroyTask(tp);
		}
	}
}

// FUNCTION: SADX 0x0056a500
void dsEventCtrlPauseflg(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (local_8->mode == 0)
	{
		local_8->wtimer = 0;
		local_8->mode = 1;
	}
	else
	{
		local_8->wtimer++;
		if (local_8->wtimer == 0x10)
		{
			DAT_05cd14d4 = 0;
			DestroyTask(tp);
		}
		else
		{
			DAT_05cd14d4 = 1;
		}
	}
}

// FUNCTION: SADX 0x0056a570
int dsCheckBGMActive()
{
	int local_8g = 1;
	int *local_cg;
	if (current_event < 0)
	{
		return 1;
	}
	local_cg = evbgmtbl;
	while (*local_cg >= 0 || local_8g != 0)
	{
		if (current_event == *local_cg)
		{
			local_8g = 0;
			break;
		}
		local_cg++;
	}
	return local_8g;
}

// FUNCTION: SADX 0x0056a6a0
void EV_MainThread(void (*func)(int))
{
	int *local_8g = (int *)TH_GetWork(0);
	int local_cj;
	int local_10m;
	int local_14;
	DAT_05ccde10 = 0;
	DAT_05ccde14 = 0x3c;
	if (func == 0)
	{
		___OutputDebugString("\nERROR : EV_MainThread() func=NULL\n\n");
	}
	else
	{
		EV_FreeNpcMilesPlayerTask();
		TH_SetStatus(0, 1);
		if (func != 0)
		{
			func(1);
		}
		DAT_05cd14d4 = 1;
		TH_SetStatus(0, 2);
		if (func != 0)
		{
			func(2);
		}
		ResetCameraTimer();
		SpDestroyTaskAll();
		EV_MsgClose();
		FUN_0056a970(*(unsigned long *)(DAT_05ccddf8 + 4));
		FUN_004f3f60(DAT_05eda1d8);
		late_execCancelNoErase();
		pdVibMxStop(0);
		local_cj = (int)TH_GetWork(0);
		for (local_10m = 0x20; local_10m != 0; local_10m--)
		{
			local_14 = local_cj;
			dsStop_id(local_14);
			local_cj++;
		}
		FUN_005a4d70();
		dsEventFinish();
		FUN_005a4d70();
		___njSetPerspective(0x31c7);
		DAT_05b42a80 = 0x31c7;
		EV_CreateNpcMilesPlayerTask();
		if (DAT_05ccde0c == *local_8g)
		{
			DAT_05ccde0c = 0;
		}
		ReleaseModule(5);
	}
}

// FUNCTION: SADX 0x0056a800
static void dsEventFinish()
{
	int local_8g;
	int *local_cg;
	ADX_Close();
	dsInitInt(2, 2);
	dsLoadCharacterVoice();
	EV_PcNpcInit();
	CreateElementalTask(2, 0, dsFadeout_flgend);
	DAT_05b9d728 = -1;
	local_8g = 0;
	local_cg = evnobgmtbl;
	while (*local_cg >= 0 || local_8g != 0)
	{
		if (current_event == *local_cg)
		{
			local_8g = -1;
			break;
		}
		local_cg++;
	}
	if (local_8g == 0)
	{
		CreateElementalTask(2, 0, dsEventBGMRestart);
	}
	else if (current_event == 0x166)
	{
		CreateElementalTask(2, 0, dsEventADXReinit);
	}
	current_event = -1;
}

// FUNCTION: SADX 0x0056a8c0
static void dsEventADXReinit(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (local_8->mode == 0)
	{
		local_8->wtimer = 0;
		local_8->mode = 1;
		local_8->smode = (DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff;
	}
	else
	{
		local_8->wtimer++;
		if (local_8->wtimer == 8)
		{
			if (current_event < 0 && local_8->smode == ((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff))
			{
				ADXTaskInit();
			}
			DestroyTask(tp);
		}
	}
}

// FUNCTION: SADX 0x0056a970
void FUN_0056a970(unsigned long param_1)
{
	DAT_05ccde18 = param_1;
}

// FUNCTION: SADX 0x0056a980
void EV_Load2(int no)
{
	char str[32];
	DAT_05ad95e1 = 1;
	if (no < 0)
	{
		goto LAB_0056a9d3;
	}
	SPrintf(str, "ev%04X.rel", no);
	ADX_Close();
	njWaitVSync();
	if (((int (*)(char *, int))FUN_004c39c0)(str, 5) != -1)
	{
LAB_0056a9d3:
		DAT_05ccddf8 = DAT_02603708[no];
		DAT_05ccddfd = 1;
		DAT_05ccde04 = 0;
		DAT_05ccde00 = *(int *)DAT_05ccddf8;
		DAT_05ccde08 = no;
		PadReadOff();
		FUN_0056aa50((int *)*(int *)(DAT_05ccddf8 + 4));
		if (DAT_05ccde00 != 0)
		{
			((void (*)(int))DAT_05ccde00)(0);
		}
	}
	ADXTaskInit();
	DAT_05ad95e1 = 0;
}

// FUNCTION: SADX 0x0056aa50
void FUN_0056aa50(int *param_1)
{
	if (param_1 == 0)
	{
		___OutputDebugString("ERROR : EV_LoadPvm(NULL)\n");
	}
	else
	{
		while (param_1[1] != 0)
		{
			if (*param_1 != 0)
			{
				texLoadTexturePvmFile((char *)*param_1, (struct NJS_TEXLIST *)param_1[1]);
			}
			else
			{
				NeonuLoadTexture((struct NJS_TEXLIST *)param_1[1]);
			}
			param_1 = param_1 + 2;
		}
	}
}

// FUNCTION: SADX 0x0056aab0
void EV_Exec2()
{
	if (FUN_0056ab50(&DAT_05ccde00) == 4)
	{
		DAT_05cd14d4 = 1;
		CreateElementalTask(2, 0, dsEventCtrlPauseflg);
		FUN_0056ab80(&DAT_05ccde00, EV_MainThread);
		DAT_05baf900[DAT_05ccde08] = 1;
		FUN_0056ab30();
		current_event = DAT_05ccde08;
		HintMessageStop();
	}
	else
	{
		dsEventFinish();
	}
	DAT_05cda168 = 0;
}

// FUNCTION: SADX 0x0056ac20
void EV_Destruct()
{
	int *local_8g = (int *)TH_GetWork(0);
	int local_cg = *local_8g;
	FUN_004c3310(local_8g + 1);
	if (DAT_05ccde0c == local_cg)
	{
		DAT_05ccde0c = 0;
	}
	if (DAT_05ccddf4 == local_cg)
	{
		FUN_0056bcd0();
	}
	*(int *)(local_cg + 4) = 0;
}

// FUNCTION: SADX 0x0056ac80
void FUN_0056ac80()
{
	___OutputDebugString("EV_Cansel\n");
	if (DAT_05ccde0c != 0)
	{
		if (FUN_0056ab50((int *)DAT_05ccde0c) == 1)
		{
			FUN_0056ab80((int *)DAT_05ccde0c, EV_CanselThread);
		}
	}
}

// FUNCTION: SADX 0x0056acd0
static void EV_CanselThread(void (*func)(int))
{
	int local_8g;
	int local_cj;
	int local_10;
	___OutputDebugString("EV_CanselThread\n");
	DAT_05cd14d4 = 1;
	MSG_Disp(0);
	if (func == 0)
	{
		___OutputDebugString("\nERROR : EV_CanselThread() func=NULL\n\n");
	}
	else
	{
		TH_SetStatus(0, 2);
		func(2);
		SpDestroyTaskAll();
		EV_MsgClose();
		___OutputDebugString("before EV_ReleasePvm on EV_Cansel_Thread\n");
		FUN_0056a970(*(unsigned long *)(DAT_05ccddf8 + 4));
		___OutputDebugString("before deleteThreadTask on EV_Cansel_Thread\n");
		FUN_004f3f60((void *)*(int *)(DAT_05ccde0c + 4));
		___OutputDebugString("before deleteThreadTask on EV_Cansel_Thread\n");
		late_execCancelNoErase();
		ResetCameraTimer();
		___OutputDebugString("before pdVibMxStop on EV_Cansel_Thread\n");
		pdVibMxStop(0);
		local_8g = (int)TH_GetWork(0);
		for (local_cj = 0x20; local_cj != 0; local_cj--)
		{
			local_10 = local_8g;
			dsStop_id(local_10);
			local_8g++;
		}
		FUN_005a4d70();
		dsEventFinish();
		FUN_005a4d70();
		___OutputDebugString("before njSetPerspective on EV_Cansel_Thread\n");
		___njSetPerspective(0x31c7);
		DAT_05b42a80 = 0x31c7;
		EV_CreateNpcMilesPlayerTask();
		ReleaseModule(5);
		if (DAT_05b9d73c == 4)
		{
			DAT_05b9d73c = 0xf;
		}
		DAT_05cd14d4 = 1;
		DAT_05ccde10 = 0x3c;
	}
}

// FUNCTION: SADX 0x0056ae50
int EV_Check(int no)
{
	if (FUN_0056ab50(&DAT_05ccde00) != 4)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0056ae70
int EV_CheckCansel()
{
	return DAT_05ccde0c != 0;
}

// FUNCTION: SADX 0x0056ae90
int EV_CheckExec(int no)
{
	return DAT_05baf900[no];
}

// FUNCTION: SADX 0x0056b020
void EV_Msg(char *str)
{
	char *local_8g = (char *)TH_GetWork(0);
	struct MSGC *local_cg = (struct MSGC *)(local_8g + 4);
	if (str == 0)
	{
		return;
	}
	if (local_cg->bitmap == 0)
	{
		NH_MSG_OpenMain(local_cg);
		local_cg->kind = 1;
		local_cg->fc.argb.b = 0;
		local_cg->bc.argb.b = 0;
		if (local_cg->bitmap == 0)
		{
			return;
		}
	}
	else if (local_cg->fc.argb.b != 0)
	{
		MSG_FadeOut(local_cg);
	}
	MSG_Cls(local_cg);
	MSG_Puts(local_cg, str);
	MSG_LoadTexture(local_cg);
	if (local_cg->bc.argb.b == 0)
	{
		MSG_WinFadeIn(local_cg);
	}
	else
	{
		MSG_FadeIn(local_cg);
	}
}

// FUNCTION: SADX 0x0056b0f0
void EV_MsgW(int time, char *str)
{
	time += GetGlobalTime();
	EV_Msg(str);
	time -= GetGlobalTime();
	if (time > 0)
	{
		FUN_0056aea0(time);
	}
}

// FUNCTION: SADX 0x0056b130
void EV_MsgClose()
{
	char *local_8g = (char *)TH_GetWork(0);
	struct MSGC *local_cg = (struct MSGC *)(local_8g + 4);
	___OutputDebugString("EV_MsgClose 1\n");
	if (local_cg->bitmap != 0)
	{
		___OutputDebugString("EV_MsgClose 2\n");
		MSG_WinFadeOut(local_cg);
		___OutputDebugString("EV_MsgClose 3\n");
		FUN_004c3310((int *)local_cg);
		___OutputDebugString("EV_MsgClose 4\n");
	}
	___OutputDebugString("EV_MsgClose 5\n");
	FUN_005a4d70();
}

// FUNCTION: SADX 0x0056b1c0
void EV_MsgCls()
{
	char *local_8g = (char *)TH_GetWork(0);
	struct MSGC *local_cg = (struct MSGC *)(local_8g + 4);
	MSG_FadeOut(local_cg);
}

// FUNCTION: SADX 0x0056b1f0
struct task *FUN_0056b1f0(unsigned char param_1)
{
	return GetPlayerTaskPointer(param_1);
}

// FUNCTION: SADX 0x0056b210
void EV_CreateObject(struct task **tp, float px, float py, float pz, long ax, long ay, long az)
{
	struct taskwk *local_8;
	FUN_0056b2f0(tp);
	*tp = CreateEventObject();
	local_8 = (*tp)->twp;
	local_8->pos.x = px;
	local_8->pos.y = py;
	local_8->pos.z = pz;
	local_8->ang.x = ax;
	local_8->ang.y = ay;
	local_8->ang.z = az;
}
