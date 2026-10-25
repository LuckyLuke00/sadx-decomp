#include "decls.h"
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2);
void inetdemo_disp(struct task *tp);
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9a4;

// FUNCTION: SADX 0x005fe0a0
struct task *SetAdvaInetDemoTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(8, 3, inetdemo_exec);
	DAT_05edd9a4 = local_8g;
	if (DAT_05edd9a4)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005fe110(local_8g, prmp);
		local_8g->exec = inetdemo_exec;
		local_8g->disp = inetdemo_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005fe110
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;
	local_8 = param_1->awp;
	*(int *)((char *)local_8 + 4) = *(int *)param_2;
	*(int *)((char *)local_8 + 8) = *(int *)((char *)param_2 + 4);
	*(float *)((char *)local_8 + 12) = 5400.0f;
	*(int *)local_8 = 0;
	*(int *)((char *)local_8 + 0x18) = 0;
}

// FUNCTION: SADX 0x005fe2f0
void FUN_005fe2f0(int param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_INETDEMO);
	*(int *)(param_1 + 0x18) = 0;
	SetAdvaBGM(0x37);
}

// STUB: SADX 0x005fe320
void inetdemo_sub_exec(struct InetDemoWk *wkp)
{
}

// FUNCTION: SADX 0x005fe3f0
void inetdemo_disp(struct task *tp)
{
	struct InetDemoWk *local_8;

	local_8 = (struct InetDemoWk *)tp->awp;
	if (local_8->BaseCol == 0)
	{
		return;
	}
	if (local_8->SubMode < 2)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(0xffffffff);
	DisplayDemoPictures(&texlist_ava_inetdemo, local_8, local_8->BaseZ, (struct DEMOPICTUREINFO *)&demopictures, 0x2e);
}

// STUB: SADX 0x005feeb0
void DisplayFullScreen(long pvrindex, float posz)
{
}

// STUB: SADX 0x005ff3b0
unsigned long CalcBetweenMaterial(unsigned long undermat, unsigned long uppermat, float f)
{
	return (unsigned long)0;
}

// STUB: SADX 0x005ff7b0
void DrawSprite2DRA(unsigned long material, struct NJS_TEXLIST *tlist, short pvrindex, float posx, float posy, float posz, float sclx, float scly, long rot)
{
}

// FUNCTION: SADX 0x005ff890
void FreeAdvaInetDemoTask()
{
	if (DAT_05edd9a4)
	{
		DestroyTask(DAT_05edd9a4);
	}
}
