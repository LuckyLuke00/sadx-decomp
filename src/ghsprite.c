#include "decls.h"

// STUB: SADX 0x0060ecd0
void ghSpriteSetFrame2(struct GHSPRITE_ANIM *pAnim, struct GHSPRITE_ANIM_TABLE *pAnimTable, float fFrame)
{
}

// STUB: SADX 0x0060ed70
void ghSpriteAnimTableInit(struct NJS_TEXLIST *pList, struct GHSPRITE_ANIM_TABLE *pTable, int flag)
{
}

// FUNCTION: SADX 0x0060ee70
void ghSpriteAnimInit(struct GHSPRITE_ANIM *pAnim)
{
	*(float *)pAnim = 0.0f;
	*(float *)((char *)pAnim + 4) = 1.0f;
	*(int *)((char *)pAnim + 8) = 0;
	*(int *)((char *)pAnim + 0xc) = 0;
}

// STUB: SADX 0x0060eea0
void ghSpriteInit(struct GHSPRITE *pSpr, struct NJS_POINT3 *pPos, struct GHSPRITE_INIT_INFO *pInit, int flag)
{
}

// STUB: SADX 0x0060f060
int ghSpriteExec(struct GHSPRITE *pSpr)
{
	return (int)0;
}

// FUNCTION: SADX 0x0060f5e0
void spriteAutoDisp(struct task *pTask)
{
	struct anywk *local_8;
	local_8 = pTask->awp;
	ghSpriteDraw_Unit3D_BillBoard((NJS_POINT3 *)local_8->work.ptr[1], (GHPARTICLE_UNIT *)((char *)local_8 + 8), (GHSPRITE_ANIM *)((char *)local_8 + 0x34), (GHSPRITE_ANIM_TABLE *)local_8->work.ptr[0x30 / 4]);
}

// FUNCTION: SADX 0x0060f620
void spriteAutoExec(struct task *pTask)
{
	struct GHSPRITE *local_8;

	local_8 = (struct GHSPRITE *)pTask->awp;
	spriteAutoDisp(pTask);
	if (ghSpriteExec(local_8) == -1)
	{
		FreeTask(pTask);
	}
}

// FUNCTION: SADX 0x0060f660
void spriteAutoExec_Exec(struct task *pTask)
{
	struct anywk *local_8;

	local_8 = pTask->awp;
	spriteAutoDisp(pTask);
	if (((int (*)(struct anywk *))local_8->work.ptr[0])(local_8) == -1)
	{
		FreeTask(pTask);
	}
}
