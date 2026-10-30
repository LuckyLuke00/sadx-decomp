#include "decls.h"
#include <math.h>
#include <stdlib.h>
struct enemywk;
void SaruBombAExecutor(struct task *tp);
void SaruBombADisplayer(struct task *tp);
void SaruTraceCircle(struct taskwk *twp, struct enemywk *ewp);
void SaruRoundSmoke(struct taskwk *twp, struct enemywk *ewp);
long SaruCheckInterrupt(struct taskwk *twp, struct enemywk *ewp);
void SaruDecideAimPos(struct taskwk *twp, struct enemywk *ewp);
extern struct NJS_TEXLIST DAT_02684a9c;
void SphericalExplosionUV(long v0);
void SphericalExplosionPos(float rate);
void SphericalExplosionAlpha(float a);
void SphericalExplosionDraw();
void FUN_005c9d00(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c9060(struct taskwk *param_1, struct enemywk *param_2);

// STUB: SADX 0x005c5b40
void EnemySaru(struct task *tp)
{
}

// FUNCTION: SADX 0x005c5dd0
void SaruTraceCircle(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 tmp_pos;
	tmp_pos.x = twp->scl.z;
	tmp_pos.y = twp->pos.y;
	tmp_pos.z = 0.0f;
	njPushMatrix(&_nj_unit_matrix_);
	if (twp->ang.x != 0)
	{
		njRotateY(0, (Uint16)twp->ang.x);
	}
	njCalcPoint(0, &tmp_pos, &twp->pos);
	njPopMatrix(1);
	twp->pos.x = twp->pos.x + ewp->home.x;
	twp->pos.z = twp->pos.z + ewp->home.z;
}

// STUB: SADX 0x005c6020
void SaruExecutor(struct task *tp)
{
}

// STUB: SADX 0x005c62a0
void FUN_005c62a0(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c6330
void SaruEditMode(struct task *tp)
{
}

// FUNCTION: SADX 0x005c68f0
void FUN_005c68f0(struct taskwk *param_1, int param_2)
{
	if (param_1->flag & 0x2000)
	{
		*(float *)((char *)param_1 + 0x24) = Shadow(param_1, 1.0f) + 4.0f;
	}
}

// FUNCTION: SADX 0x005c6930
void FUN_005c6930(struct taskwk *param_1, int param_2)
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
void FUN_005c7050(struct taskwk *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x005c71d0
void SaruRoundSmoke(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 local_3c;
	struct NJS_POINT3 local_30g;
	struct NJS_POINT3 local_24g;
	struct NJS_POINT3 local_18;
	int local_8g;
	local_30g.x = 1.0f;
	local_30g.y = -2.0f;
	local_30g.z = 0.0f;
	local_24g.x = 0.5f;
	local_24g.y = 0.0f;
	local_24g.z = 0.0f;
	for (local_8g = 0; local_8g < 8; local_8g++)
	{
		njPushMatrix(&_nj_unit_matrix_);
		if ((local_8g << 0xd) != 0)
		{
			njRotateY(0, (unsigned short)(local_8g << 0xd));
		}
		njCalcVector(0, &local_24g, &local_18);
		njCalcPoint(0, &local_30g, &local_3c);
		njPopMatrix(1);
		saru_smoke1.velo = local_18;
		njAddVector(&local_3c, &twp->pos);
		saru_smoke1.pos = local_3c;
		FUN_005536c0(&saru_smoke1);
	}
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

// STUB: SADX 0x005c7740
void SaruTurnP(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c7a80
void FUN_005c7a80(struct task *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c7ff0
void FUN_005c7ff0(struct task *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c8300
void FUN_005c8300(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c84d0
void SaruThrow(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c8b50
void SaruBombA(struct task *tp)
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

// FUNCTION: SADX 0x005c9690
void SaruBombDisplayer(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	njPushMatrix(0);
	SphericalExplosionUV(local_8->timer.l);
	SphericalExplosionPos(local_8->scl.z);
	SphericalExplosionAlpha(local_8->scl.z);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y != 0)
	{
		njRotateY(0, (unsigned short)local_8->ang.y);
	}
	FUN_0067d2d0(0, local_8->scl.x, local_8->scl.x, local_8->scl.x);
	___njSetTexture(&DAT_02684a9c);
	SphericalExplosionDraw();
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x005c9750
void SaruBombCollision(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005c9950
void SaruBombCountDown(struct taskwk *twp, struct enemywk *ewp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x005c9ab0
void SaruBombCountDraw(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005c9d00
void FUN_005c9d00(struct taskwk *param_1, struct enemywk *param_2)
{
	SaruBombExplosionDraw(param_1, param_2);
}

#pragma optimize("", off)
// STUB: SADX 0x005c9d20
void SaruBombExplosionDraw(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005c9e30
void SaruBombADisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	switch (local_cg->mode)
	{
		case 0:
			SaruBombDraw(local_cg, (struct enemywk *)local_8g);
			break;
		case 1:
			SaruBombCountDraw(local_cg, (struct enemywk *)local_8g);
			break;
		case 2:
			SaruBombExplosionDraw(local_cg, (struct enemywk *)local_8g);
			break;
	}
}
