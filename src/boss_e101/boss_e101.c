#include "decls.h"
static void execMode(struct task *pTask);
static void hover(struct task *pTask);
static void fall(struct task *pTask);
static void destTgt(struct task *pTask);
static void execTgt(struct task *pTask);
extern float DAT_05edc424;
void FUN_0082ae70(float param_1);
extern "C" double atan2(double v, double u);
extern "C" double fabs(double param_1);
extern "C" int rand(void);
static void normal(struct task *pTask);
static void FUN_00705690(int *param_1, int *param_2);
extern char DAT_05ccdad1;
static void waitPlayer(struct task *pTask);
static void FUN_00705520(struct task *param_1);
static void FUN_007054e0(int param_1, struct task *param_2);
static void turnBody(struct task *pTask, struct NJS_POINT3 *posTarget, long angMax);
static int FUN_00705400(struct task *param_1, float param_2);
static void chkDamage(struct task *pTask);
extern struct obj object_e101old_kihon0_e101old_e_head[];
extern struct obj object_e101old_kihon0_e101old_e_head[1];
extern struct bosswk *DAT_060c451c;
long CalcMMMatrix(float (*inpmat)[16], struct NJS_ACTION *actptr, float motfrm, unsigned long srcnmb, float (*ansmat)[16]);
void FUN_004a88c0(struct NJS_ACTION *param_1, float param_2);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00705270
static void chkDamage(struct task *pTask)
{
	struct motionwk *var1 = pTask->mwp;
	struct taskwk *var2 = pTask->twp;
	int *var3 = (int *)pTask->awp;
	struct task *var4;
	struct NJS_POINT3 local_14;
	struct NJS_POINT3 local_24;
	float local_18;
	if (var3[17] & 8)
	{
		E102KillCursorOnly(pTask);
		return;
	}
	if ((var2->flag & 4) && var2->mode != 5)
	{
		var4 = (struct task *)FUN_005e5720(*(int *)((char *)var1 + 0x40));
		if (var4)
		{
			local_14.x = var4->twp->pos.x;
			local_14.y = var4->twp->pos.y;
			local_14.z = var4->twp->pos.z;
			local_24.x = *(float *)((char *)var4->mwp + 4);
			local_24.y = *(float *)((char *)var4->mwp + 8);
			local_24.z = *(float *)((char *)var4->mwp + 12);
		}
		else
		{
			local_14.x = var2->pos.x;
			local_14.y = var2->pos.y;
			local_14.z = var2->pos.z;
			local_24.x = local_24.y = local_24.z = 0.0f;
		}
		var3[17] |= 8;
		dsPlay_oneshot(0x9b, 0, 0, 0);
		E102Hit(&local_14, -15.0f);
		FUN_005e5770(pTask);
		local_18 = ((float *)var3)[14] - 1.0;
		((float *)var3)[14] = local_18;
		if (local_18 <= 0.0f)
		{
			if (pTask->twp->mode != 7)
			{
				((int *)pTask->awp)[18] = 7;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
		}
		else
		{
			if (pTask->twp->mode != 5)
			{
				((int *)pTask->awp)[18] = 5;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			((float *)var3)[29] = local_24.x * 0.3f;
			((float *)var3)[30] = local_24.y * 0.3f;
			((float *)var3)[31] = local_24.z * 0.3f;
		}
	}
}

// FUNCTION: SADX 0x00705400
static int FUN_00705400(struct task *param_1, float param_2)
{
	struct taskwk *var1 = param_1->twp;
	struct taskwk *var3 = DAT_05baf368[0];
	float local_8 = var1->pos.x - var3->pos.x;
	float local_c = var1->pos.z - var3->pos.z;
	float var2 = local_8 * local_8 + local_c * local_c;
	if (var2 < param_2)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00705460
static void turnBody(struct task *pTask, struct NJS_POINT3 *posTarget, long angMax)
{
	struct taskwk *var1 = pTask->twp;
	float *var2 = (float *)pTask->awp;
	float local_8 = var1->pos.x - posTarget->x;
	float local_c = var1->pos.z - posTarget->z;
	long var3 = SubAngle(var1->ang.y, (long)(atan2((double)local_c, (double)local_8) * 65536.0 / -6.283184));
	if (var3 < -angMax)
	{
		var3 = -angMax;
	}
	else if (var3 > angMax)
	{
		var3 = angMax;
	}
	var1->ang.y += var3;
	var2[25] = local_8 * local_8 + local_c * local_c;
}

// FUNCTION: SADX 0x007054e0
static void FUN_007054e0(int param_1, struct task *param_2)
{
	char *var1 = (char *)param_2->awp + param_1 * 12;
	EnemyBossE101Missile((struct NJS_POINT3 *)(var1 + 0xa4), (struct NJS_POINT3 *)(var1 + 0xbc), param_2->twp->cwp);
	dsPlay_oneshot(0x99, 0, 0, 0);
}

// FUNCTION: SADX 0x00705520
static void FUN_00705520(struct task *param_1)
{
	float *var1 = (float *)((char *)param_1->awp + 0x90);
	int var2;
	for (var2 = 0; var2 < 2; var2++)
	{
		bsmoke_data.pos.x = var1[-1];
		bsmoke_data.pos.y = var1[0];
		bsmoke_data.pos.z = var1[1];
		FUN_005536c0(&bsmoke_data);
		var1 += 3;
	}
}

// FUNCTION: SADX 0x00705560
static void waitPlayer(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	int *var2 = (int *)pTask->awp;
	struct bosswk *var3 = (struct bosswk *)pTask->awp;
	SleepTimer();
	PadReadOff();
	switch (var1->smode)
	{
	case 0:
		((float *)var2)[14] = 3.0f;
		var1->pos.x = posStart.x;
		var1->pos.y = posStart.y;
		var1->pos.z = posStart.z;
		var3->req_action = 0;
		var2[17] = (var2[17] & ~0x30) | 0xc;
		var1->cwp->info->damage |= 0xc;
		DAT_060c4538 = 0;
		var1->smode = 1;
		break;
	case 1:
		SetParamCameraChaosStageInit(var1, 0.0f, 30.0f, 0xf0);
		CameraSetEventCamera(0x34, 0);
		SetDisplayBossName("E101|", -1, 0xf0, 0x78);
		var1->smode = 2;
		BGM_Play(0xb);
		break;
	case 2:
		if (DAT_05ccdad1)
		{
			WakeTimer();
			PadReadOn();
			SetChaosLifeGauge(0, 0, 3);
			var2[17] &= ~8;
			var1->cwp->info->damage = (var1->cwp->info->damage & ~4) | 8;
			StartCameraE101_Tgt(&var1->pos, &CamEye);
			if (pTask->twp->mode != 6)
			{
				((int *)pTask->awp)[18] = 6;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			var1->smode = -1;
		}
		break;
	}
}

// FUNCTION: SADX 0x00705690
static void FUN_00705690(int *param_1, int *param_2)
{
	long local_c = SubAngle(*param_1, 0);
	long var1;
	if (local_c < -182)
	{
		local_c = -182;
	}
	else if (local_c > 182)
	{
		local_c = 182;
	}
	var1 = (long)(local_c - *param_2 * 0.2f) + *param_2;
	*param_2 = var1;
	*param_1 += var1;
	if ((float)fabs((float)*param_2) < 91.0f && (float)fabs((float)*param_1) < 91.0f)
	{
		*param_2 = 0;
		*param_1 = 0;
	}
}

// FUNCTION: SADX 0x00705730
static void move(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	float *var2 = (float *)pTask->awp;
	struct NJS_POINT3 vec;
	float local_18;
	float local_18g;
	float local_18h;
	struct NJS_POINT3 *var3 = (struct NJS_POINT3 *)(var2 + 26);
	*var3 = var1->pos;
	if (ChkE104ColliLandXZ(&var1->pos, 5.0f, &var2[23], &vec) == 1)
	{
		var1->pos.x += vec.x;
		var1->pos.y += vec.y;
		var1->pos.z += vec.z;
		var2[29] = -var2[29];
		var2[31] = -var2[31];
	}
	if (var2[23] < 0.0f)
	{
		local_18 = 0.0f;
	}
	else
	{
		if (var2[23] > 40.0f)
		{
			local_18 = 40.0f;
		}
		else
		{
			local_18 = var2[23];
		}
	}
	local_18 = local_18 + 14.0;
	var2[23] = local_18;
	var2[24] = var1->pos.y - local_18;
	if (((int *)var2)[17] & 4)
	{
		var2[30] = var2[30] - 0.05f;
	}
	local_18g = var1->pos.y + var2[30];
	var1->pos.y = local_18g;
	if (var2[23] >= local_18g)
	{
		var1->pos.y = var2[23];
		var2[30] = 0.0f;
		if (!(((int *)var2)[17] & 0x40))
		{
			((int *)var2)[17] |= 0x40;
			dsPlay_oneshot_v(0x33e, 0, 0, 0, var1->pos.x, var1->pos.y, var1->pos.z);
		}
	}
	else
	{
		((int *)var2)[17] &= ~0x40;
	}
	var1->pos.x += var2[29];
	var1->pos.z += var2[31];
	local_18g = var2[29] * 0.95f;
	var2[29] = local_18g;
	local_18h = var2[31] * 0.95f;
	var2[31] = local_18h;
	if (local_18g < 0.05f && -0.05f < local_18g)
	{
		var2[29] = 0.0f;
	}
	if (local_18h < 0.05f && -0.05f < local_18h)
	{
		var2[31] = 0.0f;
	}
	{
		long var4;
		if (((int *)var2)[17] & 2)
		{
			float var5;
			float var6;
			if (!DAT_05baf368[0])
			{
				return;
			}
			var6 = var1->pos.z - DAT_05baf368[0]->pos.z;
			var5 = var1->pos.x - DAT_05baf368[0]->pos.x;
			var4 = -var1->ang.y - (long)(atan2((double)var6, (double)var5) * 65536.0 / 6.283184);
		}
		else
		{
			var4 = 0;
		}
		var4 = SubAngle(((int *)var2)[21], var4);
		if (var4 < -455)
		{
			var4 = -455;
		}
		else if (var4 > 455)
		{
			var4 = 455;
		}
		((int *)var2)[21] += var4;
		FUN_00705690((int *)&var1->ang.x, &((int *)var2)[22]);
	}
}

// FUNCTION: SADX 0x00705990
static void normal(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	int *var2 = (int *)pTask->awp;
	struct bosswk *var3 = (struct bosswk *)pTask->awp;
	switch (var1->smode)
	{
	case 0:
		StartCameraE101_Tgt(&var1->pos, &CamEye);
		var3->req_action = 0;
		var2[17] |= 2;
		var1->smode = 1;
		break;
	case 1:
		if (DAT_05b932e8[1].on & 4)
		{
			if (var1->mode != 0)
			{
				((int *)pTask->awp)[18] = 0;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			return;
		}
		if (DAT_060c4538 == 0 && var2[16] > 10)
		{
			var2[16] = 10;
		}
		else if (--var2[16] < 0)
		{
			if (DAT_060c4538 < 1)
			{
				if (pTask->twp->mode != 6)
				{
					((int *)pTask->awp)[18] = 6;
					((int *)pTask->awp)[19] = pTask->twp->mode;
				}
			}
			else if (pTask->twp->mode != 2)
			{
				((int *)pTask->awp)[18] = 2;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			var2[16] = 0x78;
		}
		if (FUN_00705400(pTask, 3600.0f) && pTask->twp->mode != 2)
		{
			((int *)pTask->awp)[18] = 2;
			((int *)pTask->awp)[19] = pTask->twp->mode;
		}
		if (var1->pos.y - ((float *)var2)[23] >= 10.0 && pTask->twp->mode != 4)
		{
			((int *)pTask->awp)[18] = 4;
			((int *)pTask->awp)[19] = pTask->twp->mode;
		}
		break;
	}
}

// FUNCTION: SADX 0x00705ad0
static void jump(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	int *var3 = (int *)pTask->awp;
	int var4;
	int *var5;
	switch (var1->smode)
	{
	case 0:
		var2->req_action = 1;
		var3[17] &= ~2;
		var1->smode = 1;
		break;
	case 1:
		DAT_05edd13e &= 0xfd;
		if (var2->action == 1)
		{
			var3[22] = 0;
			var1->ang.x = 0;
			var1->smode = 2;
		}
		break;
	case 2:
		var5 = (int *)pTask->awp;
		var4 = (rand() & 1) + var5[20] + 1;
		if (var4 >= 3)
		{
			var4 -= 3;
		}
		var5[20] = var4;
		((float *)var3)[30] = ((float *)var3)[30] + 2.0;
		dsPlay_oneshot_v(0x33c, 0, 0, 0, var1->pos.x, var1->pos.y, var1->pos.z);
		var1->smode = 3;
		break;
	case 3:
		if (((float *)var3)[30] <= 0.0f)
		{
			if (var1->mode != 3)
			{
				((int *)pTask->awp)[18] = 3;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			var1->smode = -1;
		}
		break;
	}
}

// FUNCTION: SADX 0x00705bc0
static void hover(struct task *pTask)
{
	struct bosswk *var1 = (struct bosswk *)pTask->awp;
	struct taskwk *var3 = pTask->twp;
	struct NJS_POINT3 *var2 = (struct NJS_POINT3 *)((char *)var1 + 0x74);
	double var4;
	SetE101HoverSmoke(var3, (*(float *)((char *)var1 + 0x5c)) - 14.0);
	switch (var3->smode)
	{
	case 0:
		var1->req_action = 4;
		(*(int *)((char *)var1 + 0x44)) = ((*(int *)((char *)var1 + 0x44)) & ~2) | 9;
		var3->cwp->info->damage |= 0xc;
		var3->smode = 1;
		break;
	case 1:
		dsPlay_timer_v(0x98, (int)pTask, 1, 0, 4, var3->pos.x, var3->pos.y, var3->pos.z);
		turnBody(pTask, &PosSpot[(*(int *)((char *)var1 + 0x50))], 0x38e);
		(*(int *)((char *)var1 + 0x58)) = 0;
		if (var3->ang.x < 0x1c71)
		{
			var3->ang.x += 0x222;
		}
		var4 = 0.0;
		if (var2->y >= 0.0f)
		{
			var4 = var2->y * (double)0.95f;
		}
		var2->y = var4;
		FUN_0082ae70(0.15f);
		if ((*(float *)((char *)var1 + 0x64)) <= 400.0)
		{
			if (pTask->twp->mode != 4)
			{
				*(int *)((char *)pTask->awp + 0x48) = 4;
				*(int *)((char *)pTask->awp + 0x4c) = pTask->twp->mode;
			}
			var3->smode = -1;
		}
		break;
	}
	if (var3->smode == -1)
	{
		(*(int *)((char *)var1 + 0x44)) &= ~9;
		var2->x *= 0.6f;
		var2->z *= 0.6f;
		var3->cwp->info->damage = (var3->cwp->info->damage & ~4) | 8;
	}
}

// FUNCTION: SADX 0x00705d30
static void fall(struct task *pTask)
{
	float *var1 = (float *)pTask->awp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	struct taskwk *var3 = pTask->twp;
	SetE101HoverSmoke(var3, var1[23] - 14.0);
	switch (var3->smode)
	{
	case 0:
		var2->req_action = 2;
		var3->smode = 1;
		break;
	case 1:
		turnBody(pTask, &DAT_05baf368[0]->pos, 0x49f);
		if (var1[23] == var3->pos.y)
		{
			var2->req_action = 3;
			var3->smode = 2;
		}
		break;
	case 2:
		DAT_05edd13e &= 0xfd;
		if (var2->action == 3)
		{
			DAT_05edd13e &= 0xfe;
			var3->smode = 3;
		}
		break;
	case 3:
		if (DAT_05edd13e & 1)
		{
			if (pTask->twp->mode != 6)
			{
				((int *)pTask->awp)[18] = 6;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			var3->smode = -1;
		}
		break;
	}
}

// FUNCTION: SADX 0x00705e20
static void damage(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	int *var3 = (int *)pTask->awp;
	switch (var1->smode)
	{
	case 0:
		var2->req_action = 7;
		var3[17] = (var3[17] & ~2) | 8;
		var1->cwp->info->damage |= 0xc;
		if (((float *)var3)[14] <= 1.0f)
		{
			var3[17] |= 0x10;
		}
		if (((float *)var3)[14] <= 1.0f)
		{
			var3[17] |= 0x20;
		}
		var1->smode = 1;
		break;
	case 1:
		DAT_05edd13e &= 0xfd;
		if (var2->action == 7)
		{
			DAT_05edd13e &= 0xfe;
			var1->smode = 2;
		}
		break;
	case 2:
		if (DAT_05edd13e & 1)
		{
			if (FUN_00705400(pTask, 14400.0f))
			{
				if (var1->mode != 1)
				{
					((int *)pTask->awp)[18] = 1;
					((int *)pTask->awp)[19] = pTask->twp->mode;
				}
			}
			else if (var1->mode != 6)
			{
				((int *)pTask->awp)[18] = 6;
				((int *)pTask->awp)[19] = pTask->twp->mode;
			}
			var1->smode = -1;
		}
		break;
	}
	if (var1->smode == -1)
	{
		var3[17] &= ~8;
		var1->cwp->info->damage = (var1->cwp->info->damage & ~4) | 8;
	}
}

// FUNCTION: SADX 0x00705f10
static void attack(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	struct NJS_POINT3 *var3 = (struct NJS_POINT3 *)((char *)var2 + 0x74);
	switch (var1->smode)
	{
	case 0:
		if (DAT_060c4538 >= 1)
		{
			if (var1->mode != 1)
			{
				*(int *)((char *)pTask->awp + 0x48) = 1;
				*(int *)((char *)pTask->awp + 0x4c) = pTask->twp->mode;
			}
			return;
		}
		var3->x = var3->y = var3->z = 0.0f;
		var2->req_action = 5;
		var1->smode = 1;
		break;
	case 1:
		DAT_05edd13e &= 0xfd;
		if (var2->action == 5)
		{
			var1->smode = 2;
		}
		break;
	case 2:
		turnBody(pTask, &DAT_05baf368[0]->pos, 0x2d8);
		DAT_05edd13e &= 0xfd;
		if (!(var2->nframe >= 35.0f))
		{
			break;
		}
		FUN_007054e0(1, pTask);
		DAT_05edd13e &= 0xfe;
		var1->smode = 3;
		break;
	case 3:
		if (DAT_05edd13e & 1)
		{
			if (FUN_00705400(pTask, 14400.0f))
			{
				if (var1->mode != 2)
				{
					*(int *)((char *)pTask->awp + 0x48) = 2;
					*(int *)((char *)pTask->awp + 0x4c) = pTask->twp->mode;
				}
			}
			else if (rand() < 0x3fff)
			{
				if (pTask->twp->mode != 2)
				{
					*(int *)((char *)pTask->awp + 0x48) = 2;
					*(int *)((char *)pTask->awp + 0x4c) = pTask->twp->mode;
				}
			}
			else
			{
				if (pTask->twp->mode != 1)
				{
					*(int *)((char *)pTask->awp + 0x48) = 1;
					*(int *)((char *)pTask->awp + 0x4c) = pTask->twp->mode;
				}
				*(int *)((char *)var2 + 0x40) = 0x78;
			}
			var1->smode = -1;
		}
		break;
	}
	if (var1->smode == -1)
	{
		*(int *)((char *)var2 + 0x40) = 0x78;
	}
}

// FUNCTION: SADX 0x007060a0
static void death(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	int *var3 = (int *)pTask->awp;
	switch (var1->smode)
	{
	case 0:
		var2->req_action = 0;
		var3[17] = (var3[17] & ~2) | 0x30;
		DAT_060c4538 = -1;
		SleepTimer();
		PadReadOff();
		var1->smode = 1;
		break;
	case 1:
		DAT_05edd13e &= 0xfd;
		if (var2->action == 0)
		{
			DAT_05edd13e &= 0xfe;
			var3[15] = 0;
			var1->smode = 2;
		}
		break;
	case 2:
		if (!(var3[17] & 0x40))
		{
			var3[15] = 0;
		}
		if (var3[15] >= 0x78)
		{
			var2->req_action = 8;
			var1->smode = 3;
		}
		break;
	case 3:
		if (var2->action == 8)
		{
			DAT_05edd13e &= 0xfe;
			var1->smode = 4;
		}
		break;
	case 4:
		var3[15] = 0;
		var1->smode = 5;
	case 5:
		if (var3[15] >= 0xc8)
		{
			var1->smode = 6;
		}
		break;
	case 6:
		SetFinishAction();
		var1->smode = -1;
		break;
	}
	if (var1->smode == -1)
	{
		var3[17] &= ~0x30;
		PadReadOn();
	}
}

// FUNCTION: SADX 0x007061a0
static void execMode(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	switch (var1->mode)
	{
	case 0:
		if (var1->smode != 0)
		{
			move(pTask);
		}
		waitPlayer(pTask);
		break;
	case 1:
		move(pTask);
		normal(pTask);
		break;
	case 2:
		move(pTask);
		jump(pTask);
		break;
	case 3:
		move(pTask);
		hover(pTask);
		break;
	case 4:
		move(pTask);
		fall(pTask);
		break;
	case 5:
		move(pTask);
		damage(pTask);
		break;
	case 6:
		move(pTask);
		attack(pTask);
		break;
	case 7:
		move(pTask);
		death(pTask);
		break;
	}
}

// FUNCTION: SADX 0x00706270
void callbackTgt(struct obj *obj)
{
	if (obj == &object_e101old_kihon0_e101old_e_head[0])
	{
		if (*(int *)((char *)DAT_060c451c + 0x54) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)DAT_060c451c + 0x54));
		}
	}
}

// FUNCTION: SADX 0x00706420
static void destTgt(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	if (var1->smode != -1)
	{
		var1->smode = -1;
		execMode(pTask);
	}
	var2->mtnmode = 0xe;
	BSetMotion(var1, var2);
}

// FUNCTION: SADX 0x00706460
static void dispTgt(struct task *pTask)
{
	float local_88[2][16];
	float local_108[2][16];
	float local_148[16];
	struct NJS_POINT3 local_154;
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	struct NJS_ACTION *var3;
	float var4;
	struct obj *var5;
	var3 = (var2->mtnmode != 2) ? var2->plactptr[var2->action].actptr : var2->actwkptr;
	const float local_158 = var2->nframe;
	DAT_060c451c = var2;
	CalcMMMatrix(&_nj_unit_matrix_, var3, local_158, 0x2d, &local_108[0]);
	GetMMMatrix(0x24, local_108[1]);
	GetMMMatrix(0x1e, local_148);
	GetMMMatrix(0x1f, local_88[1]);
	GetMMMatrix(0x28, local_88[0]);
	Shadow(var1, 2.0f);
	___njSetTexture(&texlist_e101);
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.z)
	{
		njRotateX(0, (Uint16)var1->ang.z);
	}
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	if (var1->ang.x)
	{
		njRotateZ(0, (Uint16)var1->ang.x);
	}
	if (DAT_05b9d838 == 0)
	{
		___dsSetPalette(6);
		njSetMotionCallback(callbackTgt);
		FUN_004a88c0(var3, var2->nframe);
		njSetMotionCallback(0);
		njPushMatrix(0);
		njMultiMatrix(0, &local_148);
		njRotateZ(0, 0x8000);
		var4 = *(float *)((char *)var2 + 0xd8) + 5.0;
		FUN_0067d830(0, 5.0f, var4, 0.0f);
		___dsDrawObject(object_e101_fun_e101_fun_e101_fun);
		___dsSetPalette(0);
		if (*(int *)((char *)var2 + 0x44) & 1)
		{
			___njSetTexture(&texlist_e102_effect);
			var5 = *(struct obj **)((char *)DAT_06276b18 + 0x34);
			*(int *)((char *)var5->model->mats + 0xc) = ((*(int *)((char *)var2 + 0x3c) >> 1) & 3) + 8;
			var5 = *(struct obj **)((char *)DAT_06276b18 + 0x34);
			late_DrawObject(var5, 4);
		}
		njPopMatrix(1);
	}
	njPushMatrix(&_nj_unit_matrix_);
	local_154.x = 0.0f;
	local_154.y = 0.0f;
	local_154.z = 0.0f;
	njTranslateV(0, &var1->pos);
	if (var1->ang.z)
	{
		njRotateX(0, (Uint16)var1->ang.z);
	}
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	if (var1->ang.x)
	{
		njRotateZ(0, (Uint16)var1->ang.x);
	}
	njPushMatrix(0);
	njMultiMatrix(0, &local_108[0]);
	local_154.x = 3.0f;
	njCalcPoint(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0xa4));
	local_154.x = -1.0f;
	njCalcVector(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0xbc));
	njPopMatrix(1);
	njPushMatrix(0);
	njMultiMatrix(0, &local_108[1]);
	local_154.x = 3.0f;
	njCalcPoint(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0xb0));
	local_154.x = -1.0f;
	njCalcVector(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0xc8));
	njPopMatrix(1);
	local_154.x = 0.0f;
	njPushMatrix(0);
	njMultiMatrix(0, &local_88[1]);
	njCalcPoint(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0x98));
	njPopMatrix(1);
	njPushMatrix(0);
	njMultiMatrix(0, &local_88[0]);
	njCalcPoint(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0x8c));
	njPopMatrix(1);
	njMultiMatrix(0, &local_148);
	njCalcPoint(0, &local_154, (struct NJS_POINT3 *)((char *)var2 + 0x80));
	njPopMatrix(2);
	ResetMaterial();
	LoadControl3D();
}

// FUNCTION: SADX 0x00706830
static void execTgt(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct bosswk *var2 = (struct bosswk *)pTask->awp;
	int *var3 = (int *)pTask->awp;
	int *var4;
	float var5;
	if (DAT_05baf368[0]->pos.y <= -10.0f)
	{
		KillHimByFallingDownP(0);
	}
	var3[15]++;
	var4 = (int *)pTask->awp;
	var4[53] += 0xd55;
	((float *)var4)[54] = njSin(var4[53]);
	if (var3[17] & 0x10)
	{
		FUN_00705520(pTask);
	}
	if (var3[17] & 0x20)
	{
		var4 = (int *)pTask->awp;
		if (var4[15] % 90 == 0)
		{
			var5 = rand() * 3.0517578125e-05;
			if (var5 < 0.5f)
			{
				breakLightning((struct task *)(var4 + 32));
			}
		}
	}
	execMode(pTask);
	chkDamage(pTask);
	if (var1->mode != var3[18])
	{
		if (var1->smode != -1)
		{
			var1->smode = -1;
			execMode(pTask);
		}
		var1->mode = var3[18];
		var1->smode = 0;
	}
	DAT_05edc424 = ((float *)var3)[14];
	BSetMotion(var1, var2);
	EntryColliList(var1);
	dispTgt(pTask);
}

// FUNCTION: SADX 0x00706930
void SetE101()
{
	struct task *var1 = CreateElementalTask(2, 2, execTgt);
	struct taskwk *var2;
	struct bosswk *var3;
	float *var4;
	if (var1)
	{
		var2 = var1->twp;
		CCL_Init(var1, colliInfoTgt, 2, 3);
		EnemyInitialize(var1, var2);
		var3 = BInitialize(var2, 0xdc);
		var4 = (float *)var3;
		var3->req_action = 0;
		var3->action = 0;
		var3->plactptr = tgt_action;
		var1->awp = (struct anywk *)var3;
		BSetMotion(var2, var3);
		var2->ang.z = 0;
		var2->ang.x = 0;
		var4[14] = 3.0f;
		DAT_05edc424 = 3.0f;
		((int *)var4)[19] = 0;
		var4[31] = 0.0f;
		((int *)var4)[18] = 0;
		var4[30] = 0.0f;
		((int *)var4)[20] = 1;
		var4[29] = 0.0f;
		var1->disp = dispTgt;
		var1->dest = destTgt;
	}
}
