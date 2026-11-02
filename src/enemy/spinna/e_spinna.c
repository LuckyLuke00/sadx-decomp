#include "decls.h"
extern struct CCL_INFO spinna_info[3];
extern void SpinnaDisplayer(struct task *tp);
extern "C" int rand(void);
unsigned long GetGlobalTime();
void SpinnaEditDraw(struct taskwk *twp, float xpos, float ypos, float zpos);
float EnemyDist2FromHome(struct taskwk *twp, struct enemywk *ewp);
void FUN_00594710(void *, void *);
extern void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_TEXLIST texlist_supi_supi;
extern struct obj object_supi_supi_supi;
extern void ___njSetTexture(struct NJS_TEXLIST *texlist);
extern void ___dsSetPalette(long no);
extern void ___dsDrawObject(struct obj *obj);

// STUB: SADX 0x00593ba0
void EnemySpinnaA(struct task *tp)
{
}

// FUNCTION: SADX 0x00593d80
void SpinnaInit(struct task *tp, struct taskwk *twp)
{
	unsigned long local_8g;
	struct enemywk *local_cj;
	int local_10m;
	float local_14;
	local_8g = GetGlobalTime();
	CCL_Init(tp, spinna_info, 3, 2);
	local_cj = EnemyInitialize(tp, twp);
	twp->smode = 0;
	twp->wtimer = 0;
	local_cj->old_smode = (signed char)(*(unsigned int *)((char *)twp + 0x1c) & 0xff);
	*(unsigned int *)((char *)twp + 0x1c) = (*(unsigned int *)((char *)twp + 0x1c) & ~0xff) >> 8;
	local_cj->view_range = 6400.0f;
	local_cj->view_angle = 0x71c7;
	local_cj->hear_range = 400.0f;
	*(float *)((char *)local_cj + 4) = 0.4f;
	local_cj->angy_spd = 0x180;
	local_cj->norm.x = 1.0f;
	local_cj->norm.y = 0.0f;
	local_10m = rand();
	local_14 = (float)local_10m / 32768.0f;
	local_cj->angz_spd = (long)(local_14 * 360.0f * 65536.0f / 360.0f);
	local_cj->angx_spd = (int)local_8g * *(int *)((char *)twp + 0x1c) + *(int *)((char *)twp + 0x14);
	local_cj->force.y = twp->pos.y;
	EnemyPreserveHomePosition(twp, local_cj);
	twp->mode = 1;
	Knuckles_KakeraGame_Set_CheckEme(local_cj->old_smode, &twp->pos);
	tp->disp = SpinnaDisplayer;
}

// FUNCTION: SADX 0x00593ee0
void SpinnaDead(struct taskwk *twp)
{
	int local_8;
	EraseDolbyCtrl(twp);
	for (local_8 = 0; local_8 < 1; local_8++)
	{
		CreateFlash2(twp->pos.x, twp->pos.y + 5.0f, twp->pos.z, 1.4f);
	}
	CreateExpSpring(twp, 8);
	twp->mode = 5;
}

// STUB: SADX 0x00593f60
void SpinnaDisplayer(struct task *tp)
{
}

// STUB: SADX 0x005941f0
void SpinnaEditModeA(struct task *tp, struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005943b0
void SpinnaEditDraw(struct taskwk *twp, float xpos, float ypos, float zpos)
{
	___njSetTexture(&texlist_supi_supi);
	___dsSetPalette(6);
	njPushMatrix(0);
	FUN_0067d830(0, xpos, ypos, zpos);
	if (twp->ang.y != 0)
	{
		njRotateY(0, (Uint16)twp->ang.y);
	}
	___dsDrawObject(&object_supi_supi_supi);
	njPopMatrix(1);
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x00594430
void FUN_00594430(int param_1, int param_2, int param_3)
{
	FUN_005b5aa0(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00594450
void FUN_00594450(struct task *param_1, int param_2, int param_3)
{
	if (GM_CheckMode() == 2)
	{
		CreateAnimal(5, *(float *)(param_2 + 0x20), *(float *)(param_2 + 0x24), *(float *)(param_2 + 0x28));
	}
	FUN_005b5aa0(param_1, param_2, param_3);
	DeadOut(param_1);
}

// FUNCTION: SADX 0x005944b0
void FUN_005944b0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005946c0(param_1, param_2);
	FUN_005945c0(param_1, param_2);
	FUN_00594570(param_1, param_2);
	FUN_00594710(param_1, param_2);
	SpinnaNormalA(param_1, param_2);
	SpinnaDraw(param_1, param_2);
	if (EnemyDist2FromPlayer(param_1, 0) < 57600.0f)
	{
		dsPlay_Dolby_timer_vq(0x35b, (int)param_1, 1, 0, 1, 200.0f, param_1);
	}
}

// FUNCTION: SADX 0x00594570
void FUN_00594570(struct taskwk *param_1, struct enemywk *param_2)
{
	long local_8;
	if ((param_1->flag & 0x100) != 0)
	{
		EnemyTurnToHome(param_1, param_2);
	}
	else
	{
		if ((param_1->flag & 0x200) != 0)
		{
			local_8 = EnemyTurnToPlayer(param_1, param_2, 0);
		}
	}
}

// FUNCTION: SADX 0x005945c0
void FUN_005945c0(struct taskwk *param_1, struct enemywk *param_2)
{
	float local_8 = EnemyDist2FromHome(param_1, param_2);
	if (local_8 > (param_1->scl.x + 60.0f) * (param_1->scl.x + 60.0f))
	{
		param_1->flag |= 0x100;
	}
	else
	{
		param_1->flag &= ~0x100;
	}
}

// STUB: SADX 0x00594630
void SpinnaNormalA(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005946c0
void FUN_005946c0(struct taskwk *param_1, struct enemywk *param_2)
{
	if (EnemySearchPlayer(param_1, param_2) != 0)
	{
		param_1->flag |= 0x200;
	}
	else
	{
		param_1->flag &= ~0x200;
	}
}

// FUNCTION: SADX 0x00594710
void FUN_00594710(void *param_1, void *param_2)
{
	float local_8;
	local_8 = *(float *)((char *)DAT_05baf368[0] + 0x24) + 6.0f;
	*(float *)((char *)param_2 + 0x4) = *(float *)((char *)param_2 + 0x4) + *(float *)((char *)param_2 + 0x10);
	*(float *)((char *)param_2 + 0xc) = *(float *)((char *)param_2 + 0xc) + *(float *)((char *)param_2 + 0x18);
	if (*(float *)((char *)param_2 + 0x4) > 0.4f)
	{
		*(float *)((char *)param_2 + 0x4) = 0.4f;
	}
	else if (*(float *)((char *)param_2 + 0x4) < 0.1f)
	{
		*(float *)((char *)param_2 + 0x4) = 0.1f;
	}
	if (local_8 > *(float *)((char *)param_2 + 0x78))
	{
		*(float *)((char *)param_2 + 0x78) = *(float *)((char *)param_2 + 0x78) + 0.2f;
	}
	else
	{
		*(float *)((char *)param_2 + 0x78) = *(float *)((char *)param_2 + 0x78) - 0.2f;
	}
	if (*(float *)((char *)param_2 + 0x78) > *(float *)((char *)param_2 + 0x54) + 20.0f)
	{
		*(float *)((char *)param_2 + 0x78) = *(float *)((char *)param_2 + 0x54) + 20.0f;
	}
	else if (*(float *)((char *)param_2 + 0x78) < *(float *)((char *)param_2 + 0x54) - 20.0f)
	{
		*(float *)((char *)param_2 + 0x78) = *(float *)((char *)param_2 + 0x54) - 20.0f;
	}
	*(float *)((char *)param_1 + 0x20) = njCos(*(int *)((char *)param_1 + 0x18)) * *(float *)((char *)param_2 + 0x4) + njSin(*(int *)((char *)param_1 + 0x18)) * *(float *)((char *)param_2 + 0xc) + *(float *)((char *)param_1 + 0x20);
	*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_2 + 0x78) + njSin(*(int *)((char *)param_2 + 0x1c4)) * 1.6f;
	*(float *)((char *)param_1 + 0x28) = -(njSin(*(int *)((char *)param_1 + 0x18)) * *(float *)((char *)param_2 + 0x4)) + njCos(*(int *)((char *)param_1 + 0x18)) * *(float *)((char *)param_2 + 0xc) + *(float *)((char *)param_1 + 0x28);
	*(int *)((char *)param_2 + 0x1c4) = *(int *)((char *)param_2 + 0x1c4) + 0x280;
}

// STUB: SADX 0x005948e0
void SpinnaDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x00594c00
void FUN_00594c00(struct taskwk *param_1, struct enemywk *param_2)
{
	SpinnaDamage(param_1, param_2);
	SpinnaDraw(param_1, param_2);
}

// STUB: SADX 0x00594c30
void SpinnaDamage(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x00594d30
void EnemySpinnaB(struct task *tp)
{
}

// STUB: SADX 0x00594f10
void SpinnaEditModeB(struct task *tp, struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005951a0
void FUN_005951a0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005946c0(param_1, param_2);
	FUN_005945c0(param_1, param_2);
	FUN_00594570(param_1, param_2);
	SpinnaNormalB(param_1, param_2);
	SpinnaNormalA(param_1, param_2);
	SpinnaDraw(param_1, param_2);
	if (EnemyDist2FromPlayer(param_1, 0) < 57600.0f)
	{
		dsPlay_Dolby_timer_vq(0x35b, (int)param_1, 1, 0, 1, 200.0f, param_1);
	}
}

// FUNCTION: SADX 0x00595260
void SpinnaNormalB(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;
	local_8 = njSin((long)GetGlobalTime() * *(long *)((char *)twp + 0x1c) + twp->ang.x);
	twp->pos.x = twp->scl.x * local_8 + ewp->home.x;
	twp->pos.y = twp->scl.y * local_8 + ewp->home.y;
	twp->pos.z = twp->scl.z * local_8 + ewp->home.z;
	ewp->angx_spd += *(long *)((char *)twp + 0x1c);
}

// STUB: SADX 0x005952e0
void EnemySpinnaC(struct task *tp)
{
}

// STUB: SADX 0x005954e0
void SpinnaEditModeC(struct task *tp, struct taskwk *twp)
{
}
