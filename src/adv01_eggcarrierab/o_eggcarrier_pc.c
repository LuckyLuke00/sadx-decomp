#include "decls.h"

// GLOBAL: SADX 0x026dfe18
static const struct HintMessageTable *ECHintTablePointer[5];

static void ecp_actman(struct task *task_p);
extern short DAT_05b9d744;
void ECPcSet();
void ECPcDelete();
extern int DAT_060b8320;
extern int DAT_060b8324;
extern int DAT_060b8328;
extern int DAT_060b832c;

// FUNCTION: SADX 0x00693830
void ECPcInitInit()
{
	DAT_060b832c = 0;
	DAT_060b8320 = 0;
	DAT_060b8324 = 0;
	DAT_060b8328 = 0;
}

#pragma optimize("", off)
// STUB: SADX 0x00693850
void ECPcDelete()
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00693fd0
void ECPcSet()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006940d0
static void ecp_actman(struct task *task_p)
{
	struct anywk *var1;
	int var2;
	var1 = task_p->awp;
	if (var1->work.ul[0] == 0)
	{
		var2 = DAT_05b9d744 & 0xff;
		ECPcSet();
		var1->work.ul[1] = var2;
		var1->work.ul[0] = 1;
	}
	else if (var1->work.ul[1] != (DAT_05b9d744 & 0xff))
	{
		ECPcDelete();
		var1->work.ul[0] = 0;
	}
}

// FUNCTION: SADX 0x00694120
void ECPeopleInitialize()
{
	struct task *local_8;
	void *local_4;
	int local_0;

	DAT_060b8320 = 0;
	DAT_060b8324 = 0;
	DAT_060b8328 = 0;
	HintMessageDataInit(ECHintTablePointer[DAT_05b3ebbc]);
	local_8 = CreateElementalTask(0, 1, ecp_actman);
	if (local_8 != 0)
	{
		local_4 = CAlloc(1, 8);
		if (local_4 != 0)
		{
			local_8->awp = (struct anywk *)local_4;
			if (*(int *)local_4 == 0)
			{
				local_0 = (short)DAT_05b9d744 & 0xff;
				ECPcSet();
				*(int *)((char *)local_4 + 4) = local_0;
				*(int *)local_4 = 1;
			}
			else
			{
				local_0 = (short)DAT_05b9d744 & 0xff;
				if (*(int *)((char *)local_4 + 4) != local_0)
				{
					ECPcDelete();
					*(int *)local_4 = 0;
				}
			}
		}
		else
		{
			DestroyTask(local_8);
		}
	}
}
