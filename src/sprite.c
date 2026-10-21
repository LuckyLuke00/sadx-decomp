#include "decls.h"
extern struct sp_task *DAT_05edbcb4;
extern unsigned long DAT_05edbcc4;
extern int DAT_05edbcb8;
extern int DAT_05edbcbc;
extern void FUN_005a63e0(struct sp_task *param_1, unsigned long param_2);
extern float DAT_05edbcc8;

// FUNCTION: SADX 0x005a6390
void SpInitialize(struct sp_task *buffer, unsigned long size)
{
	DAT_05edbcb4 = buffer;
	DAT_05edbcc4 = size;
	FUN_005a63e0(DAT_05edbcb4, DAT_05edbcc4);
	DAT_05edbcb8 = 0;
	DAT_05edbcbc = 0;
	DAT_05edbcc8 = 0.0f;
}

// STUB: SADX 0x005a63e0
void FUN_005a63e0(struct sp_task *param_1, unsigned long param_2)
{
}

// FUNCTION: SADX 0x005a64e0
void SpFreeTask(struct sp_task *tp)
{
	tp->exec = 0;
}

// STUB: SADX 0x005a64f0
struct sp_link *SpCreateLinkW(struct sp_info *info, unsigned long wksize)
{
	return (struct sp_link *)0;
}

// FUNCTION: SADX 0x005a6560
void SpFreeLink(struct sp_link *link)
{
	if ((link->sysflag & 2) != 0)
	{
		return;
	}
	link->sysflag |= 2;
}

// FUNCTION: SADX 0x005a6940
void SpDestroyAll()
{
	int local_cg;
	int local_8g;

	FUN_005a63e0(DAT_05edbcb4, DAT_05edbcc4);
	local_cg = DAT_05edbcb8;
	while (local_cg != 0)
	{
		local_8g = *(int *)local_cg;
		Free((void *)local_cg);
		local_cg = local_8g;
	}
	DAT_05edbcb8 = 0;
	DAT_05edbcbc = 0;
}

// FUNCTION: SADX 0x005a6a30
void SpSetZOffset(float offset)
{
	DAT_05edbcc8 = offset;
}
