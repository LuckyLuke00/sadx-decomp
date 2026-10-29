#include "decls.h"
extern struct Tex_anim_land_work *land_works[7];
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// STUB: SADX 0x00682130
void SSTexAnim(struct task *tp)
{
}

// FUNCTION: SADX 0x00682190
void CreateSSTexAnim(unsigned long type)
{
	struct task *local_4 = CreateElementalTask(2, 3, SSTexAnim);
	struct taskwk *local_8 = local_4->twp;
	local_8->mode = 0;
	local_8->counter.ptr = land_works[type];
	local_8->wtimer = (DAT_05b9d724 << 8) | DAT_05b9d744;
}
