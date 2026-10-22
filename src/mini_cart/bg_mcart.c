#include "decls.h"

// STUB: SADX 0x007e4140
void Bg_MiniCart(struct task *task_p)
{
}

// STUB: SADX 0x007e4160
void dispBg(struct task *task_p)
{
}

// FUNCTION: SADX 0x007e4230
void destBg(struct task *task_p)
{
	if (*(int *)&task_p->mwp->spd.x)
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)(*(void **)&task_p->mwp->spd.x));
	}
}

// STUB: SADX 0x007e4250
void FUN_007e4250(void)
{
}
