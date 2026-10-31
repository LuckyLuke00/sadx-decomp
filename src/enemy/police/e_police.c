#include "decls.h"
extern "C" double atan2(double v, double u);
long AdjustAngle(long ang0, long ang1, long dang);
extern struct NJS_MATERIAL matlist_nisepat_nisepat_grid1[1];
extern struct NJS_MATERIAL matlist_nisepat_nisepat_grid3[1];
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x005cdd30
void PoliceDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	PoliceDraw(local_cg, local_8g);
}

// STUB: SADX 0x005cdd60
void PoliceDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005ced40
void dispPoliceShadow(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cef00
void PoliceExecutor(struct task *tp)
{
}

// STUB: SADX 0x005cf280
void PoliceEditMode(struct task *tp)
{
}

// FUNCTION: SADX 0x005cf4f0
void FUN_005cf4f0(struct task *param_1, void *param_2, void *param_3)
{
	FUN_005b5aa0(param_1, param_2, param_3);
	DeadOut(param_1);
}

// FUNCTION: SADX 0x005cf520
void PoliceWait(struct taskwk *twp, struct enemywk *ewp)
{
	PoliceCheckTerritory(twp, ewp);
	PoliceRectifyPosition(twp, ewp);
	PoliceMove(twp, ewp);
	PoliceDraw(twp, ewp);
	ewp->weight = ewp->weight + -0.004000000189989805;
	if (ewp->weight < 2.0)
	{
		ewp->weight = 2.0;
	}
	if (EnemyDist2FromPlayer(twp, 0) < 40000.0)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 1;
		twp->wtimer = 0;
		twp->flag = twp->flag | 0x400;
		ewp->aim = DAT_05baf368[0]->pos;
	}
	ewp->radius = ewp->radius - 0.019999999552965164;
	if (ewp->radius < 0.0)
	{
		ewp->radius = 0.0;
	}
	ewp->view_angle = AdjustAngle(ewp->view_angle, 0, 0x60);
	ewp->angz_spd = AdjustAngle(ewp->angz_spd, 0, 0x60);
	ewp->sub_angle[1] = AdjustAngle(ewp->sub_angle[1], 0, 0x100);
	twp->ang.x = AdjustAngle(twp->ang.x, 0, 0xb0);
	twp->ang.z = AdjustAngle(twp->ang.z, 0, 0xb0);
}

// STUB: SADX 0x005cf6d0
void PoliceCheckTerritory(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cf800
void PoliceMove(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cf9c0
void PoliceRectifyPosition(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cfd80
void PoliceScramble(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005cfef0
void PoliceTurnSlow(struct taskwk *twp, struct enemywk *ewp)
{
	long local_ci;
	long local_8g;
	long local_10;

	FUN_005e3d10(twp, ewp);
	local_10 = twp->ang.y;
	local_8g = (long)(atan2(*(float *)((char *)ewp + 0x5c) - *(float *)((char *)twp + 0x20), *(float *)((char *)ewp + 0x64) - *(float *)((char *)twp + 0x28)) * 65536.0 / 6.283184) - 0x4000;
	local_ci = SubAngle(local_8g, local_10);
	if (local_ci < -0x80)
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0xfffff800, 0x30);
	}
	else if (local_ci > 0x80)
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0x800, 0x30);
	}
	else
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0, 0x80);
	}
}

// FUNCTION: SADX 0x005cfff0
void PoliceTurnHead(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8g;

	local_8g = SubAngle(ewp->aim_angle, twp->ang.y);
	local_8g = (local_8g + 0x8000) & 0xffff;
	if (local_8g < 0x400f)
	{
		local_8g = 0x400f;
	}
	else if (local_8g > 0xbff0)
	{
		local_8g = 0xbff0;
	}
	local_8g = (local_8g + 0x8000) & 0xffff;
	ewp->sub_angle[1] = AdjustAngle(ewp->sub_angle[1], -local_8g, 0x360);
}

// FUNCTION: SADX 0x005d0080
void PoliceChase(struct taskwk *twp, struct enemywk *ewp)
{
	if (EnemyCheckFrameIn(&twp->pos))
	{
		ewp->aim = DAT_05baf368[0]->pos;
	}
	else
	{
		EnemyAimAroundPlayer(twp, ewp, 0, ewp->aim_num);
	}
	PoliceCheckTerritory(twp, ewp);
	PoliceRectifyPosition(twp, ewp);
	PoliceTurn(twp, ewp);
	PoliceForward(twp, ewp);
	PoliceMove(twp, ewp);
	PoliceTurnHead(twp, ewp);
	PoliceDraw(twp, ewp);
	if ((twp->flag & 0x400) == 0)
	{
		if (EnemyDist2FromHome(twp, ewp) < 100.0)
		{
			ewp->old_mode = twp->mode;
			twp->mode = 4;
			twp->wtimer = 0;
		}
	}
	ewp->nframe = ewp->nframe + 0.800000011920929;
}

// FUNCTION: SADX 0x005d01b0
void PoliceTurn(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8g;
	long local_10;
	long local_cj;

	FUN_005e3d10(twp, ewp);
	local_10 = *(long *)((char *)twp + 0x18);
	local_8g = (long)(atan2((double)(ewp->aim.x - twp->pos.x), (double)(ewp->aim.z - twp->pos.z)) * 65536.0 / 6.283184) - 0x4000;
	local_cj = SubAngle(local_8g, local_10);
	if (local_cj < -0x80)
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0xffffe600, 0x60);
	}
	else if (local_cj > 0x80)
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0x1a00, 0x60);
	}
	else
	{
		ewp->view_angle = AdjustAngle(ewp->view_angle, 0, 0xc0);
	}
}

// STUB: SADX 0x005d02b0
void PoliceForward(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005d05d0
void PoliceReturn(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->angy_spd = 0x50;
	PoliceCheckTerritory(twp, ewp);
	PoliceRectifyPosition(twp, ewp);
	twp->ang.y = AdjustAngle(twp->ang.y, ewp->angx_spd, 0x200);
	ewp->view_angle = AdjustAngle(ewp->view_angle, 0, 0x60);
	PoliceMoveToHome(twp, ewp);
	PoliceTurnHead(twp, ewp);
	PoliceDraw(twp, ewp);
	ewp->weight -= 0.013f;
	if (ewp->weight < 2.0f)
	{
		ewp->weight = 2.0f;
	}
	if (twp->wtimer > 0x96)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 0;
		twp->wtimer = 0;
	}
	if (EnemyDist2FromPlayer(twp, 0) < 40000.0f)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 1;
		twp->wtimer = 0;
		twp->flag |= 0x400;
		ewp->aim = DAT_05baf368[0]->pos;
	}
	ewp->radius -= 0.005f;
	if (ewp->radius < 0.0f)
	{
		ewp->radius = 0.0f;
	}
	ewp->nframe += 0.2f;
	matlist_nisepat_nisepat_grid1[0].attrflags |= 0x10000000;
	matlist_nisepat_nisepat_grid3[0].attrflags |= 0x10000000;
}

// STUB: SADX 0x005d0ac0
void FUN_005d0ac0(struct taskwk *param_1, struct enemywk *param_2)
{
}
