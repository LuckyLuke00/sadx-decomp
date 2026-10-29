#include "decls.h"
void FUN_008d69e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d63e0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_TEXLIST texlist_e_amenbo;
void FUN_008d62e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6360(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6200(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d63e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6480(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6640(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d68e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d69e0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_ACTION action_walk_ene_s_amb_root[1];
extern struct NJS_ACTION action_run_ene_s_amb_root[1];

// STUB: SADX 0x008d5bd0
void EnemyPondSkater(struct task *tp)
{
}

// STUB: SADX 0x008d6040
void FUN_008d6040(struct NJS_POINT3 *param_1)
{
}

// FUNCTION: SADX 0x008d60b0
void FUN_008d60b0(struct taskwk *param_1, int param_2)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0, param_1->pos.z, 1.4f);
	CreateExpParts(param_1, &pond_model[0], &texlist_e_amenbo);
	CreateExpSpring(param_1, 8);
	CreateAnimal(1, param_1->pos.x, param_1->pos.y + 15.0, param_1->pos.z);
}

// FUNCTION: SADX 0x008d6150
void FUN_008d6150(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	param_2->actp = &action_walk_ene_s_amb_root[0];
	param_2->view_angle = 0x38e3;
	FUN_008d6480(param_1, param_2);
	FUN_008d6200(param_1, param_2);
	FUN_008d6640(param_1, param_2);
	FUN_008d68e0(param_1, param_2);
	PondRectifyPosition(param_1, param_2);
	FUN_008d69e0(param_1, param_2);
	PondDraw(param_1, param_2);
	FUN_008d63e0(param_1, param_2);
}

// FUNCTION: SADX 0x008d6200
void FUN_008d6200(struct taskwk *param_1, struct enemywk *param_2)
{
	if ((param_1->flag & 0x1200) != 0)
	{
		EnemyTurnToHome(param_1, param_2);
		return;
	}
	switch (param_1->mode)
	{
		case 0:
			FUN_008d62e0(param_1, param_2);
			param_1->ang.y = AdjustAngle(param_1->ang.y, param_2->aim_angle, param_2->angy_spd);
			break;
		case 2:
			if ((param_1->flag & 0x800) != 0)
				FUN_008d62e0(param_1, param_2);
			else
				FUN_008d6360(param_1, param_2);
			param_1->ang.y = AdjustAngle(param_1->ang.y, param_2->aim_angle, param_2->angy_spd);
			break;
	}
}

// FUNCTION: SADX 0x008d62e0
void FUN_008d62e0(struct taskwk *param_1, struct enemywk *param_2)
{
	switch (param_1->mode)
	{
		case 0:
			if (param_1->wtimer == 0x46)
			{
				param_2->aim_angle = param_1->ang.y + 0x2aaa;
			}
			param_2->angy_spd = 0x60;
			break;
		case 2:
			if (param_1->wtimer == 0xf)
			{
				param_2->aim_angle = param_1->ang.y + 0x2aaa;
			}
			param_2->angy_spd = 0x200;
			break;
	}
}

// FUNCTION: SADX 0x008d6360
void FUN_008d6360(struct taskwk *param_1, struct enemywk *param_2)
{
	switch (param_1->mode)
	{
	case 0:
		if (param_1->wtimer == 0x46)
			param_2->aim_angle = *(long *)((char *)param_1 + 0x18) - 0x2aaa;
		param_2->angy_spd = 0x60;
		break;
	case 2:
		if (param_1->wtimer == 0xf)
			param_2->aim_angle = *(long *)((char *)param_1 + 0x18) - 0x2aaa;
		param_2->angy_spd = 0x200;
		break;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x008d63e0
void FUN_008d63e0(struct taskwk *param_1, struct enemywk *param_2)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d6480
void FUN_008d6480(struct taskwk *param_1, struct enemywk *param_2)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d6640
void FUN_008d6640(struct taskwk *param_1, struct enemywk *param_2)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d68e0
void FUN_008d68e0(struct taskwk *param_1, struct enemywk *param_2)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d6b70
void PondDraw(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008d6c70
void PondRectifyPosition(struct taskwk *twp, struct enemywk *ewp)
{
	EnemyCheckGroundCollision(twp, ewp);
	if ((ewp->flag & 0x4000) == 0)
	{
		EnemyBackToPreviousPosition(twp, ewp);
		ewp->velo.x = ewp->velo.x * -1.0;
		ewp->velo.z = ewp->velo.z * -1.0;
		twp->ang.x = 0;
		twp->ang.z = 0;
		twp->flag = twp->flag | 0x1000;
	}
	else
	{
		twp->flag = twp->flag & ~0x1000;
	}
}

// FUNCTION: SADX 0x008d6d10
void FUN_008d6d10(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	param_2->view_angle = 0x8000;
	param_2->actp = &action_run_ene_s_amb_root[0];
	FUN_008d6480(param_1, param_2);
	FUN_008d6200(param_1, param_2);
	FUN_008d6640(param_1, param_2);
	FUN_008d68e0(param_1, param_2);
	PondRectifyPosition(param_1, param_2);
	FUN_008d69e0(param_1, param_2);
	PondDraw(param_1, param_2);
	FUN_008d63e0(param_1, param_2);
}

// FUNCTION: SADX 0x008d6dc0
void FUN_008d6dc0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8g;
	float local_cg;
	local_8g = param_1->cwp;
	local_cg = EnemyDist2FromAim(param_1, param_2);
	param_2->actp = (struct NJS_ACTION *)&action_mihari_ene_s_amb_root;
	param_2->view_angle = 0x8000;
	FUN_008d6480(param_1, param_2);
	PondRectifyPosition(param_1, param_2);
	FUN_008d69e0(param_1, param_2);
	PondDraw(param_1, param_2);
	FUN_008d63e0(param_1, param_2);
}

// STUB: SADX 0x008d6e50
void FUN_008d6e50(struct taskwk *param_1, struct enemywk *param_2)
{
}
