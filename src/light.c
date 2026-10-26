#include "decls.h"
#include <string.h>
static struct LE_PALIGHT_ENV *le_find_paenv(int stg, int act, int chr);
static struct LE_PALIGHT_ENV *le_find_paenv(int, int, int);

extern float DAT_05b39d10;
extern void *DAT_05ab39ac;
extern struct LE_LIGHT_ENV DAT_05b39bf0[4];
extern struct LE_LIGHT_ENV DAT_05b39cb0;
extern struct LE_PALIGHT_ENV DAT_05b39ce0;
extern char DAT_05b39da8[4];
extern unsigned char DAT_05b39db1;
extern int DAT_05b39be8;
extern int DAT_05b39bec;
extern int DAT_05b39dac;

int __fastcall FUN_004199f0(void *param_1, float param_2);
void njPushMatrix(float *param_1);
void njTranslateV(float *param_1, struct NJS_POINT3 *param_2);
void njRotateZ(float *param_1, int param_2);
void njRotateX(float *param_1, unsigned short param_2);
void njRotateY(float *param_1, unsigned short param_2);
void njCalcVector(float *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3);
void njPopMatrixEx();
void FUN_007d21b0(...);
void FUN_005b5aa0(...);

void FUN_0049f340(struct task *);
void FUN_0049f4a0(struct task *);
void FUN_0049f5e0(struct task *);
static void cnv_stg_act(int *, int *);

// FUNCTION: SADX 0x0049f2c0
void ChangePowerMaterial()
{
	FUN_004199f0(DAT_05ab39ac, DAT_05b39d10);
}

// FUNCTION: SADX 0x0049f2e0
void Light(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		le_load_stagelight();
		dsEditLightInit();
		tp->dest = FUN_0049f340;
		local_8->mode++;
		break;
	case 1:
		break;
	case 2:
		FreeTask(tp);
		break;
	}
}

// FUNCTION: SADX 0x0049f340
void FUN_0049f340(struct task *)
{
	le_DeleteLight(0);
}

// FUNCTION: SADX 0x0049f350
struct task *asSetLight(struct task *tp, struct NJS_LIGHT *glp, struct LightInfo *lip)
{
	struct taskwk *local_8g;
	struct task *local_cj;
	struct taskwk *local_10;
	local_10 = tp->twp;
	local_cj = CreateChildTask(2, FUN_0049f4a0, tp);
	if (local_cj == 0)
	{
		return 0;
	}
	local_8g = local_cj->twp;
	if (local_8g)
	{
		if (local_10)
		{
			struct NJS_POINT3 local_20g;
			struct NJS_POINT3 local_2c = lip->pos;
			njPushMatrix(_nj_unit_matrix_);
			njTranslateV(0, &local_10->pos);
			if (local_10->ang.z)
			{
				njRotateZ(0, (unsigned short)local_10->ang.z);
			}
			if (local_10->ang.x)
			{
				njRotateX(0, local_10->ang.x);
			}
			if (local_10->ang.y)
			{
				njRotateY(0, local_10->ang.y);
			}
			njCalcVector(0, &local_2c, &local_20g);
			njPopMatrixEx();
			local_8g->pos.x = local_10->pos.x + local_2c.x;
			local_8g->pos.y = local_10->pos.y + local_2c.y;
			local_8g->pos.z = local_10->pos.z + local_2c.z;
		}
		local_8g->counter.ptr = glp;
		local_8g->timer.ptr = lip;
	}
	return local_cj;
}

// FUNCTION: SADX 0x0049f4a0
void FUN_0049f4a0(struct task *param_1)
{
	struct taskwk *local_8 = param_1->twp;
	switch (local_8->mode)
	{
	case 0:
	{
		struct LightInfo *local_c = (struct LightInfo *)local_8->timer.ptr;
		local_8->wtimer = ((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744;
		le_CreateLight(3, local_c->lsrc);
		le_SetLightIntensity(3, local_c->spc, local_c->dif, local_c->amb);
		le_SetLightColor(3, local_c->argb.r, local_c->argb.g, local_c->argb.b);
		if (local_c->lsrc & 0xa)
		{
			le_SetLightDirection(3, local_c->vec.x, local_c->vec.y, local_c->vec.z);
		}
		param_1->dest = FUN_0049f5e0;
		local_8->mode++;
		break;
	}
	case 1:
		if (local_8->wtimer != (((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744))
		{
			local_8->mode = 2;
		}
		break;
	case 2:
		FreeTask(param_1);
		break;
	}
}

// FUNCTION: SADX 0x0049f5e0
void FUN_0049f5e0(struct task *param_1)
{
	void *local_8g;
	struct taskwk *local_cg = param_1->twp;
	local_8g = local_cg->counter.ptr;
	FUN_007d21b0(local_8g);
}

// FUNCTION: SADX 0x0049f610
void get_stg_act(int *a_stg, int *a_act)
{
	int act;
	int stg;
	act = ((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744;
	stg = act >> 8;
	act = (unsigned char)act;
	if (stg == 0x1a || stg == 0x21 || stg == 0x1d)
	{
		cnv_stg_act(&stg, &act);
	}
	*a_act = act;
	*a_stg = stg;
}

// FUNCTION: SADX 0x0049f680
static void cnv_stg_act(int *a_stg, int *a_act)
{
	int local_cg;
	int local_8g;
	local_8g = *a_stg;
	local_cg = *a_act;
	if (local_8g == 0x1a)
	{
		int local_10;
		switch (local_cg)
		{
		case 2:
			break;
		case 5:
			local_cg = 0;
			break;
		case 4:
			if (checkInSsHodel() == 2)
			{
				local_cg = 0;
				break;
			}
		default:
			local_10 = SeqGetTime();
			if (local_10 == 1)
			{
				local_cg = 1;
			}
			else if (local_10 == 2)
			{
				local_cg = 3;
			}
			else
			{
				local_cg = 0;
			}
		}
	}
	else if (local_8g == 0x21)
	{
		if (local_cg < 3)
		{
			local_cg = SeqGetTime();
		}
	}
	else if (local_8g == 0x1d)
	{
		local_8g = 1;
		local_cg = 0;
	}
	*a_act = local_cg;
	*a_stg = local_8g;
}

// FUNCTION: SADX 0x0049f750
void le_titleLightInit()
{
	DAT_05b9d724 = 0;
	DAT_05b9d744 = 1;
	le_load_stagelight();
	le_lightInit(0, 0);
}

// FUNCTION: SADX 0x0049f780
void FUN_0049f780()
{
	FUN_005b5aa0();
}

// FUNCTION: SADX 0x0049f790
void dsEditLightInit()
{
	int act;
	int stg;
	get_stg_act(&stg, &act);
	le_lightInit(stg, act);
}

// FUNCTION: SADX 0x0049f7c0
void le_loadLight(int stg, int act)
{
	int local_cg;
	int local_8g;
	local_cg = 0;
	local_cg = GetPlayerNumber();
	if (local_cg != 6)
	{
		local_cg = 0;
	}
	local_8g = local_cg;
	cnv_stg_act(&stg, &act);
	FUN_005b5aa0();
	le_set_env(stg, act);
	DAT_05b39cb0 = le_ctrl_dflt;
	dsGDLoadPalette(stg, act);
	FUN_005b5aa0();
}

// FUNCTION: SADX 0x0049f840
void le_lightInit(int stg, int act)
{
	int local_cg;
	int local_8g;
	local_cg = 0;
	local_cg = GetPlayerNumber();
	if (local_cg != 6)
	{
		local_cg = 0;
	}
	local_8g = local_cg;
	cnv_stg_act(&stg, &act);
	DAT_05b39bec = 0;
	DAT_05b39be8 = 0;
	DAT_05b39dac = 0;
	FUN_005b5aa0();
	le_set_env(stg, act);
	DAT_05b39cb0 = le_ctrl_dflt;
	dsGDLoadPalette(stg, act);
	FUN_005b5aa0();
}

// FUNCTION: SADX 0x0049f8e0
void le_CreateLight(int no, int typ)
{
	if (no)
	{
		DAT_05b39da8[no & 3] = typ;
		if (typ & 2)
		{
			DAT_05b39bf0[no & 3].flgs |= 1;
		}
	}
}

// FUNCTION: SADX 0x0049f930
void le_DeleteLight(int no)
{
	if (no)
	{
		DAT_05b39da8[no & 3] = 0;
		DAT_05b39bf0[no & 3].flgs &= ~1;
	}
}

// FUNCTION: SADX 0x0049f970
void le_SetLightIntensity(int no, float spe, float dif, float amb)
{
	int local_8g;
	struct LE_LIGHT_ENV *local_cg;
	if (no)
	{
		local_cg = &DAT_05b39cb0;
		local_8g = -1;
		if (no)
		{
			local_cg = &DAT_05b39bf0[no & 3];
			local_8g = DAT_05b39da8[no & 3];
		}
		local_cg->dif = dif;
		if (local_8g & 0x10)
		{
			local_cg->spe = spe;
		}
		if (local_8g & 1)
		{
			local_cg->ambB = amb;
			local_cg->ambG = amb;
			local_cg->ambR = amb;
		}
	}
}

// FUNCTION: SADX 0x0049fa00
void le_SetLightColor(int no, float r, float g, float b)
{
	struct LE_LIGHT_ENV *local_8;
	if (no)
	{
		local_8 = &DAT_05b39cb0;
		if (no)
		{
			local_8 = &DAT_05b39bf0[no & 3];
		}
		local_8->r = r;
		local_8->g = g;
		local_8->b = b;
	}
}

// FUNCTION: SADX 0x0049fa50
void le_SetLightDirection(int no, float x, float y, float z)
{
	struct LE_LIGHT_ENV *local_8;
	if (no)
	{
		local_8 = &DAT_05b39cb0;
		if (no)
		{
			local_8 = &DAT_05b39bf0[no & 3];
		}
		local_8->vec.x = x;
		local_8->vec.y = y;
		local_8->vec.z = z;
	}
}

// FUNCTION: SADX 0x0049fd70
int le_load_stagelight()
{
	DAT_05b39db1 = 1;
	if (le_stg[0].stgNo == 0)
	{
		le_env_dflt = le_stg[0];
		le_env_dflt.stgNo = 0;
		le_env_dflt.actNo = 0;
		le_env_dflt.ligNo = 0;
		le_env_dflt.flgs = 1;
	}
	le_stg[0].stgNo = 0;
	le_stg[255].stgNo = 0xff;
	return 1;
}

// FUNCTION: SADX 0x0049fdd0
struct LE_LIGHT_ENV *le_find_env(int stg, int act, int ligNo)
{
	int local_8g;
	struct LE_LIGHT_ENV *local_cg;
	for (local_cg = le_stg, local_8g = 0; local_cg->stgNo != 0xff && local_8g < 0xff; local_8g++, local_cg++)
	{
		if (local_cg->stgNo == stg && local_cg->actNo == act && local_cg->ligNo == ligNo)
		{
			return local_cg;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x0049fe40
void le_set_env(int stg, int act)
{
	int local_14;
	struct LE_LIGHT_ENV *local_10;
	struct LE_LIGHT_ENV *local_ci;
	int local_8g;
	local_ci = le_stg;
	local_10 = DAT_05b39bf0;
	memset(DAT_05b39bf0, 0, sizeof(DAT_05b39bf0));
	*local_10 = le_env_dflt;
	local_10->flgs = 1;
	local_10->stgNo = stg;
	local_10->actNo = act;
	local_10->ligNo = 0;
	local_10[1].ligNo = 1;
	local_10[2].ligNo = 2;
	local_10[3].ligNo = 3;
	for (local_8g = 0; local_ci->stgNo != 0xff && local_8g < 0xff; local_8g++, local_ci++)
	{
		if (local_ci->stgNo == stg && (local_ci->actNo == act || local_ci->actNo == 0))
		{
			local_14 = local_ci->ligNo & 3;
			local_10 = &DAT_05b39bf0[local_14];
			*local_10 = *local_ci;
			local_10->stgNo = stg;
			local_10->actNo = act;
			local_10->ligNo = local_14;
		}
	}
}

// FUNCTION: SADX 0x0049ff50
void le_set_paenv(int stg, int act, int chr)
{
	struct LE_PALIGHT_ENV *local_8;
	memset(&DAT_05b39ce0, 0, sizeof(DAT_05b39ce0));
	local_8 = le_find_paenv(stg, act, chr);
	if (local_8 == 0)
	{
		local_8 = le_find_paenv(stg, 0, chr);
	}
	if (local_8 == 0)
	{
		local_8 = le_find_paenv(0, 0, chr);
	}
	if (local_8)
	{
		DAT_05b39ce0 = *local_8;
		chr = chr < 0 ? -chr : chr;
		if (chr == 6)
		{
			DAT_05b39ce0.chrNo = 6;
		}
		else if (chr == 8)
		{
			DAT_05b39ce0.chrNo = 8;
		}
	}
	if (!(DAT_05b39ce0.flgs & 2))
	{
		DAT_05b39ce0.vec = DAT_05b39bf0[0].vec;
	}
}

// FUNCTION: SADX 0x004a0040
static struct LE_PALIGHT_ENV *le_find_paenv(int stg, int act, int chr)
{
	struct LE_PALIGHT_ENV *local_ci;
	struct LE_PALIGHT_ENV *local_14;
	int local_10m;
	int local_8g;
	local_ci = &le_plyrPal[0];
	local_14 = 0;
	local_10m = 0;
	if (chr < 0)
	{
		local_10m = 1;
		chr = -chr;
	}
	for (local_8g = 0; local_ci->stgNo != 0xff && local_8g < 0xff; local_8g++)
	{
		if (local_ci->stgNo == stg && local_ci->actNo == act &&
			(local_ci->chrNo == chr || (local_10m && local_ci->chrNo == 0)))
		{
			local_14 = local_ci;
			if (local_ci->chrNo == chr)
			{
				break;
			}
		}
		local_ci++;
	}
	return local_14;
}

// STUB: SADX 0x004a0100
int dsGDLoadPalette(unsigned short stg, unsigned short act)
{
	return (int)0;
}
