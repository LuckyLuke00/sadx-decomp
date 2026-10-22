#include "decls.h"
void DestroyTask(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void *CAlloc(unsigned int num, unsigned int size);
void adva_serifu_exec(struct task *tp);
extern int DAT_05b40a48;
extern int DAT_05cda194;
extern int DAT_05cda198;

// FUNCTION: SADX 0x0059f630
void AdvaSndCsrMove()
{
	dsPlay_oneshot(1, 0, 0, 0);
}

// FUNCTION: SADX 0x0059f650
void AdvaSndCsrClick()
{
	dsPlay_oneshot(2, 0, 0, 0);
}

// FUNCTION: SADX 0x0059f670
void AdvaSndCancel()
{
	dsPlay_oneshot(3, 0, 0, 0);
}

// FUNCTION: SADX 0x0059f690
void InitAdvaBGM()
{
	SetBankDir(0x2a);
	DAT_05cda198 = 0;
	DAT_05cda194 = DAT_05cda198;
}

// FUNCTION: SADX 0x0059f6c0
void EndAdvaBGM()
{
	if ((*(struct task *(*))&DAT_05cda198) != 0)
	{
		DestroyTask((*(struct task *(*))&DAT_05cda198));
		(*(struct task *(*))&DAT_05cda198) = 0;
	}
	if ((*(struct task *(*))&DAT_05cda194) != 0)
	{
		DestroyTask((*(struct task *(*))&DAT_05cda194));
		(*(struct task *(*))&DAT_05cda194) = 0;
	}
	ADX_Close();
}

// FUNCTION: SADX 0x0059f710
void StopAdvaBGM()
{
	BGM_Stop();
}

// FUNCTION: SADX 0x0059f720
int GetStatAdvaBGM()
{
	return BGM_Status();
}

// FUNCTION: SADX 0x0059f730
void SetAdvaBGM(int adxnum)
{
	struct task *local_8g;
	int *local_cg;

	EndAdvaBGM();
	ADXTaskInit();
	if (adxnum >= 0)
	{
		if (DAT_05cda194 == 0)
		{
			local_8g = CreateElementalTask(0, 4, adva_bgm_exec);
			DAT_05cda194 = (int)local_8g;
			if (DAT_05cda194 != 0)
			{
				local_cg = (int *)CAlloc(1, 8);
				local_8g->awp = (struct anywk *)local_cg;
				local_cg[0] = adxnum;
				local_cg[1] = 0;
			}
		}
	}
}

// FUNCTION: SADX 0x0059f7b0
void adva_bgm_exec(struct task *tp)
{
	struct anywk *local_8 = tp->awp;
	if ((local_8->work.sl[1]++ > 0) && (DAT_05b40a48 != 0))
	{
		BGM_Play((int)local_8->work.ptr[0]);
		DestroyTask(tp);
		DAT_05cda194 = 0;
	}
}

// FUNCTION: SADX 0x0059f810
void SetAdvaModeBGM(enum AvaBgmEnum num)
{
	SetAdvaBGM(AdvaBgmTbl[num]);
}

// FUNCTION: SADX 0x0059f830
int SetAdvaSerifuNum(int adxnum)
{
	struct task *local_8g;
	int *local_cg;
	if (DAT_05cda198 == 0)
	{
		local_8g = CreateElementalTask(0, 4, adva_serifu_exec);
		DAT_05cda198 = (int)local_8g;
		if (DAT_05cda198 != 0)
		{
			local_cg = (int *)CAlloc(1, 8);
			local_8g->awp = (struct anywk *)local_cg;
			*local_cg = adxnum;
			local_cg[1] = 0;
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x0059f8a0
void adva_serifu_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0059f930
int SetAdvaCharSelSerifu(enum AvaCharEnum chnum)
{
	return SetAdvaSerifuNum(AdvaCharSelSerifuTbl[chnum]);
}
