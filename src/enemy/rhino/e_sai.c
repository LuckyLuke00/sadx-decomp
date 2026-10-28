#include "decls.h"
#include <math.h>
#include <stdlib.h>
void FUN_008d8580(int param_1, char *param_2);
void FUN_008d76c0(int *param_1, int *param_2);
void FUN_008d7730(struct taskwk *param_1);
void FUN_008d8710(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d8800(int param_1, int param_2, int param_3);
void CalcAimAngle(struct taskwk *twp, struct enemywk *ewp);
void SaiSearch(struct taskwk *twp, struct enemywk *ewp, struct taskwk *ptwp);
void SaiScramble(struct taskwk *twp, struct taskwk *ptwp, struct enemywk *ewp);
void SaiDash(struct taskwk *twp, struct enemywk *ewp);
void CreateSaiCatSmoke(struct taskwk *param_1, struct enemywk *param_2);
void SaiCatAnimation(struct taskwk *twp, struct enemywk *ewp);
void SaiMove(struct taskwk *twp, struct enemywk *ewp);
void SaiDraw(struct taskwk *twp, struct enemywk *ewp);
void SaiNormal(struct taskwk *twp, struct enemywk *ewp);
void SaiDisplayer(struct task *tp);
void SaiEditMode(struct taskwk *twp);
void FUN_008d7d30(struct taskwk *param_1);
void CreateFlash2(float x, float y, float z, float scl);
void CreateExpParts(struct taskwk *twp, struct NJS_MODEL **model, struct NJS_TEXLIST *tex);
void CreateExpSpring(struct taskwk *twp, unsigned char num);
extern struct NJS_TEXLIST texlist_e_sai;
extern struct NJS_MODEL *sai_model;
void FUN_008d75f0(struct enemywk *param_1, struct taskwk *param_2);
void FUN_008d7d30(struct taskwk *param_1);
extern struct NJS_ACTION *action_rhino;
extern struct obj object_rhino_jet[1];
void FUN_008d75c0(int param_1, char *param_2);
void FUN_008d88b0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_MATERIAL matlist_rhino_jet[1];

// STUB: SADX 0x008d6ec0
void EnemySai(struct task *tp)
{
}

// STUB: SADX 0x008d74f0
void CalcAimAngle(struct taskwk *twp, struct enemywk *ewp)
{
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
void FUN_008d75f0(struct enemywk *param_1, struct taskwk *param_2)
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

// STUB: SADX 0x008d7880
void SaiScramble(struct taskwk *twp, struct taskwk *ptwp, struct enemywk *ewp)
{
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
void FUN_008d7d30(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008d7e80
void CreateSaiCatSmoke(struct taskwk *param_1, struct taskwk *param_2)
{
	FUN_008d75c0((int)param_1, (char *)param_2);
	*(int *)((char *)param_2 + 0x1a8) = 0;
	((float *)((char *)param_2 + 0x0))[3] = -0.15f; // data + 0xc
	FUN_008d7d30(param_1);
	if (*(float *)((char *)param_2 + 4) < 0.5f)
	{
		*(float *)((char *)param_2 + 4) = 0.0f;
		((float *)((char *)param_2 + 0x0))[3] = 0.0f;
		param_1->mode = 3;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x008d7ef0
void SaiCatAnimation(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d8030
void SaiMove(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008d8110
void SaiDraw(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x008d8330
void SaiJetDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x008d8580
void FUN_008d8580(int param_1, char *param_2)
{
	matlist_rhino_jet[0].attr_texId = (int)((unsigned char)(*(char *)(param_1 + 3)) % 3);
	matlist_rhino_jet[0].diffuse.argb.b = (char)((char)*param_2 + 3);
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
	___dsDrawObject((struct obj *)action_rhino);
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
