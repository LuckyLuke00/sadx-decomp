#include "decls.h"
void SetInputP(unsigned char pno, signed char mode);
extern int DAT_05cd14f8;
void EV_NpcMilesStandByOff();

// FUNCTION: SADX 0x005aca60
void NpcMilesControlDestructor(struct task *tp)
{
	DAT_05cd14f8 = 0;
	EV_NpcMilesStandByOff();
}

// STUB: SADX 0x005aca80
int FUN_005aca80(void)
{
	return (int)0;
}

// STUB: SADX 0x005acab0
long ComeBackNpcMiles()
{
	return (long)0;
}

// FUNCTION: SADX 0x005acb60
struct task *CreateNpcMilesPlayerTask()
{
	struct task *local_8;
	if (DAT_05cd14f8 == 0)
	{
		return 0;
	}
	local_8 = CreateElementalTask(7, 1, MilesTalesPrower);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 9) = 2;
		*(unsigned char *)((char *)local_8->twp + 8) = 1;
	}
	return local_8;
}

// FUNCTION: SADX 0x005ad150
void SetPlayerFlyMode(unsigned char plno)
{
	struct csts *local_8g;
	struct playerwk *local_cg;

	local_8g = (struct csts *)DAT_05ba3328[plno];
	local_cg = GetPlayerWorkPointer(plno);
	if ((local_8g != 0) && (local_cg != 0))
	{
		local_8g->pos.z = 0.0f;
		local_8g->pos.y = 0.0f;
		local_8g->pos.x = 0.0f;
		local_cg->spd.z = 0.0f;
		local_cg->spd.y = 0.0f;
		local_cg->spd.x = 0.0f;
		SetInputP(plno, 0x30);
	}
}

// STUB: SADX 0x005ad7f0
float FUN_005ad7f0(float *param_1)
{
	return (float)0;
}

// STUB: SADX 0x005ad830
float FUN_005ad830(float *param_1, float *param_2)
{
	return (float)0;
}

// FUNCTION: SADX 0x005ada20
void GetPlayerSidePos(struct taskwk *twp, float dist, struct NJS_POINT3 *pos)
{
	float local_8g;
	float local_cg;

	if ((twp != 0) && (pos != 0))
	{
		local_8g = njSin(*(int *)((char *)twp + 0x18));
		local_cg = njCos(*(int *)((char *)twp + 0x18));
		pos->x = twp->pos.x - dist * local_cg;
		pos->y = twp->pos.y;
		pos->z = twp->pos.z - dist * local_8g;
	}
}

// FUNCTION: SADX 0x005adf30
int FUN_005adf30()
{
	if (DAT_05cd14ea == 1)
	{
		return 1;
	}
	if (SeqCheckFlag(0x48))
	{
		return 1;
	}
	if (EV_CheckExec(0x100))
	{
		if (!EV_CheckExec(0x1a))
		{
			return 1;
		}
	}
	if (SeqCheckFlag(0xa6))
	{
		if (!EV_CheckExec(0xd))
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x005adfb0
void NpcMilesSetStandByFlag(long flag)
{
	DAT_05cd14f4 = flag;
}

// STUB: SADX 0x005ae2a0
void * FUN_005ae2a0(void *param_1, unsigned char param_2)
{
	return (void *)0;
}
