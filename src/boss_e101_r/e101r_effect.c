#include "decls.h"
void FUN_0060d560(struct NJS_POINT3 *param_1, float param_2);
void FUN_0070e240(struct GHPARTICLE *param_1);
void FUN_0060d560(struct NJS_POINT3 *, float);
extern "C" int rand(void);
static void exec_Lightning(struct task *pTask);
struct GHPARTICLE_INFO {
	float fLife;
	float fLifeEnd;
};
void FUN_0070e240(struct GHPARTICLE *param_1);
extern struct task *DAT_060c4a9c;
void FUN_0070e240(struct GHPARTICLE *param_1);
struct GHPARTICLE;
extern struct task *DAT_060c4aa0;
extern struct task *DAT_060c4aa4;

#pragma optimize("", off)
// STUB: SADX 0x0070dab0
static void exec_Lightning(struct task *pTask)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0070dbc0
void E101R_Lightning(struct NJS_POINT3 *pPos)
{
	struct task *var1;
	struct taskwk *var2;
	var1 = CreateElementalTask(2, 4, exec_Lightning);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->wtimer = 0x3c;
		var2->value.ptr = pPos;
	}
}

// STUB: SADX 0x0070dbf0
void E101R_Spark(struct NJS_POINT3 *pPos, float fRange)
{
}

// FUNCTION: SADX 0x0070de60
void E101R_Bomb(struct NJS_POINT3 *pPos, float fRadius)
{
	struct NJS_POINT3 pos;
	float local_18;

	pos.x = pPos->x;
	pos.y = pPos->y;
	pos.z = pPos->z;
	local_18 = (float)(rand() * 3.0517578125e-05);
	pos.x += fRadius * local_18 * 2.0 - fRadius;
	local_18 = (float)(rand() * 3.0517578125e-05);
	pos.y += fRadius * local_18 * 2.0 - fRadius;
	local_18 = (float)(rand() * 3.0517578125e-05);
	pos.z += fRadius * local_18 * 2.0 - fRadius;
	local_18 = (float)(rand() * 3.0517578125e-05);
	local_18 = local_18 * 0.4f + 0.3f;
	FUN_0060d560(&pos, local_18);
}

// STUB: SADX 0x0070df60
long moveWaveAccume(struct GHPARTICLE *pPart, struct GHPARTICLE_INFO *pInfo, struct GHSPRITE_ANIM_TABLE *pAnimTable)
{
	return (long)0;
}

// FUNCTION: SADX 0x0070e040
void E101R_EfWaveAccumeExit()
{
	if (DAT_060c4aa0)
	{
		FreeTask(DAT_060c4aa0);
	}
}

// STUB: SADX 0x0070e240
void FUN_0070e240(struct GHPARTICLE *pParticle)
{
}

// STUB: SADX 0x0070e320
void nozzleListExec(struct task *pTask)
{
}

// FUNCTION: SADX 0x0070e510
void E101R_NozzleLightExit()
{
	if (DAT_060c4aa4)
	{
		FreeTask(DAT_060c4aa4);
		DAT_060c4aa4 = 0;
	}
}

// FUNCTION: SADX 0x0070e530
void E101R_NozzleSetMode(enum NOZZLE_MODE mode)
{
	if (DAT_060c4aa4 != NULL)
	{
		*(int *)((char *)DAT_060c4aa4->awp + 0x10) = mode;
	}
}

// STUB: SADX 0x0070e550
void E101R_EfShotFlickPart(struct NJS_POINT3 *pPos)
{
}

// FUNCTION: SADX 0x0070e650
void E101R_EfShotFlickInit()
{
	struct GHPARTICLE_INFO local_c;
	ghSpriteAnimTableInit(&_texlist_e101r, &animtable_flick[0], 0);
	ghSpriteAnimTableInit(&_texlist_e101r, &animtable_flick_part[0], 0);
	local_c.fLife = 0.03f;
	local_c.fLifeEnd = 0.0f;
	DAT_060c4a9c = ghParticleControlSet(0x14, &local_c, &animtable_flick_part[0], 0);
}

// FUNCTION: SADX 0x0070e6b0
void E101R_EfShotFlickExit()
{
	if (DAT_060c4a9c)
	{
		FreeTask(DAT_060c4a9c);
	}
}
