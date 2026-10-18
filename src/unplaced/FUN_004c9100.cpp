#include "decls.h"

extern unsigned short DAT_05b9d724;
extern void (*DAT_025d7530[43])(struct task *);
extern struct task *DAT_05b3eab4;
extern void (*DAT_025d77e8[43])(struct task *);

// FUNCTION: SADX 0x004c9100
void FUN_004c9100()
{
	if (DAT_025d7530[(short)DAT_05b9d724] != 0)
	{
		if ((short)DAT_05b9d724 == 0x13)
		{
			DAT_05b3eab4 = CreateElementalTask(2, 1, DAT_025d7530[(short)DAT_05b9d724]);
		}
		else
		{
			DAT_05b3eab4 = CreateElementalTask(2, 0, DAT_025d7530[(short)DAT_05b9d724]);
		}
	}
	else
	{
		DAT_05b3eab4 = 0;
	}
}

// FUNCTION: SADX 0x004c9170
void FUN_004c9170()
{
	___njSetBackColor(((unsigned long (*)[3])BackColorList)[(short)DAT_05b9d724][0], ((unsigned long (*)[3])BackColorList)[(short)DAT_05b9d724][1], ((unsigned long (*)[3])BackColorList)[(short)DAT_05b9d724][2]);
	if (DAT_025d77e8[(short)DAT_05b9d724] != 0)
	{
		CreateElementalTask(2, 1, DAT_025d77e8[(short)DAT_05b9d724]);
	}
}
