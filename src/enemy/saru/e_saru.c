#include "decls.h"
extern double DAT_0095cbc0;
void FUN_005c9060(struct taskwk *param_1, struct enemywk *param_2);

// FUNCTION: SADX 0x005c8fe0
void SaruBombNormal(struct taskwk *twp, struct enemywk *ewp)
{
	if (twp->wtimer > 0x14)
	{
		SaruBombCollision(twp, ewp);
	}
	FUN_005c9060(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	SaruBombDraw(twp, ewp);
	if (twp->wtimer > 0x78)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 1;
		twp->wtimer = 0;
		twp->smode = 0xf;
	}
}

// FUNCTION: SADX 0x005c9060
void FUN_005c9060(struct taskwk *param_1, struct enemywk *param_2)
{
	param_2->velo.y = param_2->acc.y - DAT_0095cbc0 + param_2->velo.y;
	param_1->pos.x = param_1->pos.x + param_2->velo.x;
	param_1->pos.y = param_1->pos.y + param_2->velo.y;
	param_1->pos.z = param_1->pos.z + param_2->velo.z;
	param_2->acc.x = 0.0f;
	param_2->acc.y = 0.0f;
	param_2->acc.z = 0.0f;
}

// FUNCTION: SADX 0x005c9460
void CreateSaruBombExplosion(struct NJS_POINT3 *pos)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateElementalTask(2, 5, SaruBombExplosion);
	local_cg->disp = SaruBombDisplayer;
	if (local_cg != NULL)
	{
		local_8g = local_cg->twp;
		local_8g->pos = *pos;
	}
}

// FUNCTION: SADX 0x005c9d00
void FUN_005c9d00(struct taskwk *param_1, struct enemywk *param_2)
{
	SaruBombExplosionDraw(param_1, param_2);
}

// STUB: SADX 0x005c9e30
void SaruBombADisplayer(struct task *tp)
{
}
