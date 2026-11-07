#include "decls.h"
#include <string.h>
void FUN_005b30b0(struct taskwk *param_1, char *param_2);
struct thread;
void FUN_0056b810(int param_1, unsigned char *param_2);
void FUN_0056b8b0(void);
struct thread *TH_CreateChild(struct thread *parent, void (*func)(void *), void *pParam, unsigned int stack_size);
extern unsigned char DAT_0098b338;
void FUN_0056b6d0(struct task *param_1);
void FUN_0056b920(struct task *param_1);
void FUN_004e2f70(int param_1, int param_2);
void *TH_GetWork(struct thread *tp);
void EV_Destruct();
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
void ___njSetPerspective(long a);
int HokanInt(int mode, int time, int count, int va, int vb);
void FUN_0056ccc0(int param_1);
extern int DAT_05ccdd28;
void FUN_0056cc30(int param_1);
extern unsigned char DAT_05ccddfc;
extern struct NJS_POINT3 DAT_05ccdd34;
extern struct Angle3 DAT_05ccdd40;
void FUN_0056a200(struct task *param_1);
struct eventwk;
void ___OutputDebugString(char *str, ...);
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
extern int DAT_05ccde08;
extern int DAT_05ccddf4;
extern int DAT_05cda168;
extern short DAT_05b9d73c;
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

// FUNCTION: SADX 0x0056a200
void FUN_0056a200(struct task *param_1)
{
	struct motionwk *local_8g;
	int local_cg;
	if (param_1 != 0)
	{
		if (param_1->mwp != 0)
		{
			local_8g = param_1->mwp;
			if (local_8g->work.ptr != 0)
			{
				local_cg = (int)local_8g->work.ptr;
				FUN_004e2f70((int)local_8g, local_cg);
			}
		}
	}
}

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

// FUNCTION: SADX 0x0056a2a0
void FUN_0056a2a0()
{
	PadReadOn();
}

// FUNCTION: SADX 0x0056a2b0
void FUN_0056a2b0()
{
	PadReadOff();
}

// FUNCTION: SADX 0x0056a2c0
void FUN_0056a2c0()
{
	void *local_8;
	local_8 = TH_GetWork(0);
	if (DAT_05ccde0c == 0)
	{
		DAT_05ccde0c = *(int *)local_8;
	}
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

// STUB: SADX 0x0056a980
void EV_Load2(int no)
{
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

// STUB: SADX 0x0056ab80
void FUN_0056ab80(int *param_1, void (*param_2)(void (*)(int)))
{
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
		local_cg->fc.argb.a = 0;
		local_cg->bc.argb.a = 0;
		if (local_cg->bitmap == 0)
		{
			return;
		}
	}
	else if (local_cg->fc.argb.a != 0)
	{
		MSG_FadeOut(local_cg);
	}
	MSG_Cls(local_cg);
	MSG_Puts(local_cg, str);
	MSG_LoadTexture(local_cg);
	if (local_cg->bc.argb.a == 0)
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

// FUNCTION: SADX 0x0056b270
void EV_CreateObjectFunc(struct task **tp, struct task *(*func)(), float px, float py, float pz, long ax, long ay, long az)
{
	struct taskwk *local_8;
	FUN_0056b2f0(tp);
	if (func == 0)
	{
		___OutputDebugString("\nERROR : EV_CreateObjectFunc() func=NULL\n\n");
	}
	else
	{
		*tp = func();
		local_8 = (*tp)->twp;
		local_8->pos.x = px;
		local_8->pos.y = py;
		local_8->pos.z = pz;
		local_8->ang.x = ax;
		local_8->ang.y = ay;
		local_8->ang.z = az;
	}
}

// FUNCTION: SADX 0x0056b2f0
void FUN_0056b2f0(struct task **param_1)
{
	if (*param_1 != 0)
	{
		FreeTask(*param_1);
	}
	*param_1 = 0;
}

// FUNCTION: SADX 0x0056b320
void FUN_0056b320(struct task *param_1)
{
	if (param_1)
	{
		FUN_0056b6d0(param_1);
		EV_ClrPath(param_1);
		FUN_0056b920(param_1);
		EV_MoveFree(param_1);
		EV_ClrFace(param_1);
	}
}

// FUNCTION: SADX 0x0056b370
void FUN_0056b370(struct task *param_1, float param_2, float param_3, float param_4)
{
	struct taskwk *local_8;

	if (param_1 != 0)
	{
		local_8 = param_1->twp;
		FUN_0056a200(param_1);
		local_8->pos.x = param_2;
		local_8->pos.y = param_3;
		local_8->pos.z = param_4;
		if (local_8->cwp != 0)
		{
			if (local_8->cwp->id == 0)
			{
				SetPlayerPosition(local_8->counter.b[0], 0, &local_8->pos, 0);
			}
		}
	}
}

// FUNCTION: SADX 0x0056b3e0
void FUN_0056b3e0(struct task *param_1, long param_2, long param_3, long param_4)
{
	struct taskwk *local_8;
	if (param_1 != 0)
	{
		local_8 = param_1->twp;
		FUN_0056a200(param_1);
		local_8->ang.x = param_2;
		local_8->ang.y = 0x4000 - param_3;
		local_8->ang.z = param_4;
	}
}

// FUNCTION: SADX 0x0056b430
void EV_SetMode(struct task *tp, int mode)
{
	if (tp != 0)
	{
		tp->twp->ewp->mode = mode;
	}
}

// FUNCTION: SADX 0x0056b450
void EV_SetShadow(struct task *tp, float size)
{
	if (tp != 0)
	{
		tp->twp->ewp->shadowSize = size;
	}
}

// FUNCTION: SADX 0x0056b470
void EV_SetColli(struct task *tp, float size)
{
	if (tp != 0)
	{
		tp->twp->cwp->info->a = size;
	}
}

// STUB: SADX 0x0056b490
void EV_CreatePlayer(int n, void (*func)(struct task *), float px, float py, float pz, long ax, long ay, long az)
{
}

// STUB: SADX 0x0056b510
void FUN_0056b510(unsigned char param_1)
{
}

// STUB: SADX 0x0056b540
void EV_InitPlayer(int n)
{
}

// FUNCTION: SADX 0x0056b650
void FUN_0056b650(struct task *param_1, struct NJS_ACTION *param_2, struct NJS_TEXLIST *param_3, float param_4, int param_5, int param_6)
{
	if (param_1 != 0)
	{
		EntryEventAction(param_1->twp, param_2, param_3, param_4, param_5, param_6);
	}
}

// FUNCTION: SADX 0x0056b6d0
void FUN_0056b6d0(struct task *param_1)
{
	if (param_1 != 0)
	{
		FreeEventAction(param_1->twp);
	}
}

// FUNCTION: SADX 0x0056b6f0
void FUN_0056b6f0(void *param_1)
{
	if (0 != param_1)
	{
		while (*(int **)((char *)*(int **)((char *)*(int **)((char *)param_1 + 0x20) + 0x3c) + 0x40) != 0)
		{
			FUN_0056aea0(1);
		}
	}
}

// FUNCTION: SADX 0x0056b720
void FUN_0056b720(struct task *param_1, struct EPATHTAG *param_2, float param_3, int param_4)
{
	if (param_1 != 0)
	{
		EntryEventPath(param_1->twp, param_2, param_3, param_4);
	}
}

// FUNCTION: SADX 0x0056b750
void EV_ClrPath(struct task *tp)
{
	if (tp != 0)
	{
		FreeEventPath(tp->twp);
	}
}

// FUNCTION: SADX 0x0056b770
void FUN_0056b770(int param_1)
{
	if (0 != param_1)
	{
		while (*(int **)((char *)*(int **)((char *)*(int **)((char *)param_1 + 0x20) + 0x3c) + 0x4c) != 0)
		{
			FUN_0056aea0(1);
		}
	}
}

// FUNCTION: SADX 0x0056b7a0
void FUN_0056b7a0(int param_1, int param_2)
{
	void *local_cg;
	struct thread *local_8g;

	FUN_0056aea0(1);
	local_8g = TH_CreateChild(0, (void (__cdecl *)(void *))FUN_0056b8b0, 0, 0);
	if (local_8g != 0)
	{
		local_cg = TH_GetWork(local_8g);
		*(char *)local_cg = (char)param_1;
		*(int *)((char *)local_cg + 4) = param_2;
	}
	FUN_0056b810(param_1, &DAT_0098b338);
	FUN_0056aea0(1);
}

// STUB: SADX 0x0056b810
void FUN_0056b810(int param_1, unsigned char *param_2)
{
}

// FUNCTION: SADX 0x0056b920
void FUN_0056b920(struct task *param_1)
{
	if (param_1 != 0)
		param_1->twp->ewp->look.mode = 0;
}

// FUNCTION: SADX 0x0056b940
void EV_LookObject(struct task *tp, struct task *target, float x, float y, float z)
{
	struct eventwk *local_8;
	if (tp != 0)
	{
		local_8 = tp->twp->ewp;
		local_8->look.mode = 3;
		local_8->look.obj = target;
		local_8->look.pos.x = x;
		local_8->look.pos.y = y;
		local_8->look.pos.z = z;
	}
}

// FUNCTION: SADX 0x0056b990
void EV_LookPoint(struct task *tp, float x, float y, float z)
{
	struct eventwk *local_8;
	if (tp != 0)
	{
		local_8 = tp->twp->ewp;
		local_8->look.mode = 2;
		local_8->look.pos.x = x;
		local_8->look.pos.y = y;
		local_8->look.pos.z = z;
	}
}

// FUNCTION: SADX 0x0056b9d0
void EV_LookAngle(struct task *tp, long x, long y, long z)
{
	if (tp != 0)
	{
		void *local_8 = (void *)tp->twp->ewp;
		*(char *)((char *)local_8 + 4) = 1;
		*(long *)((char *)local_8 + 8) = x;
		*(long *)((char *)local_8 + 0xc) = y;
		*(long *)((char *)local_8 + 0x10) = z;
	}
}

// FUNCTION: SADX 0x0056ba10
void EV_MoveFree(struct task *tp)
{
	struct eventwk *local_8;
	if (tp != 0)
	{
		local_8 = tp->twp->ewp;
		local_8->move.mode = 0;
		local_8->move.run_speed = 0.0f;
		local_8->move.run_accel = 0.0f;
	}
}

// FUNCTION: SADX 0x0056ba50
void FUN_0056ba50(struct task *param_1, float param_2, float param_3, float param_4)
{
	struct taskwk *local_8g;
	if (param_1 != 0)
	{
		local_8g = (struct taskwk *)param_1->twp->ewp;
		FUN_0056a200(param_1);
		*(unsigned char *)((char *)local_8g + 0x24) = 2;
		local_8g->pos.z = param_2;
		local_8g->scl.x = param_3;
		local_8g->scl.y = param_4;
		local_8g->scl.z = 0.0f;
		*(float *)((char *)local_8g + 0x38) = 0.0f;
	}
	return;
}

// FUNCTION: SADX 0x0056bab0
void EV_MovePoint2(struct task *tp, float x, float y, float z, float s, float a)
{
	char *local_8;
	if (tp != 0)
	{
		local_8 = (char *)tp->twp->ewp;
		FUN_0056a200(tp);
		*(char *)(local_8 + 0x24) = 2;
		*(float *)(local_8 + 0x28) = x;
		*(float *)(local_8 + 0x2c) = y;
		*(float *)(local_8 + 0x30) = z;
		*(float *)(local_8 + 0x34) = s;
		*(float *)(local_8 + 0x38) = a;
	}
}

// FUNCTION: SADX 0x0056bb10
void EV_MoveRotation(struct task *tp, long x, long y, long z)
{
	if (tp != 0)
	{
		struct eventwk *local_8 = tp->twp->ewp;
		local_8->move.mode = 5;
		local_8->move.param.ang.x = x;
		local_8->move.param.ang.y = y;
		local_8->move.param.ang.z = z;
	}
}

// FUNCTION: SADX 0x0056bb50
void FUN_0056bb50(struct task *param_1)
{
	struct eventwk *local_8;
	if (param_1 != 0)
	{
		local_8 = param_1->twp->ewp;
		while (local_8->move.mode != 0)
		{
			FUN_0056aea0(1);
		}
	}
}

// FUNCTION: SADX 0x0056bcd0
void FUN_0056bcd0()
{
	int *local_8g = (int *)TH_GetWork(0);
	int *local_cg = (int *)&DAT_05ccdd28;
	if (*(int *)((char *)local_cg + 0xcc) == *local_8g)
	{
		*(int *)((char *)local_cg + 0xcc) = 0;
		CameraReleaseEventCamera();
	}
}

// STUB: SADX 0x0056bd10
void CalcEventCameraPers()
{
}

// STUB: SADX 0x0056bdc0
int HokanInt(int mode, int time, int count, int va, int vb)
{
	return (int)0;
}

// FUNCTION: SADX 0x0056be40
void CalcEventCamera()
{
	if (DAT_05ccddfc == 0)
	{
		CalcEventCameraPos();
		CalcEventCameraAng();
		CalcEventCameraPers();
	}
	DAT_05b42a7c->pos = DAT_05ccdd34;
	DAT_05b42a7c->ang = DAT_05ccdd40;
}

// FUNCTION: SADX 0x0056c640
float HokanFloat(int mode, int time, int count, float va, float vb)
{
	float c;
	switch (mode)
	{
	case 0:
		c = (float)count / (float)time;
		break;
	case 1:
		c = (-njCos((count << 0xf) / time) + 1.0) / 2.0;
		break;
	}
	return (vb - va) * c + va;
}

// STUB: SADX 0x0056c6a0
int ExecCameraPath()
{
	return (int)0;
}

// STUB: SADX 0x0056cab0
void CalcAng(struct NJS_POINT3 *pos, struct NJS_POINT3 *target, struct Angle3 *ang)
{
}

// STUB: SADX 0x0056cb30
void FUN_0056cb30(float *param_1, float *param_2, int *param_3)
{
}

// STUB: SADX 0x0056cbf0
void EV_CameraAng(int mode, int time, long x, long y, long z)
{
}

// STUB: SADX 0x0056cc30
void FUN_0056cc30(int param_1)
{
}

// FUNCTION: SADX 0x0056cc80
void EV_CameraPos(int mode, int time, float x, float y, float z)
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)local_8 = (char)mode;
	*(float *)((char *)local_8 + 0x3c) = x;
	*(float *)((char *)local_8 + 0x40) = y;
	*(float *)((char *)local_8 + 0x44) = z;
	FUN_0056ccc0(time);
}

// STUB: SADX 0x0056ccc0
void FUN_0056ccc0(int param_1)
{
}

// STUB: SADX 0x0056cd10
void EV_CameraPosORY(int mode, int time, struct task *tp, float x, float y, float z)
{
}

// FUNCTION: SADX 0x0056cde0
void FUN_0056cde0(void)
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0x54) = 0;
}

// FUNCTION: SADX 0x0056ce00
void FUN_0056ce00(char param_1, int param_2, float param_3, float param_4, float param_5, int param_6)
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0x01) = param_1;
	*(char *)((char *)local_8 + 0x54) = 1;
	*(float *)((char *)local_8 + 0x58) = param_3;
	*(float *)((char *)local_8 + 0x5c) = param_4;
	*(float *)((char *)local_8 + 0x60) = param_5;
	*(int *)((char *)local_8 + 0x50) = param_6;
	FUN_0056cc30(param_2);
}

// FUNCTION: SADX 0x0056ce50
void FUN_0056ce50(char param_1, int param_2, int param_3, float param_4, float param_5, float param_6, int param_7)
{
	char *local_8;
	local_8 = (char *)&DAT_05ccdd28;
	*(char *)(local_8 + 1) = param_1;
	*(char *)(local_8 + 0x54) = 2;
	*(int *)(local_8 + 0x64) = param_3;
	*(float *)(local_8 + 0x58) = param_4;
	*(float *)(local_8 + 0x5c) = param_5;
	*(float *)(local_8 + 0x60) = param_6;
	*(int *)(local_8 + 0x50) = param_7;
	FUN_0056cc30(param_2);
}

// FUNCTION: SADX 0x0056ceb0
void EV_CameraChaseFree()
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0x68) = 0;
}

// STUB: SADX 0x0056cf40
void EV_CameraChaseRM(int mode, int time, struct task *tp, float height, long x0, long y0, long z0, float d0, long x1, long y1, long z1, float d1)
{
}

// FUNCTION: SADX 0x0056d010
void EV_CameraPerspective(int mode, int time, long ang)
{
	int *local_8;
	local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0xac) = (char)mode;
	*(short *)((char *)local_8 + 0xae) = (short)time;
	*(short *)((char *)local_8 + 0xb0) = 0;
	*(int *)((char *)local_8 + 0xb8) = *(int *)((char *)local_8 + 0xb4);
	*(int *)((char *)local_8 + 0xbc) = (int)ang;
	if (time == 0)
		CalcEventCameraPers();
}

// STUB: SADX 0x0056d070
void EV_CameraPath(struct cpathtag *path, float speed)
{
}

// FUNCTION: SADX 0x0056d0b0
void FUN_0056d0b0(struct task *param_1, char *param_2)
{
	struct taskwk *local_8;
	if (param_1 != NULL)
	{
		local_8 = param_1->twp;
		FUN_005b30b0(local_8, param_2);
	}
}

// FUNCTION: SADX 0x0056d0e0
void EV_ClrFace(struct task *tp)
{
	struct taskwk *local_8;
	if (tp != 0)
	{
		local_8 = tp->twp;
		ClrEventFace(local_8);
	}
}

// FUNCTION: SADX 0x0056d110
void EV_CameraOff()
{
	long local_8g = FUN_004f6400();
	while (local_8g != 0 && local_8g != 5)
	{
		FUN_0056aea0(1);
		local_8g = FUN_004f6400();
	}
}

// FUNCTION: SADX 0x0056d140
void EV_SerifPlay(int id)
{
	EV_CameraOff();
	Serif_Play(id);
}

// FUNCTION: SADX 0x0056d160
void FUN_0056d160(struct AlrReal *param_1)
{
	Serif_Stop();
}
