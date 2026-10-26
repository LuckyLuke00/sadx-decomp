#include "decls.h"
void FUN_007d6940(struct task *);
int FUN_007d5120();
extern struct task *DAT_060cc340;

// FUNCTION: SADX 0x007d4f70
void deleteScanLine()
{
	if (DAT_060cc340)
	{
		FreeTask(DAT_060cc340);
		DAT_060cc340 = 0;
	}
}

// STUB: SADX 0x007d50e0
void dispScanLineTask(struct task *p_task)
{
}

// STUB: SADX 0x007d5120
int FUN_007d5120()
{
	return (int)0;
}

// FUNCTION: SADX 0x007d5140
int FUN_007d5140()
{
	return FUN_007d5120();
}

// FUNCTION: SADX 0x007d5150
void initScanLineTask(struct task *p_task)
{
	p_task->exec = (void (__cdecl *)(struct task *))FUN_007d5140;
	p_task->disp = (void (__cdecl *)(struct task *))FUN_007d5120;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x007d5170
void createScanLine(unsigned char a, unsigned char r, unsigned char g, unsigned char b, int res)
{
}
