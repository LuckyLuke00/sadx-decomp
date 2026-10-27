#include "decls.h"
void FUN_007d21b0(...);
extern long AL_GBAManagerIsExist(int PortNum, int ItemNum);
extern long AL_GBAManagerIsSelected(int PortNum, int ItemNum);
void AL_ClearSaveInfo(struct chao_save_info *pInfo);
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
void FUN_00441c20(int param_1, int param_2);
struct chao_save_info;
void FUN_004419d0(void *param_1);
extern struct task *DAT_05b06828;

// FUNCTION: SADX 0x004419b0
void AL_GBAManagerKill()
{
	struct task *var1;
	var1 = DAT_05b06828;
	if (var1 == 0)
		return;
	var1 = var1->ctp;
	if (var1 == 0)
		return;
	DestroyTask(var1);
}

// STUB: SADX 0x004419d0
void FUN_004419d0(void *param_1)
{
}

// FUNCTION: SADX 0x00441a00
void AL_ClearSaveInfo(struct chao_save_info *pInfo)
{
	memset(pInfo, 0, 0x800);
	FUN_004419d0(pInfo);
}

// STUB: SADX 0x00441a20
void AL_GBAManagerClearPortData(int PortNum)
{
}

// STUB: SADX 0x00441a80
void FUN_00441a80(void)
{
}

// FUNCTION: SADX 0x00441be0
long AL_GBAManagerIsExist(int PortNum, int ItemNum)
{
	if (DAT_05b06828 != NULL)
	{
		return *(long *)((char *)DAT_05b06828 + (PortNum * 0x421 + ItemNum) * 4 + 0x5c);
	}
	return 0;
}

// FUNCTION: SADX 0x00441c00
long AL_GBAManagerIsSelected(int PortNum, int ItemNum)
{
	if (DAT_05b06828 != NULL)
	{
		return *(int *)((char *)DAT_05b06828 + 0x30 + (PortNum * 0x421 + ItemNum) * 4);
	}
	return 0;
}

// STUB: SADX 0x00441c20
void FUN_00441c20(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x00441f60
struct CHAO_PARAM_GC *AL_GBAManagerGetPortParam(long PortNum)
{
	if (DAT_05b06828 == NULL)
	{
		return NULL;
	}
	return (struct CHAO_PARAM_GC *)(((char *)DAT_05b06828) + (PortNum * 0x1084) + 0x9c);
}

// FUNCTION: SADX 0x00441f80
void AL_GBAManagerDestructor(struct task *tp)
{
	___OutputDebugString("\nGBAManagerDestruct\n\n");
	if (DAT_05b06828)
	{
		Free(DAT_05b06828);
		DAT_05b06828 = 0;
	}
	FUN_007d21b0(tp);
}

// FUNCTION: SADX 0x00441ff0
void AL_GBAManagerSleep()
{
	if (DAT_05b06828)
	{
		DAT_05b06828->next = 0;
	}
}

// FUNCTION: SADX 0x00442000
long AL_GBAManagerIsBusy()
{
	if (DAT_05b06828 != 0)
	{
		return (long)DAT_05b06828->ptp;
	}
	return 1;
}

// FUNCTION: SADX 0x00442020
enum GBAPortKind AL_GBAManagerGetPortKind(int PortNum)
{
	if (DAT_05b06828 != 0)
		return (enum GBAPortKind)*(unsigned short *)((char *)DAT_05b06828 + PortNum * 0x1084 + 0x20);
	return (enum GBAPortKind)0;
}

// STUB: SADX 0x00442040
void AL_GBAManagerSetOdekakeChaoParam(struct CHAO_PARAM_GC *pParam)
{
}

// FUNCTION: SADX 0x00442060
void AL_GBAManagerClearChaoParam()
{
	struct task *var1 = DAT_05b06828;
	if (var1 != NULL)
	{
		var1->exec = NULL;
		var1->disp = NULL;
	}
}

// FUNCTION: SADX 0x00442080
long AL_GBAManagerIsOdekake()
{
	if (DAT_05b06828)
	{
		return (long)DAT_05b06828->exec;
	}
	return 0;
}

// FUNCTION: SADX 0x00442090
struct CHAO_PARAM_GC *AL_GBAManagerGetChaoParam()
{
	if (DAT_05b06828)
	{
		return *(struct CHAO_PARAM_GC **)(&DAT_05b06828->disp);
	}
	return NULL;
}

// FUNCTION: SADX 0x004420a0
int FUN_004420a0()
{
	return -1;
}

// FUNCTION: SADX 0x004420b0
char FUN_004420b0()
{
	return '\xf0';
}

// FUNCTION: SADX 0x004420c0
void AL_GBAManagerCreate()
{
	struct task *var1;

	if (DAT_05b06828 == 0)
	{
		DAT_05b06828 = (struct task *)CAlloc(1, 0x4228);
		if (DAT_05b06828 != 0)
		{
			var1 = CreateElementalTask(2, 8, AL_GBAManagerExecutor);
			DAT_05b06828->ctp = var1;
			var1->dest = AL_GBAManagerDestructor;
			FUN_007d21b0();
		}
		___OutputDebugString("\nGBAManagerCreate\n\n");
	}
}

// FUNCTION: SADX 0x00442120
long AL_ToridasuCountSelectedChao()
{
	long var1;
	int var2;

	var1 = 0;
	for (var2 = 1; var2 < 4; var2++)
	{
		var1 += (long)AL_GBAManagerIsSelected(var2, 1) != 0;
		var1 += (long)AL_GBAManagerIsSelected(var2, 0) != 0;
	}
	return var1;
}
