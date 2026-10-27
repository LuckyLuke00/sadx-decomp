#include "decls.h"
struct NJS_TEXLIST;

// STUB: SADX 0x007e4140
void Bg_MiniCart(struct task *task_p)
{
}

#pragma optimize("", off)
// STUB: SADX 0x007e4160
void dispBg(struct task *task_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007e4230
void destBg(struct task *task_p)
{
	if (((struct BgTask *)task_p->mwp)->texList_p)
	{
		late_ReleaseTexture(((struct BgTask *)task_p->mwp)->texList_p);
	}
}

// FUNCTION: SADX 0x007e4250
void FUN_007e4250(void)
{
	le_SetLightIntensity(0, 0.8f, 0.9f, 0.2f);
	le_SetLightColor(0, 1.0f, 1.0f, 0.95f);
	le_SetLightDirection(0, 0.5f, -0.866025f, 0.0f);
}

// STUB: SADX 0x007e42c0
void execBg(struct task *task_p)
{
}

// STUB: SADX 0x007e4360
void FUN_007e4360(struct task *task_p)
{
}
