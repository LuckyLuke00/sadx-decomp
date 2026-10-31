#include "decls.h"
extern struct task *DAT_05baf518;
extern void *DAT_05baf520;
extern void ___OutputDebugString(char *str, ...);
struct task;
struct task *FUN_004f3870(long level, void (*exec)(struct task *));
extern void *DAT_05baf4f4;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
void ExecTask(long level);
void ___OutputDebugString(char *str, ...);
extern void *DAT_05baf524;
extern void *DAT_05baf51c;
void FUN_004da910(int param_1);
void FUN_005b2480(int param_1);
void FreeTask(struct task *tp);
void FUN_004f3d40(void *param_1);
extern int DAT_05baf4d0[8];
extern int DAT_05baf4f8[8];

// FUNCTION: SADX 0x004f34a0
void setBtpToBtp_Pre()
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8++)
	{
		DAT_05baf4f8[local_8] = DAT_05baf4d0[local_8];
	}
}

// FUNCTION: SADX 0x004f34e0
void setBtp_PreToBtp()
{
	int local_8;

	for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
	{
		DAT_05baf4d0[local_8] = DAT_05baf4f8[local_8];
	}
}

// FUNCTION: SADX 0x004f3520
long checkdestroytaskc(struct task *tp, struct task *ctp)
{
	while (ctp != 0)
	{
		if (ctp == tp)
		{
			return 1;
		}
		if (ctp->ctp != 0)
		{
			if (checkdestroytaskc(tp, ctp->ctp))
			{
				return 1;
			}
		}
		ctp = ctp->next;
	}
	return 0;
}

// FUNCTION: SADX 0x004f3570
long checkdestroytask(struct task *tp)
{
	int local_8g;
	struct task *local_cg;

	for (local_8g = 0; local_8g < 8; local_8g++)
	{
		local_cg = (struct task *)DAT_05baf4d0[local_8g];
		while (local_cg != 0)
		{
			if (local_cg == tp)
			{
				return 1;
			}
			if (local_cg->ctp != 0)
			{
				if (checkdestroytaskc(tp, local_cg->ctp) != 0)
				{
					return 1;
				}
			}
			local_cg = local_cg->next;
		}
	}
	___OutputDebugString("???????S???@\n");
	return 0;
}

// STUB: SADX 0x004f3600
void InitTask()
{
}

// STUB: SADX 0x004f3750
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *))
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x004f3870
struct task *FUN_004f3870(long param_1, void (*param_2)(struct task *))
{
	struct task *local_cg;
	struct task *local_8g;
	if (DAT_05baf518 == 0)
	{
		return 0;
	}
	if (param_1 < 0 || param_1 >= 9)
	{
		return 0;
	}
	local_cg = DAT_05baf518;
	local_8g = local_cg->next;
	if (local_8g != 0)
	{
		local_8g->last = 0;
	}
	DAT_05baf518 = local_8g;
	if (param_2 != 0)
	{
		local_cg->exec = param_2;
	}
	else
	{
		local_cg->exec = (void (__cdecl *)(struct task *))FUN_005b5aa0;
	}
	if (param_1 != 7)
	{
		if (param_1 == 8)
		{
			param_1 = 7;
		}
		if (DAT_05baf4d0[param_1] == 0)
		{
			DAT_05baf4d0[param_1] = (int)local_cg;
			local_cg->next = 0;
			local_cg->last = 0;
		}
		else
		{
			local_8g = (struct task *)DAT_05baf4d0[param_1];
			local_cg->last = 0;
			local_cg->next = local_8g;
			local_8g->last = local_cg;
			DAT_05baf4d0[param_1] = (int)local_cg;
		}
	}
	local_cg->ocp = 0;
	local_cg->twp = 0;
	local_cg->mwp = 0;
	local_cg->fwp = 0;
	local_cg->awp = 0;
	local_cg->disp = 0;
	local_cg->dest = 0;
	local_cg->ctp = 0;
	local_cg->ptp = 0;
	local_cg->thp = 0;
	return local_cg;
}

#pragma optimize("", off)
// STUB: SADX 0x004f39c0
void DestroyTask(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f3be0
void FreeTask(struct task *tp)
{
	if (!checkdestroytask(tp))
	{
		return;
	}
	tp->exec = DestroyTask;
}

// FUNCTION: SADX 0x004f3c10
void ExecTask(long level)
{
	struct task *local_10;
	void (*local_8g)(struct task *);
	struct task *local_cj;

	if (level == 8)
	{
		level = 7;
	}
	local_10 = (struct task *)DAT_05baf4d0[level];
	if (local_10 == 0)
	{
		return;
	}
	while (1)
	{
		local_8g = *(void (**)(struct task *))((char *)local_10 + 0x10);
		local_cj = local_10->next;
		if (local_cj == local_10)
		{
			___OutputDebugString("???????????????[?[?[?[?[?[!!!");
		}
		DAT_05baf520 = local_8g;
		if (local_8g != 0)
		{
			DAT_05baf524 = *(void **)((char *)local_10 + 0x30);
			local_8g(local_10);
			DAT_05baf524 = 0;
		}
		DAT_05baf520 = 0;
		local_10 = local_cj;
		if (local_10 == 0)
		{
			return;
		}
	}
}

// FUNCTION: SADX 0x004f3cc0
void FUN_004f3cc0(int param_1)
{
	struct task *local_10;
	void (*local_8g)(struct task *);
	struct task *local_cj;

	if (param_1 == 8)
	{
		param_1 = 7;
	}
	local_10 = (struct task *)DAT_05baf4d0[param_1];
	if (local_10 == 0)
	{
		return;
	}
	while (1)
	{
		local_8g = *(void (**)(struct task *))((char *)local_10 + 0x14);
		local_cj = local_10->next;
		if (local_8g != 0)
		{
			local_8g(local_10);
		}
		if (local_10->ctp != 0)
		{
			FUN_004f3d40(local_10);
		}
		local_10 = local_cj;
		if (local_10 == 0)
		{
			return;
		}
	}
}

// FUNCTION: SADX 0x004f3d40
void FUN_004f3d40(void *param_1)
{
	struct task *local_8g;
	struct task *local_10;
	void (*local_cj)(struct task *);

	local_8g = (struct task *)*(int *)((char *)param_1 + 0xc);
	if (local_8g == 0)
	{
		return;
	}
	while (1)
	{
		local_cj = *(void (**)(struct task *))((char *)local_8g + 0x14);
		local_10 = local_8g->next;
		if (local_cj != 0)
		{
			local_cj(local_8g);
		}
		if (local_8g->ctp != 0)
		{
			FUN_004f3d40(local_8g);
		}
		local_8g = local_10;
		if (local_8g == 0)
		{
			return;
		}
	}
}

// FUNCTION: SADX 0x004f3db0
void FUN_004f3db0(int param_1)
{
	struct task *local_10;
	struct task *local_8g;
	struct task *local_cj;

	if (param_1 == 8)
	{
		param_1 = 7;
	}
	local_10 = (struct task *)DAT_05baf4d0[param_1];
	if (local_10 == 0)
	{
		return;
	}
	while (1)
	{
		local_8g = (struct task *)local_10->exec;
		local_cj = local_10->next;
		if (local_8g != 0)
		{
			DestroyTask(local_10);
		}
		local_10 = local_cj;
		if (local_10 == 0)
		{
			return;
		}
	}
}

// STUB: SADX 0x004f3e20
void LoopTask()
{
}

// FUNCTION: SADX 0x004f3ec0
void DisplayTask()
{
	int iVar1;

	ResetMaterial();
	FUN_004f3cc0(8);
	for (iVar1 = 0; iVar1 < 7; iVar1 = iVar1 + 1)
	{
		FUN_004f3cc0(iVar1);
	}
}

// FUNCTION: SADX 0x004f3f00
void FUN_004f3f00(void)
{
	int local_8;

	for (local_8 = 0; local_8 < 7; local_8++)
	{
		FUN_004f3db0(local_8);
	}
}

// FUNCTION: SADX 0x004f3f30
void GenocideTask()
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
	{
		FUN_004f3db0(local_8);
	}
}

// FUNCTION: SADX 0x004f3f60
void FUN_004f3f60(void *param_1)
{
	int local_8g;
	struct task *local_14;
	struct task *local_cj;
	struct task *local_10;

	for (local_8g = 0; local_8g < 8; local_8g++)
	{
		if (local_8g == 8)
		{
			local_8g = 7;
		}
		local_14 = (struct task *)DAT_05baf4d0[local_8g];
		while (local_14 != 0)
		{
			local_cj = (struct task *)local_14->exec;
			local_10 = local_14->next;
			if (local_cj != 0 && local_14->thp == param_1)
			{
				FreeTask(local_14);
			}
			local_14 = local_10;
		}
	}
}

// FUNCTION: SADX 0x004f3fe0
void *FUN_004f3fe0()
{
	void *local_8 = CAlloc(1, 0x40);
	return local_8;
}

// FUNCTION: SADX 0x004f4000
void *FUN_004f4000()
{
	void *local_8 = CAlloc(2, 0x1c);
	return local_8;
}

// FUNCTION: SADX 0x004f4020
void *FUN_004f4020()
{
	void *local_8 = CAlloc(1, 0x10);
	return local_8;
}

// FUNCTION: SADX 0x004f4040
void FUN_004f4040(void *param_1)
{
	if (*(int *)((char *)*(void **)((char *)param_1 + 0x20) + 0x38) != 0)
	{
		FUN_004da910(*(int *)((char *)param_1 + 0x20));
	}
	if (*(int *)((char *)*(void **)((char *)param_1 + 0x20) + 0x3c) != 0)
	{
		FUN_005b2480(*(int *)((char *)param_1 + 0x20));
	}
	Free(*(void **)((char *)param_1 + 0x20));
	*(void **)((char *)param_1 + 0x20) = 0;
}

// FUNCTION: SADX 0x004f40a0
void FUN_004f40a0(void *param_1)
{
	Free(*(void **)((char *)param_1 + 0x24));
	*(void **)((char *)param_1 + 0x24) = 0;
}

// FUNCTION: SADX 0x004f40c0
void FUN_004f40c0(void *param_1)
{
	Free(*(void **)((char *)param_1 + 0x28));
	*(void **)((char *)param_1 + 0x28) = 0;
}

// FUNCTION: SADX 0x004f40e0
void FUN_004f40e0(void *param_1)
{
	Free(*(void **)((char *)param_1 + 0x2c));
	*(void **)((char *)param_1 + 0x2c) = 0;
}

// FUNCTION: SADX 0x004f4100
bool IsSafeTask(void *ptask)
{
	if (ptask < DAT_05baf51c || (void *)((char *)DAT_05baf51c + 0x10000200) <= ptask)
		return false;
	return true;
}

// FUNCTION: SADX 0x004f4130
void InitMemory()
{
	void *local_8;

	EventSeInitInit();
	if (DAT_05baf51c == 0)
	{
		DAT_05baf51c = _SOCMalloc(0x1000020, "..\\..\\src\\task.c", 0x3b1);
		memset(DAT_05baf51c, 0, 0x1000020);
	}
	DAT_05baf4f4 = DAT_05baf51c;
	local_8 = (char *)DAT_05baf51c + 0x1000000;
	*(void **)DAT_05baf4f4 = local_8;
	*(void **)((char *)DAT_05baf4f4 + 4) = 0;
	*(void **)((char *)DAT_05baf4f4 + 8) = local_8;
	*(void **)((char *)DAT_05baf4f4 + 0xc) = 0;
	*(void **)local_8 = 0;
	*(void **)((char *)local_8 + 4) = DAT_05baf4f4;
	*(void **)((char *)local_8 + 8) = 0;
	*(void **)((char *)local_8 + 0xc) = DAT_05baf4f4;
}

// STUB: SADX 0x004f41f0
void *MAlloc(unsigned int size)
{
	return (void *)0;
}

// FUNCTION: SADX 0x004f4390
void *CAlloc(unsigned int num, unsigned int size)
{
	unsigned int local_8g;
	unsigned int local_cj;
	unsigned int local_10m;
	unsigned int local_14;

	local_8g = ((size + 3) & 0xfffffffc) * num;
	local_cj = (unsigned int)MAlloc(local_8g);
	if (local_cj != 0)
	{
		local_10m = local_cj;
		for (local_14 = local_8g >> 2; local_14 != 0; local_14--)
		{
			*(unsigned int *)local_10m = 0;
			local_10m = local_10m + 4;
		}
	}
	return (void *)local_cj;
}

#pragma optimize("", off)
// STUB: SADX 0x004f4400
void Free(void *mp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x004f45c0
struct task *CreateChildTask(unsigned short im, void (*exec)(struct task *), struct task *tp)
{
	return (struct task *)0;
}

// STUB: SADX 0x004f46a0
struct task *CreateChildrenTask(struct childtaskset *ctsp, struct task *tp)
{
	return (struct task *)0;
}

// STUB: SADX 0x004f48b0
void FreeTaskC(struct task *tp)
{
}

// FUNCTION: SADX 0x004f49a0
void LoopTaskC(struct task *tp)
{
	struct task *local_cg = tp->ctp;
	struct task *local_8g;

	while (local_cg != 0)
	{
		local_8g = local_cg->next;

		DAT_05baf524 = local_cg->thp;
		local_cg->exec(local_cg);
		DAT_05baf524 = 0;
		local_cg = local_8g;
	}
}
