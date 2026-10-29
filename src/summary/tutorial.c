#include "decls.h"
extern unsigned char DAT_05cd27e8;
extern int DAT_05cd27f0;
extern int DAT_05cd14d4;
extern float DAT_05b36808;

// GLOBAL: SADX 0x0234f5ec
static unsigned char DAT_0234f5ec[7] = {5, 4, 3, 0, 1, 2, 20};

// FUNCTION: SADX 0x004960c0
long TutorialExit(void *Param)
{
	int var1;
	npSetZCompareMode(1);
	DAT_05cd14d4 = 1;
	if (DAT_05cd27e8 == 0)
	{
		var1 = GetAdvertisePlayerNumber((unsigned char)GetPlayerNumber());
	}
	else
	{
		var1 = DAT_05cd27f0;
	}
	BGM_Stop();
	Serif_Stop();
	LoopTask();
	ADX_Close();
	FreeDialogTask();
	GenocideTask();
	LoopTask();
	ReleaseTutorialBookTexture(var1);
	late_ReleaseTexture(&texlist_adv_window);
	late_ReleaseTexture(&texlist_ava_csr);
	late_ReleaseTexture(&DAT_025ddb78);
	FUN_004b6520((int)&texlist_tuto_cmn);
	late_ReleaseTexture(&texlist_tuto_cmn);
	if (DAT_05cd27e8 == 0)
	{
		___njReleaseTextureAll();
	}
	else
	{
		setBtp_PreToBtp();
		setPreflagstat();
	}
	FUN_007d21b0((void *)1);
	DAT_05cd14d4 = 0;
	return 1;
}

// STUB: SADX 0x00496390
void TutorialTaskDestructor(struct task *tp)
{
}

// FUNCTION: SADX 0x004963c0
void TutorialBgmTask(struct task *tp)
{
	int iVar1;
	if (DAT_05cd27e8 == 0)
	{
		iVar1 = GetAdvertisePlayerNumber((unsigned char)GetPlayerNumber());
	}
	else
	{
		iVar1 = DAT_05cd27f0;
	}
	if (iVar1 != -1)
	{
		BGM_Play(DAT_0234f5ec[iVar1]);
	}
	FreeTask(tp);
}

// STUB: SADX 0x00496400
void FUN_00496400(int param_1)
{
}

// FUNCTION: SADX 0x00496430
float MiTutoGetFade()
{
	return DAT_05b36808;
}

// FUNCTION: SADX 0x00496670
struct task *CreateTutorialTask(int level, int advplno)
{
	struct task *var1;
	struct task *var2;
	struct task *var3;
	struct anywk *var4;
	var1 = CreateElementalTask(2, level, TutorialTask);
	if (var1)
	{
		var4 = (struct anywk *)CAlloc(1, 0xc);
		var1->awp = var4;
		var2 = CreateTutorialMsgTask(level + 1, advplno, 0);
		var1->twp->ang.x = (long)var2;
		var3 = CreateTutorialBgTask(level + 1, advplno, 0);
		var1->twp->ang.y = (long)var3;
		var4->work.ptr[0] = (void *)var2;
		var4->work.ptr[1] = (void *)var2;
		var4->work.ub[8] = (unsigned char)advplno;
		var1->dest = TutorialTaskDestructor;
	}
	return var1;
}
