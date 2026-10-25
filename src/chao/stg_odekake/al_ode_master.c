#include "decls.h"
extern void *DAT_05b330e4;
void FUN_0047a9f0();
void AL_GBAManagerSleep();
void Free(void *mp);

// STUB: SADX 0x0047aa10
void AL_OdekakeMenuMaster(struct task *tp)
{
}

// FUNCTION: SADX 0x0047aab0
void AL_OdekakeMenuMasterDestructor(struct task *tp)
{
	if (DAT_05b330e4 != 0)
	{
		FUN_0047a9f0();
		Free((void *)DAT_05b330e4);
		DAT_05b330e4 = 0;
	}
	AL_GBAManagerSleep();
}

// FUNCTION: SADX 0x0047aae0
void AL_OdeMenuSetNextStage(enum OdeMenuStage stage)
{
	if (DAT_05b330e4 != 0)
	{
		*(int *)((char *)DAT_05b330e4 + 8) = (int)stage;
	}
}

// STUB: SADX 0x0047ab00
void AL_OdeMenuChangeStage()
{
}

// FUNCTION: SADX 0x0047ab80
long AL_OdeMenuGetMode()
{
	if (DAT_05b330e4)
	{
		return *(int *)((char *)DAT_05b330e4 + 0xc);
	}
	return -1;
}

// FUNCTION: SADX 0x0047aba0
void AL_OdeMenuSetMode(long mode)
{
	if (DAT_05b330e4 != 0)
	{
		*(int *)((char *)DAT_05b330e4 + 0xc) = (int)mode;
		*(int *)((char *)DAT_05b330e4 + 0x10) = 0;
		*(int *)((char *)DAT_05b330e4 + 0x14) = 0;
	}
}

// FUNCTION: SADX 0x0047abd0
long AL_OdeMenuIsEnd()
{
	if (DAT_05b330e4 != 0)
	{
		return *(long *)((char *)DAT_05b330e4 + 0x20);
	}
	return 0;
}

// FUNCTION: SADX 0x0047abe0
void AL_OdeMenuSetEnd()
{
	if (DAT_05b330e4)
	{
		*(int *)((char *)DAT_05b330e4 + 0x20) = 1;
	}
}

// FUNCTION: SADX 0x0047ac00
enum OdeMenuState AL_OdeMenuGetState()
{
	if (DAT_05b330e4 != 0)
	{
		return *(enum OdeMenuState *)((char *)DAT_05b330e4 + 0x1c);
	}
	return ODE_MENU_STATE_FAIL;
}

// FUNCTION: SADX 0x0047ac20
void AL_OdeMenuSetStateBusy()
{
	if (DAT_05b330e4 != 0)
	{
		*(int *)((char *)DAT_05b330e4 + 0x1c) = 1;
	}
}

// FUNCTION: SADX 0x0047ac40
void CreateOdekakeMenuMaster()
{
	struct task *var1;

	if (DAT_05b330e4 == 0)
	{
		DAT_05b330e4 = CAlloc(1, 0x38);
		if (DAT_05b330e4 != 0)
		{
			var1 = CreateElementalTask(2, 2, AL_OdekakeMenuMaster);
			*(struct task **)((char *)DAT_05b330e4 + 0x2c) = var1;
			*(int *)((char *)DAT_05b330e4 + 0x28) = 2;
			var1->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
			var1->dest = AL_OdekakeMenuMasterDestructor;
			CreateOdeBG();
			FUN_00441fb0();
		}
	}
}
