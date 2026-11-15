#include "decls.h"
#include "../advertise.h"
extern unsigned char DAT_05cda1a8;
extern unsigned char DAT_05cd14ec;
extern unsigned char DAT_05cd14e3;
extern int DAT_05b9d840;
extern int DAT_05cc3624;
extern bool DAT_05b3e359;
extern int DAT_05b3e35c;


extern unsigned char DAT_026313a8;
extern int DAT_026313a4;
extern int DAT_05a92334;
extern int DAT_05cda1ac;
void DisplayFinTitle(struct TitleNewWk *wkp, float basez);
void DrawDXTitle(struct TitleNewWk *wkp);
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_005a0070(struct task *param_1);
void FUN_005a0070(struct task *param_1);
extern struct task *DAT_05cda19c;

// FUNCTION: SADX 0x0059f950
struct task *SetAdvaTitleNewTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(8, 3, title_new_exec);
	DAT_05cda19c = local_8g;
	if (DAT_05cda19c)
	{
		local_cg = CAlloc(1, 0x48);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005fe110(local_8g, prmp);
		local_8g->exec = title_new_exec;
		local_8g->disp = FUN_005a0070;
	}
	return local_8g;
}

// FUNCTION: SADX 0x0059fc10
void TitleNewWakeProcedure(struct TitleNewWk *wkp)
{
	unsigned char local_5;
	FUN_00405f00()->FUN_00424950(-1);
	local_5 = DAT_05ad95e1;
	DAT_05ad95e1 = 1;
	DAT_05cda1a8 = 0;
	SetStageNumber(0, 0);
	dsEditLightInit();
	wkp->titletimer = 0;
	wkp->movetimer = 0;
	wkp->kumotimer = 0.0f;
	wkp->kumoindex = 0;
	FUN_005988f0();
	if (!wkp->CamTskPtr)
	{
		if ((wkp->CamTskPtr = CreateElementalTask(2, 0, ghAdvertiseCamera)) != 0)
		{
			struct taskwk *local_c = wkp->CamTskPtr->twp;
			local_c->ang.z = 0;
			local_c->ang.y = 0;
			local_c->ang.x = 0;
			local_c->pos.z = 0.0f;
			local_c->pos.y = 0.0f;
			local_c->pos.x = 0.0f;
		}
	}
	wkp->wavetimer = 0;
	AvaLoadTexForEachMode((AdvaModeEnum)5);
	DAT_05ab39ac->FUN_00419d00(6);
	if (!DAT_05b3ebbc)
		texLoadTexturePvmFile("ava_gtitle0", &texlist_ava_title_sub);
	if (DAT_05cd14ec || DAT_05cd14e3 == 1)
	{
		SetSerifuChar();
		ChgSeqTitleNew();
		ChgSeqTitleMenu();
		wkp->SubMode = (TitleNewSbMdEnum)2;
	}
	else
		wkp->SubMode = (TitleNewSbMdEnum)0;
	wkp->bBgmEnabled = 0;
	DAT_05ad95e1 = local_5;
}

// FUNCTION: SADX 0x0059fd80
void FUN_0059fd80(struct task *param_1)
{
	if (param_1->awp)
	{
		DestroyTask((struct task *)param_1->awp);
		param_1->awp = NULL;
	}
}

// FUNCTION: SADX 0x0059fdb0
void FUN_0059fdb0(struct TitleNewWk *param_1)
{
	int local_8;
	switch (param_1->SubMode)
	{
	case 0:
		param_1->SubMode = (TitleNewSbMdEnum)2;
		calcvsyncsyoriochi();
		DAT_05b9d838 = 0;
		DAT_05b9d840 = DAT_05b9d848;
		param_1->titletimer = 0;
		param_1->titleblinktimer = 0;
		DAT_05cd14e3 = 0;
		DAT_05cc3574 = 1;
		DAT_05cc3624 = 0;
		DAT_05cc3620 = 0;
		break;
	case 2:
		DAT_05b9d848 = DAT_05b9d840;
		if (!param_1->bBgmEnabled)
		{
			param_1->bBgmEnabled = 1;
			SetAdvaModeBGM((AvaBgmEnum)0);
		}
		if (param_1->titletimer < 0)
		{
			param_1->titletimer = DAT_05b9d848 + param_1->titletimer;
			param_1->titleblinktimer = 0;
			break;
		}
		KeyGetPress(0x29);
		local_8 = -1;
		FUN_00405f00()->FUN_00424950(-1);
		if (DAT_05b3e359 || ((local_8 = FUN_00405f00()->FUN_00424910(0)) != -1 && DAT_05b40a48 == 1))
		{
			if (DAT_05b3e359)
				local_8 = DAT_05b3e35c;
			FUN_00405f00()->FUN_00424950(local_8);
			DAT_05b3e359 = 0;
			if (!FUN_0040ae00())
			{
				if (DAT_026313a8)
				{
					CreateInitData();
					DAT_026313a8 = 0;
				}
				else
				{
					char local_9g = DAT_05ccca18.option;
					char local_ag = DAT_05ccca18.vibration;
					CreateInitData();
					DAT_05ccca18.vibration = local_ag;
					DAT_05ccca18.option = local_9g;
				}
				ExtractLoadData();
				CmnAdvaModeProcedure((AdvaModeEnum)14);
			}
			else
				CmnAdvaModeProcedure(param_1->NextMode);
			AdvaSndCsrClick();
			param_1->SubMode = (TitleNewSbMdEnum)3;
			break;
		}
		{
		int local_10 = 0;
		if (IsSoundSystem() && DAT_05a92334)
		{
			if (DAT_05cda1a8)
				DAT_026313a4 = FUN_0041a800()->FUN_004caf80();
			else if (FUN_0041a800()->FUN_004caf80() - DAT_026313a4 > 5000 && GetStatAdvaBGM() == 5)
				local_10 = 1;
		}
		else
		{
			DAT_05cda1ac += DAT_05b9d848;
			if (DAT_05cda1ac >= 300)
			{
				DAT_05cda1ac = 0;
				local_10 = 1;
			}
		}
		if (local_10)
		{
			*(int *)((char *)DAT_05cda18c->awp + 0x10) = 107;
			CmnAdvaModeProcedure((AdvaModeEnum)0);
			param_1->SubMode = (TitleNewSbMdEnum)3;
		}
		}
		break;
	}
}

// FUNCTION: SADX 0x005a0070
void FUN_005a0070(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	if (*(int *)((char *)local_8 + 0x18) < 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	FUN_007d21b0((void *)3);
	title_new_disp((struct task *)local_8);
}

// FUNCTION: SADX 0x005a00d0
void title_new_disp(struct task *tp)
{
	if (!FUN_0040ae00())
	{
		DisplayFinTitle((struct TitleNewWk *)tp, ((struct TitleNewWk *)tp)->BaseZ);
	}
	DrawDXTitle((struct TitleNewWk *)tp);
}

// FUNCTION: SADX 0x005a06b0
void FreeAdvaTitleNewTask()
{
	if (DAT_05cda19c)
	{
		DestroyTask(DAT_05cda19c);
	}
}

// FUNCTION: SADX 0x005a06d0
void ChgSeqTitleNew()
{
	DAT_05cda19c->awp->work.ul[2] = 0xe;
}
