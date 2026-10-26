#include "decls.h"
struct NJS_POINT2;
struct NJS_POINT3;
struct taskwk;
extern float DAT_00956608;

// STUB: SADX 0x007e4140
void Bg_MiniCart(struct task *task_p)
{
}

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
	le_SetLightIntensity(0, 0.8f, DAT_00956608, 0.2f);
	le_SetLightColor(0, 1.0f, 1.0f, 0.95f);
	le_SetLightDirection(0, 0.5f, -0.866025f, 0.0f);
}
