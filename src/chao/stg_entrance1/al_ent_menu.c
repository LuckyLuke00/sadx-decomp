#include "decls.h"
void FUN_0044daf0(void);
extern void *DAT_05b33018;

// FUNCTION: SADX 0x004728c0
void AL_EntranceMenuManagerDestructor(struct task *tp)
{
	FreeTaskC(tp);
	FUN_0044db20();
	FUN_0044c4b0(*(void **)((char *)DAT_05b33018 + 0x114));
	Free(DAT_05b33018);
	DAT_05b33018 = 0;
}

// FUNCTION: SADX 0x00472900
void AL_EntranceMenuCreate()
{
	struct task *var1;

	if (DAT_05b33018 == 0)
	{
		var1 = CreateElementalTask(2, 5, AL_EntranceMenuManagerExecutor);
		DAT_05b33018 = CAlloc(1, 0x118);
		*(int *)((char *)DAT_05b33018 + 0xe8) = (int)var1;
		var1->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->dest = AL_EntranceMenuManagerDestructor;
		*(int *)((char *)DAT_05b33018 + 0x18) = 1;
		*(unsigned long *)((char *)DAT_05b33018 + 0x114) = (unsigned long)AlMsgStrLoad("ChaoDX_Message_Race");
		FUN_0044daf0();
		AlMsgFontColorSet(0, 0xffffffff);
	}
}
