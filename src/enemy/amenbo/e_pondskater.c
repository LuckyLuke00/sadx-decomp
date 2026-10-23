#include "decls.h"
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

// FUNCTION: SADX 0x008d60b0
void FUN_008d60b0(struct taskwk *param_1)
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

// STUB: SADX 0x008d63e0
void FUN_008d63e0(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x008d6b70
void PondDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

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
