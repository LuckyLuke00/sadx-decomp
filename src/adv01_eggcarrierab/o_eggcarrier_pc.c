#include "decls.h"
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
void ecp_actman(struct task *task_p)
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

// STUB: SADX 0x00694120
void ECPeopleInitialize()
{
}
