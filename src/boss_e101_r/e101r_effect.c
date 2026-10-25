#include "decls.h"
void FUN_0070e240(struct GHPARTICLE *param_1);
extern struct task *DAT_060c4a9c;
void FUN_0070e240(struct GHPARTICLE *param_1);
struct GHPARTICLE;
extern struct task *DAT_060c4aa0;
extern struct task *DAT_060c4aa4;

// STUB: SADX 0x0070dbf0
void E101R_Spark(struct NJS_POINT3 *pPos, float fRange)
{
}

// STUB: SADX 0x0070de60
void E101R_Bomb(struct NJS_POINT3 *pPos, float fRadius)
{
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

// STUB: SADX 0x0070e650
void E101R_EfShotFlickInit()
{
}

// FUNCTION: SADX 0x0070e6b0
void E101R_EfShotFlickExit()
{
	if (DAT_060c4a9c)
	{
		FreeTask(DAT_060c4a9c);
	}
}
