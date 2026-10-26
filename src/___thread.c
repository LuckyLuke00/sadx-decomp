#include "decls.h"
extern int DAT_05cda1d8;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern void *DAT_05eda1e0;
struct thread;
void *FUN_005a4c50(int param_1);
void TH_SetFunc(struct thread *tp, void (*func)(void *), void *pParam);
void FUN_005a4fe0(int param_1, int param_2, int param_3, int param_4);
void FUN_005a4d90(void);
void FUN_005a4f80(void *param_1, void *param_2, void *param_3);
void FUN_005a4db0(void *param_1);
void NextThread();
extern void *DAT_05eda1d8;
extern void *DAT_05eda1dc;
extern int DAT_05eda200[16];
extern int DAT_05cda1d4;
extern int DAT_05cda1d0;

// FUNCTION: SADX 0x005a4c00
void TH_Queue_Init()
{
	int local_8;
	for (local_8 = 0; local_8 < 0x10; local_8++)
	{
		DAT_05eda200[local_8] = (int)&DAT_05cda1d8 + local_8 * 0x20000;
	}
	DAT_05cda1d4 = 0xf;
	DAT_05cda1d0 = 0xf;
}

// FUNCTION: SADX 0x005a4c90
void FUN_005a4c90(int param_1)
{
	DAT_05cda1d0 = DAT_05cda1d0 + 1;
	if (DAT_05cda1d0 == 0x10)
	{
		DAT_05cda1d0 = 0;
	}
	DAT_05eda200[DAT_05cda1d0] = param_1;
}

// FUNCTION: SADX 0x005a4cd0
void TH_Init()
{
	TH_Queue_Init();
	memset(&DAT_05eda1dc, 0, 0x24);
	DAT_05eda1e0 = &DAT_05eda1dc;
	DAT_05eda1dc = DAT_05eda1e0;
	DAT_05eda1d8 = DAT_05eda1dc;
}

// FUNCTION: SADX 0x005a4d10
void NextThread()
{
	void *local_8;
	if (*(void **)((char *)DAT_05eda1d8 + 0xc) != 0)
	{
		local_8 = *(void **)((char *)DAT_05eda1d8 + 0xc);
	}
	else
	{
		local_8 = *(void **)DAT_05eda1d8;
		while (*(void **)((char *)local_8 + 8) != 0 && *(void **)((char *)*(void **)((char *)local_8 + 8) + 0xc) == local_8)
		{
			local_8 = *(void **)(*(void **)((char *)local_8 + 8));
		}
	}
	DAT_05eda1d8 = local_8;
}

// STUB: SADX 0x005a4d70
void FUN_005a4d70()
{
}

// FUNCTION: SADX 0x005a4d90
void FUN_005a4d90(void)
{
	FUN_005a4db0(DAT_05eda1d8);
}

// STUB: SADX 0x005a4e00
void FUN_005a4e00()
{
}

// FUNCTION: SADX 0x005a4ef0
void TH_DestroyAll()
{
	void *local_8;
	local_8 = DAT_05eda1dc;
	while (local_8 != (void *)&DAT_05eda1dc)
	{
		void *local_c;
		local_c = *(void **)local_8;
		FUN_005a4db0(local_8);
		local_8 = local_c;
	}
}

// FUNCTION: SADX 0x005a4f30
void TH_SetFunc(struct thread *tp, void (*func)(void *), void *pParam)
{
	if (!tp || tp == DAT_05eda1d8)
	{
		FUN_005a4f80(DAT_05eda1d8, func, pParam);
		FUN_005a4e00();
	}
	else
	{
		FUN_005a4f80(tp, func, pParam);
	}
}

// STUB: SADX 0x005a4f80
void FUN_005a4f80(void *param_1, void *param_2, void *param_3)
{
}

// STUB: SADX 0x005a4fa0
struct thread *TH_Create(void *func, void *pParam, unsigned int stack_size)
{
	return (struct thread *)0;
}

// FUNCTION: SADX 0x005a4fc0
void FUN_005a4fc0(int param_1, int param_2, int param_3, int param_4)
{
	FUN_005a4fe0(*(int *)(param_1 + 4), param_2, param_3, param_4);
}

// FUNCTION: SADX 0x005a5040
void *FUN_005a5040(void *param_1, void *param_2, int param_3)
{
	void *local_8;
	if (param_3 == 0)
	{
		param_3 = 0x20000;
	}
	local_8 = FUN_005a4c50(param_3);
	if (local_8 != 0)
	{
		*(int *)((char *)local_8 + 0x14) = (int)((char *)local_8 + param_3);
		*(int *)((char *)local_8 + 0xc) = 0;
		*(int *)((char *)local_8 + 8) = 0;
		*(int *)((char *)local_8 + 0x18) = 0;
		*(int *)((char *)local_8 + 0x20) = 0;
		*(int *)((char *)local_8 + 0x1c) = 0;
		TH_SetFunc((struct thread *)local_8, (void (*)(void *))param_1, param_2);
	}
	return local_8;
}

// STUB: SADX 0x005a50c0
struct thread *TH_CreateChild(struct thread *parent, void (*func)(void *), void *pParam, unsigned int stack_size)
{
	return (struct thread *)0;
}

// FUNCTION: SADX 0x005a5150
void *TH_GetWork(struct thread *tp)
{
	if (tp == 0)
		tp = (struct thread *)DAT_05eda1d8;
	tp = (struct thread *)((char *)tp + 0x24);
	return (void *)tp;
}

// FUNCTION: SADX 0x005a5170
void TH_SetStatus(struct thread *tp, long status)
{
	if (tp == 0)
		tp = (struct thread *)DAT_05eda1d8;
	*(long *)((char *)tp + 0x20) = status;
}

// FUNCTION: SADX 0x005a5190
int FUN_005a5190(int param_1)
{
	if (param_1 == 0)
	{
		param_1 = (int)DAT_05eda1d8;
	}
	return *(int *)((char *)param_1 + 0x20);
}

// FUNCTION: SADX 0x005a51b0
void TH_SetDest(struct thread *tp, void (*func)())
{
	if (tp == 0)
	{
		tp = (struct thread *)DAT_05eda1d8;
	}
	*(void (**)(void))((char *)tp + 0x18) = func;
}
