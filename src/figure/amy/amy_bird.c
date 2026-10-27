#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void AmyBirdInit(struct task *tp);

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
