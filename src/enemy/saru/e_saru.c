#include "decls.h"
void FUN_005c9d00(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c9060(struct taskwk *param_1, struct enemywk *param_2);

// FUNCTION: SADX 0x005c5dd0
void SaruTraceCircle(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 tmp_pos;
	tmp_pos.x = twp->scl.z;
	tmp_pos.y = twp->pos.y;
	tmp_pos.z = 0.0f;
	njPushMatrix(_nj_unit_matrix_);
	if (twp->ang.x != 0)
	{
		njRotateY(0, twp->ang.x);
	}
	njCalcPoint(0, &tmp_pos, &twp->pos);
	njPopMatrix(1);
	twp->pos.x = twp->pos.x + ewp->home.x;
	twp->pos.z = twp->pos.z + ewp->home.z;
}

// STUB: SADX 0x005c62a0
void FUN_005c62a0(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c68f0
void FUN_005c68f0(struct taskwk *param_1)
{
	if (param_1->flag & 0x2000)
	{
		*(float *)((char *)param_1 + 0x24) = Shadow(param_1, 1.0f) + 4.0f;
	}
}

// FUNCTION: SADX 0x005c6930
void FUN_005c6930(struct taskwk *param_1)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0, param_1->pos.z, 1.4f);
	CreateExpParts(param_1, saru_model, &texlist_e_saru);
	CreateExpSpring(param_1, 8);
	CreateAnimal(3, param_1->pos.x, param_1->pos.y + 15.0, param_1->pos.z);
}

// STUB: SADX 0x005c6cd0
void SaruDecideAimPos(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c6e60
long SaruCheckInterrupt(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// STUB: SADX 0x005c7050
void FUN_005c7050(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c71d0
void SaruRoundSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c72f0
void SaruPori(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c7440
void SaruTurnL(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c75c0
void SaruTurnR(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c8300
void FUN_005c8300(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c84d0
void SaruThrow(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c8e80
void SaruBombAExecutor(struct task *tp)
{
}

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
	param_2->velo.y = param_2->acc.y - 0.05999999865889549 + param_2->velo.y;
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

// STUB: SADX 0x005c9750
void SaruBombCollision(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c9950
void SaruBombCountDown(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c9d00
void FUN_005c9d00(struct taskwk *param_1, struct enemywk *param_2)
{
	SaruBombExplosionDraw(param_1, param_2);
}

// STUB: SADX 0x005c9d20
void SaruBombExplosionDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c9e30
void SaruBombADisplayer(struct task *tp)
{
}
