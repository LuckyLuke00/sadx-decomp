#include "decls.h"
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

// STUB: SADX 0x0060fa80
void control_exec(struct task *pTask)
{
}

// STUB: SADX 0x0060fb20
void FUN_0060fb20(int param_1, int param_2)
{
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
