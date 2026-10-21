#include "decls.h"

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

// FUNCTION: SADX 0x0060fc70
void control_exit(struct task *pTask)
{
	struct anywk *local_8 = pTask->awp;
	Free(local_8->work.ptr[1]);
	Free(local_8->work.ptr[2]);
	Free(local_8->work.ptr[3]);
}
