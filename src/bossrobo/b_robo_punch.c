#include "decls.h"
extern int DAT_060bcea0;
void punchColliSet();
void RoboPunch_Init();
extern int DAT_060bceb0;
extern int DAT_060bceb4;
extern int DAT_05b9d838;
extern int DAT_060bcea4;
extern int DAT_060bcea8;

// FUNCTION: SADX 0x006de450
void dest_colli(struct task *pTask)
{
	DAT_060bcea4 = 0;
	DAT_060bcea8 = 0;
}

// FUNCTION: SADX 0x006de460
void exec_colli(struct task *pTask)
{
	if (DAT_05b9d838 == 0 && DAT_060bcea8 != 0)
	{
		EntryColliList(pTask->twp);
	}
}

// STUB: SADX 0x006de490
void disp_ChainElec(struct task *pTask)
{
}

// FUNCTION: SADX 0x006de6d0
void dest_ChainElec(struct task *pTask)
{
	DAT_060bceb4 = 0;
	DAT_060bceb0 = 0;
}

// STUB: SADX 0x006df100
void punchColliSet()
{
}

// STUB: SADX 0x006df170
void RoboPunch_Init()
{
}

// FUNCTION: SADX 0x006df1f0
void FUN_006df1f0()
{
	DAT_060bcea0 = 0;
	punchColliSet();
	RoboPunch_Init();
}
