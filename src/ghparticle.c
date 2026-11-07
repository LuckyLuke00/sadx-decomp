#include "decls.h"
struct GHPARTICLE_UNIT;
int FUN_0060fb90(struct GHPARTICLE_UNIT *param_1, struct GHPARTICLE_INFO *param_2, struct GHSPRITE_ANIM_TABLE *param_3);
void control_disp(struct task *pTask);
void FUN_0060fb20(int param_1, int param_2);
struct GHPARTICLE_INFO;
struct GHSPRITE_ANIM_TABLE;
struct GHPARTICLE;

// STUB: SADX 0x0060f6a0
void ghParticleUnitInit(struct GHPARTICLE_UNIT *pUnit, struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVec)
{
}

// STUB: SADX 0x0060f750
void ghParticleMove(struct GHPARTICLE_UNIT *pPart, struct GHPARTICLE_INFO *pInfo)
{
}

// STUB: SADX 0x0060f7e0
void ghParticleSet(struct task *pTask, struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVec, float fStartFrame, float fOffsetZ)
{
}

// STUB: SADX 0x0060f8e0
struct task *ghParticleControlSet(int nMax, struct GHPARTICLE_INFO *pInfo, struct GHSPRITE_ANIM_TABLE *pAnimTable, long (*exec)(struct GHPARTICLE *, struct GHPARTICLE_INFO *, struct GHSPRITE_ANIM_TABLE *))
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0060fa10
void control_disp(struct task *pTask)
{
	char *local_10;
	struct anywk *local_8g;
	int local_cj;

	local_8g = pTask->awp;
	for (local_cj = 0; local_cj < local_8g->work.sw[0]; local_cj++)
	{
		local_10 = (char *)local_8g->work.ptr[3] + ((short *)local_8g->work.ptr[2])[local_cj] * 0x30;
		ghSpriteDraw_Unit3D_BillBoard((struct NJS_POINT3 *)local_10, (struct GHPARTICLE_UNIT *)local_10, (struct GHSPRITE_ANIM *)(local_10 + 0x20), *(struct GHSPRITE_ANIM_TABLE **)((char *)local_8g + 0x1c));
	}
}

// STUB: SADX 0x0060fa80
void control_exec(struct task *pTask)
{
}

// FUNCTION: SADX 0x0060fb20
void FUN_0060fb20(int param_1, int param_2)
{
	struct anywk *local_8;

	local_8 = ((struct task *)param_1)->awp;
	if (local_8->work.sw[0] <= 0)
	{
		return;
	}
	local_8->work.sw[0]--;
	((short *)local_8->work.ptr[1])[local_8->work.sw[0]] = ((short *)local_8->work.ptr[2])[param_2];
	((short *)local_8->work.ptr[2])[param_2] = ((short *)local_8->work.ptr[2])[local_8->work.sw[0]];
}

// FUNCTION: SADX 0x0060fb90
int FUN_0060fb90(struct GHPARTICLE_UNIT *param_1, struct GHPARTICLE_INFO *param_2, struct GHSPRITE_ANIM_TABLE *param_3)
{
	ghParticleMove(param_1, param_2);
	if (ghSpriteAnim((struct GHSPRITE_ANIM *)((char *)param_1 + 0x20), param_3) == -1)
	{
		return 0;
	}
	return 1;
}

// STUB: SADX 0x0060fbd0
void control_exec_exec(struct task *pTask)
{
}

// FUNCTION: SADX 0x0060fc70
void control_exit(struct task *pTask)
{
	struct anywk *local_8 = pTask->awp;
	Free(local_8->work.ptr[1]);
	Free(local_8->work.ptr[2]);
	Free(local_8->work.ptr[3]);
}
