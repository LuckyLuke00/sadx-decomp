#include "decls.h"
struct CRUSHLIGHT_WK;

// STUB: SADX 0x008c2050
void CreateCrushLight(struct NJS_POINT3 *pPos, struct CRUSHLIGHT_DATA *pCrushLightData)
{
}

// STUB: SADX 0x008c21e0
void execCrushLight(struct task *pTask)
{
}

#pragma optimize("", off)
// STUB: SADX 0x008c22b0
void rotate(struct CRUSHLIGHT_WK *pCrushWk)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008c23b0
void execDeathCrushLight(struct task *pTask)
{
	struct anywk *local_8;
	local_8 = pTask->awp;
	rotate((struct CRUSHLIGHT_WK *)local_8);
	local_8->work.f[3] = local_8->work.f[3] - 0.1f;
	if (local_8->work.f[3] <= 0.0f)
	{
		local_8->work.f[3] = 0.0f;
		FreeTask(pTask);
	}
	dispCrushLight(pTask);
}

#pragma optimize("", off)
// STUB: SADX 0x008c2420
void dispCrushLight(struct task *pTask)
{
}
#pragma optimize("", on)

// STUB: SADX 0x008c2830
float FUN_008c2830(float *param_1, float *param_2, float param_3, float param_4)
{
	return (float)0;
}
