#include "decls.h"
static void disp(struct task *pTask);
static void _exec(struct task *pTask);
extern struct taskwk *DAT_05baf368[8];
extern struct NJS_POINT3COL locursor[];
extern int DAT_05b9d838;
extern int DAT_060bd1ac;
extern float DAT_060bd1a0;
extern float DAT_060bd1a4;
extern float DAT_060bd1a8;

// FUNCTION: SADX 0x006e1790
void RoboLockOnCursor_GetPos(struct NJS_POINT3 *pPos)
{
	pPos->x = DAT_060bd1a0;
	pPos->y = DAT_060bd1a4;
	pPos->z = DAT_060bd1a8;
}

// FUNCTION: SADX 0x006e17b0
void FUN_006e17b0()
{
	DAT_060bd1ac = 2;
}

// FUNCTION: SADX 0x006e17c0
void RoboLockOnCursor_Off()
{
	DAT_060bd1ac = 1;
}

// FUNCTION: SADX 0x006e17d0
static void disp(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		njPushMatrix(NULL);
		njTranslateV(NULL, (struct NJS_POINT3 *)&DAT_060bd1a0);
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		FUN_0067d2d0((float *)0, *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c));
		late_DrawLine3D(&locursor[0], 6, 0, 1);
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x006e1880
static void _exec(struct task *pTask)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006e1a80
void RoboLockOnCursor()
{
	struct task *var1 = CreateElementalTask(2, 4, _exec);
	if (var1 != 0)
	{
		struct taskwk *var2 = DAT_05baf368[0];
		DAT_060bd1a0 = var2->pos.x;
		DAT_060bd1ac = 0;
		DAT_060bd1a4 = var2->pos.y;
		DAT_060bd1a8 = var2->pos.z;
		var1->disp = disp;
	}
}
