#include "decls.h"
#include <math.h>
#include <stdlib.h>
void CreateSaiJetSmoke(struct taskwk *twp, struct enemywk *ewp);
void FUN_00609b40(int param_1);
extern struct NJS_MODEL model_rhino_catarpl[];
extern struct NJS_MODEL model_rhino_catarpr[];
extern union NJS_COLOR vuvS_0_rhino_catarpl[];
extern union NJS_COLOR vuvS_0_rhino_catarpr[];
extern struct NJS_ACTION action_rhino_attack[];
static struct NJS_POINT3 jet_pos[3];
void SaiJetDraw(struct taskwk *twp, struct enemywk *ewp);
void FUN_008d8580(int param_1, char *param_2);
void FUN_008d76c0(int *param_1, int *param_2);
void FUN_008d7730(struct taskwk *param_1);
void FUN_008d8710(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d8800(int param_1, int param_2, int param_3);
void CalcAimAngle(struct taskwk *twp, struct enemywk *ewp);
void SaiSearch(struct taskwk *twp, struct enemywk *ewp, struct taskwk *ptwp);
void SaiScramble(struct taskwk *twp, struct taskwk *ptwp, struct enemywk *ewp);
void SaiDash(struct taskwk *twp, struct enemywk *ewp);
void CreateSaiCatSmoke(struct taskwk *twp);
void SaiCatAnimation(struct taskwk *twp, struct enemywk *ewp);
void SaiMove(struct taskwk *twp, struct enemywk *ewp);
void SaiDraw(struct taskwk *twp, struct enemywk *ewp);
void SaiNormal(struct taskwk *twp, struct enemywk *ewp);
void SaiDisplayer(struct task *tp);
void SaiEditMode(struct taskwk *twp);
void CreateFlash2(float x, float y, float z, float scl);
void CreateExpParts(struct taskwk *twp, struct NJS_MODEL **model, struct NJS_TEXLIST *tex);
void CreateExpSpring(struct taskwk *twp, unsigned char num);
extern struct NJS_TEXLIST texlist_e_sai;
extern struct NJS_MODEL *sai_model;
void FUN_008d75f0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_ACTION action_rhino[];
extern struct obj object_rhino_jet[1];
void FUN_008d75c0(int param_1, char *param_2);
void FUN_008d88b0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_MATERIAL matlist_rhino_jet[1];

// STUB: SADX 0x008d6ec0
void EnemySai(struct task *tp)
{
}

// FUNCTION: SADX 0x008d74f0
void CalcAimAngle(struct taskwk *twp, struct enemywk *ewp)
{
	short local_14;
	struct colliwk *local_10;
	struct taskwk *local_cj;
	struct colliwk *local_8g;

	local_cj = DAT_05baf368[0];
	local_14 = local_cj->flag;
	local_10 = twp->cwp;
	local_8g = twp->cwp->hit_cwp;
	ewp->velo.z = 0.02f;
	if (ewp->velo.x > 0.48f)
	{
		ewp->velo.x = 0.48f;
	}
	ewp->angy_spd = 0;
	if ((local_10->flag & 1) && local_8g->id == 4)
	{
		FUN_008d75f0(twp, ewp);
		twp->mode = 2;
		twp->wtimer = 0;
		twp->pos.x = ewp->pre.x;
		twp->pos.z = ewp->pre.z;
	}
	FUN_008d75c0((int)twp, (char *)&ewp->sub.b[0]);
}

// FUNCTION: SADX 0x008d75c0
void FUN_008d75c0(int param_1, char *param_2)
{
	*param_2 = (char)((char)*param_2 - 8);
	if ((char)*param_2 < 0x23)
	{
		*param_2 = 0x23;
	}
}

// STUB: SADX 0x008d75f0
void FUN_008d75f0(struct taskwk *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x008d76c0
void FUN_008d76c0(int *param_1, int *param_2)
{
	*(float *)((char *)param_2 + 4) = 0.0f;
	*(long *)((char *)param_1 + 0x18) = AdjustAngle(*(long *)((char *)param_1 + 0x18), *(long *)((char *)param_2 + 0x1d0), 0xf0);
	*(long *)((char *)param_2 + 0x1a8) = 0xf0;
	if (SubAngle(*(long *)((char *)param_1 + 0x18), *(long *)((char *)param_2 + 0x1d0)) < 0x800)
	{
		*(char *)param_1 = 1;
		*(short *)((char *)param_1 + 6) = 0;
	}
}

// FUNCTION: SADX 0x008d7730
void FUN_008d7730(struct taskwk *param_1)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0, param_1->pos.z, 1.4f);
	CreateExpParts(param_1, &sai_model, &texlist_e_sai);
	CreateExpSpring(param_1, 8);
}

// STUB: SADX 0x008d77a0
void SaiSearch(struct taskwk *twp, struct enemywk *ewp, struct taskwk *ptwp)
{
}

// FUNCTION: SADX 0x008d7880
void SaiScramble(struct taskwk *twp, struct taskwk *ptwp, struct enemywk *ewp)
{
	long local_8j;
	long local_cg;

	ewp->velo.z = -0.5f;
	ewp->angy_spd = 0;
	local_cg = twp->ang.y;
	ewp->aim_angle = (long)(atan2((double)(ptwp->pos.x - twp->pos.x), (double)(ptwp->pos.z - twp->pos.z))
		* 65536.0 / 6.283184) - 0x4000;
	local_8j = SubAngle(ewp->aim_angle, local_cg);
	local_8j &= 0xffff;
	twp->ang.y = AdjustAngle(local_cg, ewp->aim_angle, 0x300);
	FUN_008d75c0((int)twp, (char *)&ewp->sub.b[0]);
	if (twp->wtimer % 2 != 0)
	{
		CreateSaiJetSmoke(twp, ewp);
	}
	if (twp->wtimer > 100)
	{
		twp->wtimer = 0;
		twp->mode = 4;
	}
}

// STUB: SADX 0x008d7990
void CreateSaiJetSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x008d7be0
void SaiDash(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x008d7d00
void FUN_008d7d00(int param_1, char *param_2)
{
	*param_2 = *param_2 + 2;
	if (*param_2 > 0xfc)
	{
		*param_2 = 0xfc;
	}
}

// STUB: SADX 0x008d7d30
void CreateSaiCatSmoke(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008d7e80
void FUN_008d7e80(struct taskwk *param_1, struct taskwk *param_2)
{
	FUN_008d75c0((int)param_1, (char *)param_2);
	*(int *)((char *)param_2 + 0x1a8) = 0;
	((float *)((char *)param_2 + 0x0))[3] = -0.15f; // data + 0xc
	CreateSaiCatSmoke(param_1);
	if (*(float *)((char *)param_2 + 4) < 0.5f)
	{
		*(float *)((char *)param_2 + 4) = 0.0f;
		((float *)((char *)param_2 + 0x0))[3] = 0.0f;
		param_1->mode = 3;
	}
}

// FUNCTION: SADX 0x008d7ef0
void SaiCatAnimation(struct taskwk *twp, struct enemywk *ewp)
{
	union NJS_COLOR *local_8g;
	int local_cg;
	unsigned short local_10g;
	short local_14i;

	local_8g = (union NJS_COLOR *)twp->timer.ptr;
	local_10g = model_rhino_catarpl[0].meshsets[0].nbMesh * 3;
	local_14i = (short)(ewp->velo.x * 20.0 + ewp->angy_spd * 3.141592 / 180.0 * 1.5);
	for (local_cg = 0; local_cg < local_10g; local_cg++, local_8g++)
	{
		local_8g->tex.v += local_14i;
	}
	model_rhino_catarpl[0].meshsets[0].vertuv = (union NJS_COLOR *)twp->timer.ptr;
	local_8g = (union NJS_COLOR *)twp->value.ptr;
	local_10g = model_rhino_catarpr[0].meshsets[0].nbMesh * 3;
	local_14i = (short)(ewp->velo.x * 20.0 - ewp->angy_spd * 3.141592 / 180.0 * 1.5);
	for (local_cg = 0; local_cg < local_10g; local_cg++, local_8g++)
	{
		local_8g->tex.v += local_14i;
	}
	model_rhino_catarpr[0].meshsets[0].vertuv = (union NJS_COLOR *)twp->value.ptr;
}

// FUNCTION: SADX 0x008d8030
void SaiMove(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->velo.x = ewp->velo.z + ewp->velo.x;
	if (ewp->velo.x > 3.4f)
	{
		ewp->velo.x = 3.4f;
	}
	if (ewp->velo.x < 0.0f)
	{
		ewp->velo.x = 0.0f;
	}
	ewp->velo.y += -0.4f - ewp->velo.y * 0.01f;
	twp->pos.x += UNKNOWN_DOUBLE_MACRO(ewp->velo.x) * njCos(twp->ang.y);
	twp->pos.y += ewp->velo.y;
	twp->pos.z -= UNKNOWN_DOUBLE_MACRO(ewp->velo.x) * njSin(twp->ang.y);
}

// DIFF: code: the two FUN_004a88c0 calls load the frame before they reserve its stack slot.
// FUNCTION: SADX 0x008d8110
void SaiDraw(struct taskwk *twp, struct enemywk *ewp)
{
	FUN_00609b40((int)twp);
	if (twp->mode == 3)
	{
		UNKNOWN_NO_CODE();
	}
	else
	{
		ewp->height = 0.0f;
		ewp->angz_spd = 0;
	}
	if (dsCheckViewV(&twp->pos, 10.0f) == 0)
	{
		return;
	}
	___dsSetPalette(6);
	___njSetTexture(&texlist_e_sai);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, (unsigned short)twp->ang.x);
	}
	if (twp->ang.y != 0)
	{
		njRotateY(0, (unsigned short)twp->ang.y);
	}
	FUN_0067d2d0(0, twp->scl.x, twp->scl.y, twp->scl.x);
	if (twp->mode == 3)
	{
		FUN_004a88c0(action_rhino_attack, ewp->nframe);
		ewp->nframe += 0.75;
	}
	else
	{
		FUN_004a88c0(action_rhino, ewp->nframe);
		ewp->nframe += 0.5;
	}
	ResetMaterial();
	njPopMatrix(1);
	___dsSetPalette(0);
	FUN_008d8580((int)twp, (char *)&ewp->sub.b[0]);
	SaiJetDraw(twp, ewp);
	model_rhino_catarpl[0].meshsets[0].vertuv = vuvS_0_rhino_catarpl;
	model_rhino_catarpr[0].meshsets[0].vertuv = vuvS_0_rhino_catarpr;
	if (UNKNOWN_DOUBLE_MACRO(ewp->nframe) > action_rhino[0].motion->nbFrame)
	{
		ewp->nframe -= action_rhino[0].motion->nbFrame;
	}
}

// FUNCTION: SADX 0x008d8330
void SaiJetDraw(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 jpos;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 10);
	SetMaterial((float)(ewp->sub.b[0]) / 255.0, 1.0, 1.0, 1.0);
	for (int local_18 = 0; local_18 < 3; local_18++)
	{
		___njSetTexture(&texlist_jet2);
		njPushMatrix(&_nj_unit_matrix_);
		njTranslateV(0, &twp->pos);
		if (twp->ang.z != 0)
		{
			njRotateZ(0, (unsigned short)twp->ang.z);
		}
		if (twp->ang.x != 0)
		{
			njRotateX(0, (unsigned short)twp->ang.x);
		}
		if (twp->ang.y + ewp->angz_spd != 0)
		{
			njRotateY(0, (unsigned short)(twp->ang.y + ewp->angz_spd));
		}
		FUN_0067d830(0, 0.0, 0.0, ewp->height);
		njCalcPoint(0, &jet_pos[local_18], &jpos);
		njPopMatrix(1);
	}
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, (unsigned short)twp->ang.x);
	}
	if (twp->ang.y + ewp->angz_spd != 0)
	{
		njRotateY(0, (unsigned short)(twp->ang.y + ewp->angz_spd));
	}
	FUN_0067d830(0, 0.0, 0.0, ewp->height);
	___njSetTexture(&texlist_e_sai);
	late_DrawObject(&object_rhino_jet[0], 4);
	njPopMatrix(1);
	ResetMaterial();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// FUNCTION: SADX 0x008d8580
void FUN_008d8580(int param_1, char *param_2)
{
	matlist_rhino_jet[0].attr_texId = (int)((unsigned char)(*(char *)(param_1 + 3)) % 3);
	matlist_rhino_jet[0].diffuse.argb.a = (char)((char)*param_2 + 3);
}

// STUB: SADX 0x008d85b0
void SaiDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x008d8710
void FUN_008d8710(struct taskwk *param_1, struct enemywk *param_2)
{
	EnemyCheckGroundCollision(param_1, param_2);
}

// FUNCTION: SADX 0x008d8730
void SaiEditMode(struct taskwk *twp)
{
	njPrintC(0x19, "EDIT");
	___dsSetPalette(6);
	___njSetTexture(&texlist_e_sai);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.y != 0)
	{
		njRotateY(0, (unsigned short)twp->ang.y);
	}
	___dsDrawObject(action_rhino[0].object);
	SetMaterial(0.0, 1.0, 1.0, 1.0);
	late_DrawObject(&object_rhino_jet[0], 4);
	ResetMaterial();
	matlist_rhino_jet[0].attr_texId = twp->btimer % 3;
	njPopMatrix(1);
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x008d8800
void FUN_008d8800(int param_1, int param_2, int param_3)
{
	if (*(int *)(param_2 + 0xc) != 0)
	{
		Free(*(void **)(param_2 + 0xc));
	}
	if (*(int *)(param_2 + 0x10) != 0)
	{
		Free(*(void **)(param_2 + 0x10));
	}
	FUN_005b5aa0(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x008d8850
void SaiNormal(struct taskwk *twp, struct enemywk *ewp)
{
	SaiCatAnimation(twp, ewp);
	SaiMove(twp, ewp);
	FUN_008d8710(twp, ewp);
	FUN_008d88b0(twp, ewp);
	SaiDraw(twp, ewp);
}

// FUNCTION: SADX 0x008d88f0
void FUN_008d88f0(struct task *param_1, struct taskwk *param_2, int param_3)
{
	if (CheckRangeOut(param_1) != 0)
	{
		FUN_008d8800((int)param_1, (int)param_2, param_3);
	}
	else
	{
		EntryColliList(param_2);
	}
}
