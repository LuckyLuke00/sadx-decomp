#include "decls.h"
extern struct task *DAT_05edbc84;
extern int DAT_05edbc88;
extern int DAT_05edbc24;
extern int DAT_05edbc28;
extern int DAT_05edbc6c;
extern int DAT_05edbc60;
extern int DAT_05edbc64;
extern int DAT_05edbc10;
extern int DAT_05edbc2c[10];
extern int DAT_05eda290[0x60];
extern int DAT_05edbc80;
extern int DAT_05edbc70;
extern int DAT_05edbc14[4];
extern int DAT_05edbc74;
extern int DAT_05edbc78;
extern int DAT_05edbc7c;
extern int DAT_02639af4;

// FUNCTION: SADX 0x005a6240
int ClearDownload()
{
	int local_8;
	DAT_05edbc80 = 0;
	DAT_05edbc70 = 0;
	for (local_8 = 0; 4 > local_8; local_8++)
	{
		DAT_05edbc14[local_8] = 0;
	}
	DAT_05edbc74 = 0;
	DAT_05edbc78 = 0;
	DAT_05edbc7c = 0;
	DAT_02639af4 = 0x32;
	return 1;
}

// FUNCTION: SADX 0x005a62c0
int InitDownload()
{
	int local_8;

	DAT_05edbc24 = 0;
	DAT_05edbc28 = 0;
	DAT_05edbc6c = 0;
	DAT_05edbc60 = 0;
	DAT_05edbc64 = 0;
	DAT_05edbc10 = 0;
	local_8 = 0;
	while (1)
	{
		if (local_8 >= 10)
			break;
		DAT_05edbc2c[local_8] = 0;
		local_8 = local_8 + 1;
	}
	local_8 = 0;
	while (1)
	{
		if (local_8 >= 0x60)
			break;
		DAT_05eda290[local_8] = 0;
		local_8 = local_8 + 1;
	}
	return 1;
}

// FUNCTION: SADX 0x005a6360
int CloseDownload()
{
	if (DAT_05edbc88 != 0)
	{
		DestroyTask(DAT_05edbc84);
	}
	DAT_05edbc88 = 0;
	return 1;
}
