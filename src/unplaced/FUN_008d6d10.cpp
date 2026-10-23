#include "decls.h"
void FUN_008d6200(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d63e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6480(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d6640(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d68e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d69e0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_ACTION action_run_ene_s_amb_root[1];

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
