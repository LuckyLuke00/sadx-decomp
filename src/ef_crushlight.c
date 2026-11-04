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

// STUB: SADX 0x008c22b0
void rotate(struct CRUSHLIGHT_WK *pCrushWk)
{
}

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

// FUNCTION: SADX 0x008c2420
void dispCrushLight(struct task *pTask)
{
	struct anywk *local_8g;
	float fWidth[2];
	local_8g = pTask->awp;
	fWidth[0] = local_8g->work.f[3] * *(float *)((char *)local_8g + 0x44);
	fWidth[1] = local_8g->work.f[3] * *(float *)((char *)local_8g + 0x48);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	DrawWideLine3D((struct NJS_POINT3 *)local_8g->work.ptr[6], (struct Angle3 *)((char *)local_8g + 0x1c), fWidth, (union NJS_COLOR *)((char *)local_8g + 0x4c), *(float *)((char *)local_8g + 0x54) * local_8g->work.f[4]);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x008c2830
float FUN_008c2830(float *param_1, float *param_2, float param_3, float param_4)
{
	return (float)0;
}
