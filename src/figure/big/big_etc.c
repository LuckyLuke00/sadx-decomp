#include "decls.h"
double njScalor(struct NJS_POINT3 *);
extern struct NJS_TEXLIST texlist_fishing;
void FUN_0058d570(float param_1);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern float DAT_05cd29a8;
extern float DAT_05cd29ac;
extern float DAT_05cd29b0;
extern int DAT_05cd29b4;
extern char DAT_05edd2e0[0x800];
void AddSakanaWeight(float weight, long kind);
void BigChkHighScore();
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern int DAT_05cd2990;
extern short DAT_05cd299c;
extern int DAT_05cd2994;
extern float DAT_05cd29a4;
extern float DAT_05cd2974;
extern float DAT_05cd29a0;
extern long action_button;
extern long jump_button;
extern char DAT_05b932f0[1024];
extern unsigned short DAT_05cd296c;
void FUN_0058d6a0();
extern void *DAT_05cd2980;
void FUN_00592520(struct task *);

// STUB: SADX 0x0058b9e0
void *SetFishingCursorTask(struct task *tp)
{
	return (void *)0;
}

// STUB: SADX 0x0058baf0
void fishingCursorCtrl(struct task *tp)
{
}

// STUB: SADX 0x0058c100
void FUN_0058c100(int param_1, int param_2)
{
}

// STUB: SADX 0x0058c220
int FUN_0058c220(int param_1, int param_2, float param_3, int param_4, float param_5)
{
	return (int)0;
}

// STUB: SADX 0x0058c3b0
void *SetFishingLureTask(struct task *tp)
{
	return (void *)0;
}

// FUNCTION: SADX 0x0058c480
long getLureKind()
{
	int local_8;
	local_8 = 0;
	if (SeqCheckFlag(0x1de))
	{
		local_8++;
	}
	if (SeqCheckFlag(0x1df))
	{
		local_8++;
	}
	if (SeqCheckFlag(0x1e0))
	{
		local_8++;
	}
	if (SeqCheckFlag(0x1e1))
	{
		local_8++;
	}
	*(int *)((char *)DAT_05edd2e0 + 0x404) = local_8;
	return *(int *)((char *)DAT_05edd2e0 + 0x404);
}

// FUNCTION: SADX 0x0058c510
long chkLureDistance(struct NJS_POINT3 *rod_pos_p, struct NJS_POINT3 *lure_pos_p)
{
	struct NJS_POINT3 vec;
	vec.x = rod_pos_p->x - lure_pos_p->x;
	vec.z = rod_pos_p->z - lure_pos_p->z;
	vec.y = 0.0f;
	if ((((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x803))
	{
		if (njScalor(&vec) < 20.0)
		{
			if (DAT_05cd29a0 - 10.0 < lure_pos_p->y)
				return 1;
		}
	}
	else
	{
		if (njScalor(&vec) < 20.0)
			return 1;
	}
	return 0;
}

// STUB: SADX 0x0058d230
void exitFishingLure(struct task *tp)
{
}

// FUNCTION: SADX 0x0058d490
void dispHandleTexture(float *param_1, float *param_2)
{
	float sprite;
	sprite = njSqrt((param_1[0] - param_2[0]) * (param_1[0] - param_2[0]) + (param_1[1] - param_2[1]) * (param_1[1] - param_2[1]) + (param_1[2] - param_2[2]) * (param_1[2] - param_2[2]));
	DAT_05cd29a4 = sprite;
	if (DAT_05cd29a4 > DAT_05cd29a8)
	{
		DAT_05cd29a8 = DAT_05cd29a4;
	}
	if (DAT_05cd29a4 + 5.0f <= DAT_05cd29a8)
	{
		DAT_05cd29a8 = DAT_05cd29a4 + 5.0f;
	}
	FUN_0058d570(DAT_05cd29a8);
}

// FUNCTION: SADX 0x0058d680
void FUN_0058d680()
{
	___njSetTexture(&texlist_fishing);
	dispReelMeter();
	FUN_0058d6a0();
}

// STUB: SADX 0x0058dea0
long FUN_0058dea0(int param_1)
{
	return (long)0;
}

// STUB: SADX 0x0058e910
long chkKabeAngle2(struct task *tp, struct Angle3 *angle3_p)
{
	return (long)0;
}

// FUNCTION: SADX 0x0058f980
int FUN_0058f980()
{
	if (DAT_05cd2980 == 0)
		return 0;
	if ((DAT_05cd296c & 8) != 0)
		return 1;
	if ((DAT_05cd296c & 0x20) != 0)
		return 0;
	if ((DAT_05cd296c & 1) != 0)
	{
		if (((*(int *)&DAT_05b932f0[4] & action_button) == action_button) &&
			((*(int *)&DAT_05b932f0[4] & jump_button) == jump_button))
			return 1;
	}
	return 0;
}

// STUB: SADX 0x0058fa00
long iceWaterCheck()
{
	return (long)0;
}

// FUNCTION: SADX 0x0058fcb0
void setLureSetup(struct task *tp)
{
	struct taskwk *local_8g;
	struct anywk *local_cg;

	local_8g = tp->twp;
	local_cg = tp->awp;
	local_8g->mode = 1;
	local_cg->work.sw[2] = 0;
	local_cg->work.sw[3] = 0;
	DAT_05cd29ac = 0.0f;
	DAT_05cd29b0 = 0.0f;
	DAT_05cd29b4 = 0;
	DAT_05cd29a8 = 0.0f;
	DAT_05cd29a4 = DAT_05cd29a8;
	if ((DAT_05cd296c & 1) != 0)
	{
		BGM_Replay();
	}
	dsStop_num(0x34d);
}

// STUB: SADX 0x0058ffa0
int FUN_0058ffa0(void)
{
	return (int)0;
}

// STUB: SADX 0x00590050
void FUN_00590050(struct task *tp)
{
}

// STUB: SADX 0x00591070
void moveFishingRotY(struct task *tp)
{
}

// FUNCTION: SADX 0x005914c0
void FUN_005914c0(void)
{
	OffControl3D(0x10);
	OnControl3D(0x20);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	ResetMaterial();
}

// STUB: SADX 0x00591630
void setCameraFishingTgt(struct task *tp)
{
}

// STUB: SADX 0x00591910
void setCatchCameraPos(struct task *tp)
{
}

// STUB: SADX 0x00591a00
void setCameraReturn(struct task *tp)
{
}

// FUNCTION: SADX 0x00591d30
void FUN_00591d30(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2)
{
	struct NJS_POINT3 local_14;

	local_14.x = param_2->x - param_1->x;
	local_14.y = param_2->y - param_1->y;
	local_14.z = param_2->z - param_1->z;
	if (MSetPosition(param_1, &local_14, (struct Angle3 *)0x0, 4.0f) != 0)
	{
		param_2->x = param_1->x + local_14.x;
		param_2->y = param_1->y + local_14.y;
		param_2->z = param_1->z + local_14.z;
	}
}

// FUNCTION: SADX 0x00591dd0
float GetWaterLevel()
{
	return DAT_05cd29a0;
}

// STUB: SADX 0x00591de0
void BigDisplayStatus(struct task *tp)
{
}

// FUNCTION: SADX 0x005923c0
void SetBigDispHit()
{
	CreateElementalTask(2, 6, BigDisplayHit);
	DAT_05cd2974 = 0.0f;
	Jingle_Play(0x2d);
}

// FUNCTION: SADX 0x00592680
void FUN_00592680(struct task *param_1)
{
	FUN_00592520(param_1);
}

// STUB: SADX 0x005926a0
struct task *FUN_005926a0(struct task *param_1)
{
	return (struct task *)0;
}

// STUB: SADX 0x00592880
void dispDustTexture(struct task *tp)
{
}

// STUB: SADX 0x00592980
long BigCheckTargetEnemy(struct taskwk *twp)
{
	return (long)0;
}

// STUB: SADX 0x00592a30
void BigStageInit()
{
}

// STUB: SADX 0x00592a80
float FUN_00592a80(void)
{
	return (float)0;
}

// FUNCTION: SADX 0x00592b10
void big5Ring()
{
	AddNumRing(5);
	dsPlay_oneshot(7, 0, 0, 0);
}

// FUNCTION: SADX 0x00592b30
void big10Ring()
{
	AddNumRing(10);
	dsPlay_oneshot(7, 0, 0, 0);
}

// STUB: SADX 0x00592b50
void bigRandomRing()
{
}

// FUNCTION: SADX 0x00592bb0
void big1up()
{
	AddNumPlayer(1);
}

// FUNCTION: SADX 0x00592bc0
float FUN_00592bc0()
{
	return DAT_05cd29a4;
}

// FUNCTION: SADX 0x00593370
void AddSakanaWeight(float weight, long kind)
{
	int local_8;

	DAT_05cd2990 = (long)((float)DAT_05cd2990 + weight);
	if (DAT_05cd2990 > 0x18696)
	{
		DAT_05cd2990 = 0x18696;
	}
	local_8 = (int)DAT_05cd299c;
	if ((float)local_8 < weight)
	{
		DAT_05cd299c = (short)weight;
		DAT_05cd2994 = (int)kind;
	}
}

// FUNCTION: SADX 0x005937a0
void exitFishWeightTexture(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (local_8->counter.l != 0x3e7)
	{
		AddSakanaWeight((float)local_8->value.l, (long)local_8->counter.l);
		if (local_8->counter.l == 0)
		{
			BigChkHighScore();
		}
		dsPlay_oneshot(7, 0, 0, 0);
	}
}

// FUNCTION: SADX 0x00593800
void CreateBigDisplayFishWeight(long weight, long kind)
{
	struct task *local_8;

	local_8 = CreateElementalTask(2, 6, BigDisplayFishWeight);
	if (local_8)
	{
		local_8->twp->value.l = weight;
		*(long *)((char *)local_8->twp + 8) = kind;
	}
}
