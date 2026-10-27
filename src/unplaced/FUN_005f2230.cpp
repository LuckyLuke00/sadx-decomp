#include "decls.h"
extern void *DAT_05edd88c;
extern void *DAT_05edd884;
void FUN_005f24e0(void *param_1);
void FUN_005f34f0(void *param_1);
void FUN_005f3310(float);
void FUN_005f2320(struct task *);
extern struct task *DAT_05edd888;
void FUN_005f2850(struct task *);

// FUNCTION: SADX 0x005f2230
void FUN_005f2230(void)
{
	DAT_05edd870->awp->work.ul[1] = 5;
}

// FUNCTION: SADX 0x005f2250
struct task *FUN_005f2250(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005f2320);
	DAT_05edd888 = local_8g;
	if (DAT_05edd888 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, param_1);
		local_8g->exec = FUN_005f2320;
		local_8g->disp = FUN_005f2850;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005f22c0
void FUN_005f22c0(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	*(int *)((char *)local_8 + 4) = *(int *)((char *)param_2 + 0);
	*(int *)((char *)local_8 + 8) = *(int *)((char *)param_2 + 4);
	*(int *)((char *)local_8 + 0xc) = *(int *)((char *)param_2 + 8);
	*(float *)((char *)local_8 + 0x10) = 5300.0f;
	*(int *)((char *)local_8 + 0) = 0;
	*(char *)((char *)local_8 + 0x26) = 0;
	FUN_005f34f0(local_8);
}

// STUB: SADX 0x005f2320
void FUN_005f2320(struct task *tp)
{
}

// STUB: SADX 0x005f24e0
void FUN_005f24e0(void *param_1)
{
}

// FUNCTION: SADX 0x005f32f0
void FUN_005f32f0(struct task *param_1)
{
	FUN_005f3310(*(float *)((char *)param_1 + 0x10));
}

// FUNCTION: SADX 0x005f3310
void FUN_005f3310(float param_1)
{
	float local_8g;
	float local_cg;

	___njSetTexture(&texlist_ava_new_menu);
	ghSetPvrTexMaterial(0xffffffff);
	local_cg = 0.0f;
	local_8g = -18.0f;
	DrawTexture(0, 0, 0x280, 0x1e0, 0.99f, (Magic::RenderCore::Texture *)DAT_05edd884, 0.0f, 0.0f, 1.0f, 1.0f, -1);
	___njSetTexture(&texlist_ava_new_menu);
}

// FUNCTION: SADX 0x005f3390
void FUN_005f3390()
{
	void *local_8g;
	void *local_cj;
	void *local_14;
	void *local_10;

	if (DAT_05edd888)
	{
		DestroyTask(DAT_05edd888);
	}
	if (DAT_05edd884)
	{
		FUN_0041c2d0(DAT_05edd884);
		local_cj = DAT_05edd884;
		local_8g = local_cj;
		local_8g ? (*(void *(__thiscall *)(void *, int))**(void ***)local_8g)(local_8g, 1) : 0;
		DAT_05edd884 = 0;
	}
	if (DAT_05edd88c)
	{
		FUN_0041c2d0(DAT_05edd88c);
		local_14 = DAT_05edd88c;
		local_10 = local_14;
		local_10 ? (*(void *(__thiscall *)(void *, int))**(void ***)local_10)(local_10, 1) : 0;
		DAT_05edd88c = 0;
	}
}

// FUNCTION: SADX 0x005f3460
void FUN_005f3460(void)
{
	DAT_05edd888->awp->work.ul[1] = 5;
}
