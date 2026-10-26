#include "decls.h"
extern struct taskwk *DAT_05baf368[8];

// STUB: SADX 0x00458120
struct MOVE_WORK *MOV_Init(struct task *tp)
{
	return (struct MOVE_WORK *)0;
}

// STUB: SADX 0x004582c0
void MOV_SetVelo(struct task *tp, const struct NJS_POINT3 *pVelo)
{
}

// FUNCTION: SADX 0x004582e0
void MOV_ClearVelo(struct task *tp)
{
	struct motionwk *var1;

	var1 = tp->mwp;
	var1->spd.x = 0.0f;
	var1->spd.y = 0.0f;
	var1->spd.z = 0.0f;
}

// FUNCTION: SADX 0x00458300
void MOV_ClearAcc(struct task *tp)
{
	struct motionwk *var1;

	var1 = tp->mwp;
	var1->acc.x = 0.0f;
	var1->acc.y = 0.0f;
	var1->acc.z = 0.0f;
}

// FUNCTION: SADX 0x00458320
void MOV_SetGravity(struct task *tp, float gravity)
{
	*(float *)((char *)tp->mwp + 0x48) = gravity;
}

// STUB: SADX 0x00458330
void MOV_PreservePreviousPosition(struct task *tp)
{
}

// FUNCTION: SADX 0x00458350
void MOV_SetAimPos(struct task *tp, struct NJS_POINT3 *pPos)
{
	struct motionwk *var1 = tp->mwp;
	*(int *)((char *)var1 + 0x54) = *(int *)pPos;
	*(int *)((char *)var1 + 0x58) = *(int *)((char *)pPos + 4);
	*(int *)((char *)var1 + 0x5c) = *(int *)((char *)pPos + 8);
}

// STUB: SADX 0x00458370
float MOV_DistFromAim(struct task *tp)
{
	return (float)0;
}

// STUB: SADX 0x004583c0
float MOV_Dist2FromAim(struct task *tp)
{
	return (float)0;
}

// STUB: SADX 0x00458400
long FUN_00458400(int param_1)
{
	return (long)0;
}

// FUNCTION: SADX 0x00458430
long MOV_TurnToAim2(struct task *tp, long rot_spd)
{
	struct taskwk *var1;
	struct motionwk *var2;
	long var3;

	var1 = tp->twp;
	var2 = tp->mwp;
	var3 = FUN_00458400((int)tp);
	var2->ang_aim.y = var3;
	var3 = AdjustAngle(var1->ang.y, var3, rot_spd);
	var1->ang.y = var3;
	return DiffAngle(var2->ang_aim.y, var3);
}

// FUNCTION: SADX 0x00458470
float MOV_Dist2FromPlayer(struct task *tp, long player_num)
{
	struct taskwk *var1;
	struct taskwk *var2;

	var1 = tp->twp;
	var2 = DAT_05baf368[player_num];
	return (var2->pos.x - var1->pos.x) * (var2->pos.x - var1->pos.x) + (var2->pos.y - var1->pos.y) * (var2->pos.y - var1->pos.y) + (var2->pos.z - var1->pos.z) * (var2->pos.z - var1->pos.z);
}

// STUB: SADX 0x004584b0
long MOV_CalcPlayerAngle(struct task *tp, long player_num)
{
	return (long)0;
}

// FUNCTION: SADX 0x004584f0
long MOV_TurnToPlayer2(struct task *tp, long rot_spd, long player_num)
{
	struct taskwk *var1;
	struct motionwk *var2;
	long var3;
	long var4;

	var1 = tp->twp;
	var2 = tp->mwp;
	var3 = MOV_CalcPlayerAngle(tp, player_num);
	var2->ang_aim.y = var3;
	var4 = AdjustAngle(var1->ang.y, var3, rot_spd);
	var1->ang.y = var4;
	return DiffAngle(var2->ang_aim.y, var4);
}

// FUNCTION: SADX 0x00459c60
long MOV_DetectCollision(struct task *tp)
{
	struct motionwk *var1;
	struct taskwk *var2;

	var1 = tp->mwp;
	var2 = tp->twp;
	if (((*(unsigned char *)((char *)var1 + 0x40) & 0x10) == 0))
	{
		var2->flag &= 0xfffe;
		*(short *)((char *)var1 + 0x42) = 0;
		MOV_GetShadowPosXYZ(tp);
		MOV_CheckFloor(tp);
		MOV_CheckWall(tp);
	}
	return 0;
}
