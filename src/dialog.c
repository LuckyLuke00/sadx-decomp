#include "decls.h"
void FUN_00576a60(int param_1);
extern struct task *DAT_05cd2600;

// FUNCTION: SADX 0x005761c0
void DialogExec()
{
	if (DAT_05cd2600 != 0)
	{
		dialog_exec(DAT_05cd2600);
		DAT_05cd2600->disp = 0;
	}
}

// FUNCTION: SADX 0x00576a10
void FUN_00576a10(int param_1)
{
	*(int *)(param_1 + 8) = 0;
	*(float *)(param_1 + 0xc) = 0.0f;
	*(float *)(param_1 + 0x10) = 0.0f;
	*(float *)(param_1 + 0x14) = 1.0f;
	*(short *)(param_1 + 0x24) = 0;
	*(short *)(param_1 + 0x26) = 0;
	FUN_00576a60(0);
	*(int *)(param_1 + 0x3c) = -1;
}

// STUB: SADX 0x00577850
struct task *SetDialogTask()
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x00577930
void FreeDialogTask()
{
	if (DAT_05cd2600 != 0)
	{
		DestroyTask(DAT_05cd2600);
		DAT_05cd2600 = 0;
	}
}

// STUB: SADX 0x00577a40
void OpenDialogCsrLet(struct DialogPrmType *dp, signed char csr, signed char *dis_csr_ptr)
{
}
