#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void AmyBirdInit(struct task *tp);

// FUNCTION: SADX 0x005d5780
struct task *AmyBirdStart()
{
	// GLOBAL: SADX 0x009979a8
	static const unsigned short DAT_009979a8[6] = { 0x0301, 0x0302, 0x0a00, 0x0c00, 0x0c01, 0x7fff };
	const unsigned short *local_4;
	struct task *local_8;
	unsigned short local_c;
	if (GetPlayerNumber() != 5)
	{
		return 0;
	}
	if (DAT_05b3e05c != 4 && DAT_05b3e05c != 5 && DAT_05b3e05c != 9)
	{
		return 0;
	}
	local_c = (unsigned short)((DAT_05b9d724 << 8) | DAT_05b9d744);
	if (local_c < 0xf00)
	{
		for (local_4 = DAT_009979a8; *local_4 != local_c; local_4++)
		{
			if (*local_4 == 0x7fff)
			{
				return 0;
			}
		}
	}
	else if (local_c >= 0x1a00 && local_c < 0x2300)
	{
		if (EV_CheckCansel())
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
	local_8 = CreateElementalTask(2, 3, AmyBirdInit);
	if (local_8 == 0)
	{
		return 0;
	}
	return local_8;
}

// FUNCTION: SADX 0x005d5870
void AmyBirdInit(struct task *tp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;

	local_cg = tp->twp;
	local_8g = DAT_05baf368[0];
	if (local_8g == 0)
	{
		FreeTask(tp);
	}
	local_cg->pos = local_8g->pos;
	*(float *)((char *)local_cg + 0x24) = *(float *)((char *)local_cg + 0x24) + 12.0f;
	*(int *)((char *)local_cg + 0x18) = 0x8000 - *(int *)((char *)local_8g + 0x18);
	tp->disp = AmyBirdDisplay;
	if ((((DAT_05b9d724 << 8) | (short)DAT_05b9d744) & 0xff00) == 0x300)
	{
		createMirrorTask(tp);
	}
	tp->exec = AmyBirdExe;
}
