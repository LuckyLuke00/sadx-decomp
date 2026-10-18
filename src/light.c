#include "decls.h"
#include <string.h>

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

int __fastcall FUN_004199f0(void *self, float value);
void njPushMatrix(float *m);
void njTranslateV(float *m, struct NJS_POINT3 *v);
void njRotateZ(float *m, int ang);
void njRotateX(float *m, unsigned short ang);
void njRotateY(float *m, unsigned short ang);
void njCalcVector(float *m, struct NJS_POINT3 *v, struct NJS_POINT3 *out);
void njPopMatrixEx();
void FUN_007d21b0(void *param_1);
void FUN_005b5aa0();

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
	struct taskwk *twp = tp->twp;
	switch (twp->mode)
	{
	case 0:
		le_load_stagelight();
		dsEditLightInit();
		tp->dest = FUN_0049f340;
		twp->mode++;
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
struct task *asSetLight(struct task *tp, struct NJS_LIGHT *light, struct LightInfo *info)
{
	struct taskwk *ctwp;
	struct task *ctp;
	struct taskwk *twp;
	twp = tp->twp;
	ctp = CreateChildTask(2, FUN_0049f4a0, tp);
	if (ctp == 0)
	{
		return 0;
	}
	ctwp = ctp->twp;
	if (ctwp)
	{
		if (twp)
		{
			struct NJS_POINT3 out;
			struct NJS_POINT3 pos = info->pos;
			njPushMatrix(_nj_unit_matrix_);
			njTranslateV(0, &twp->pos);
			if (twp->ang.z)
			{
				njRotateZ(0, (unsigned short)twp->ang.z);
			}
			if (twp->ang.x)
			{
				njRotateX(0, twp->ang.x);
			}
			if (twp->ang.y)
			{
				njRotateY(0, twp->ang.y);
			}
			njCalcVector(0, &pos, &out);
			njPopMatrixEx();
			ctwp->pos.x = twp->pos.x + pos.x;
			ctwp->pos.y = twp->pos.y + pos.y;
			ctwp->pos.z = twp->pos.z + pos.z;
		}
		ctwp->counter.ptr = light;
		ctwp->timer.ptr = info;
	}
	return ctp;
}

// FUNCTION: SADX 0x0049f4a0
void FUN_0049f4a0(struct task *tp)
{
	struct taskwk *twp = tp->twp;
	switch (twp->mode)
	{
	case 0:
	{
		struct LightInfo *info = (struct LightInfo *)twp->timer.ptr;
		twp->wtimer = ((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744;
		le_CreateLight(3, info->lsrc);
		le_SetLightIntensity(3, info->spc, info->dif, info->amb);
		le_SetLightColor(3, info->argb.r, info->argb.g, info->argb.b);
		if (info->lsrc & 0xa)
		{
			le_SetLightDirection(3, info->vec.x, info->vec.y, info->vec.z);
		}
		tp->dest = FUN_0049f5e0;
		twp->mode++;
		break;
	}
	case 1:
		if (twp->wtimer != (((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744))
		{
			twp->mode = 2;
		}
		break;
	case 2:
		FreeTask(tp);
		break;
	}
}

// FUNCTION: SADX 0x0049f5e0
void FUN_0049f5e0(struct task *tp)
{
	void *light;
	struct taskwk *twp = tp->twp;
	light = twp->counter.ptr;
	FUN_007d21b0(light);
}

// FUNCTION: SADX 0x0049f610
void get_stg_act(int *stage_out, int *act_out)
{
	int act;
	int stage;
	act = ((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744;
	stage = act >> 8;
	act = (unsigned char)act;
	if (stage == 0x1a || stage == 0x21 || stage == 0x1d)
	{
		cnv_stg_act(&stage, &act);
	}
	*act_out = act;
	*stage_out = stage;
}

// FUNCTION: SADX 0x0049f680
static void cnv_stg_act(int *stage_p, int *act_p)
{
	int act;
	int stage;
	stage = *stage_p;
	act = *act_p;
	if (stage == 0x1a)
	{
		int time;
		switch (act)
		{
		case 2:
			break;
		case 5:
			act = 0;
			break;
		case 4:
			if (checkInSsHodel() == 2)
			{
				act = 0;
				break;
			}
		default:
			time = SeqGetTime();
			if (time == 1)
			{
				act = 1;
			}
			else if (time == 2)
			{
				act = 3;
			}
			else
			{
				act = 0;
			}
		}
	}
	else if (stage == 0x21)
	{
		if (act < 3)
		{
			act = SeqGetTime();
		}
	}
	else if (stage == 0x1d)
	{
		stage = 1;
		act = 0;
	}
	*act_p = act;
	*stage_p = stage;
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
	int stage;
	get_stg_act(&stage, &act);
	le_lightInit(stage, act);
}

// FUNCTION: SADX 0x0049f7c0
void le_loadLight(int stg, int act)
{
	int pno;
	int player;
	pno = 0;
	pno = GetPlayerNumber();
	if (pno != 6)
	{
		pno = 0;
	}
	player = pno;
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
	int pno;
	int player;
	pno = 0;
	pno = GetPlayerNumber();
	if (pno != 6)
	{
		pno = 0;
	}
	player = pno;
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
void le_CreateLight(int no, int flg)
{
	if (no)
	{
		DAT_05b39da8[no & 3] = flg;
		if (flg & 2)
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
	int f;
	struct LE_LIGHT_ENV *e;
	if (no)
	{
		e = &DAT_05b39cb0;
		f = -1;
		if (no)
		{
			e = &DAT_05b39bf0[no & 3];
			f = DAT_05b39da8[no & 3];
		}
		e->dif = dif;
		if (f & 0x10)
		{
			e->spe = spe;
		}
		if (f & 1)
		{
			e->ambB = amb;
			e->ambG = amb;
			e->ambR = amb;
		}
	}
}

// FUNCTION: SADX 0x0049fa00
void le_SetLightColor(int no, float r, float g, float b)
{
	struct LE_LIGHT_ENV *env;
	if (no)
	{
		env = &DAT_05b39cb0;
		if (no)
		{
			env = &DAT_05b39bf0[no & 3];
		}
		env->r = r;
		env->g = g;
		env->b = b;
	}
}

// FUNCTION: SADX 0x0049fa50
void le_SetLightDirection(int no, float x, float y, float z)
{
	struct LE_LIGHT_ENV *env;
	if (no)
	{
		env = &DAT_05b39cb0;
		if (no)
		{
			env = &DAT_05b39bf0[no & 3];
		}
		env->vec.x = x;
		env->vec.y = y;
		env->vec.z = z;
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
struct LE_LIGHT_ENV *le_find_env(int stg, int act, int lig)
{
	int idx;
	struct LE_LIGHT_ENV *e;
	for (e = le_stg, idx = 0; e->stgNo != 0xff && idx < 0xff; idx++, e++)
	{
		if (e->stgNo == stg && e->actNo == act && e->ligNo == lig)
		{
			return e;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x0049fe40
void le_set_env(int stg, int act)
{
	int e;
	struct LE_LIGHT_ENV *d;
	struct LE_LIGHT_ENV *l;
	int idx;
	l = le_stg;
	d = DAT_05b39bf0;
	memset(DAT_05b39bf0, 0, sizeof(DAT_05b39bf0));
	*d = le_env_dflt;
	d->flgs = 1;
	d->stgNo = stg;
	d->actNo = act;
	d->ligNo = 0;
	d[1].ligNo = 1;
	d[2].ligNo = 2;
	d[3].ligNo = 3;
	for (idx = 0; l->stgNo != 0xff && idx < 0xff; idx++, l++)
	{
		if (l->stgNo == stg && (l->actNo == act || l->actNo == 0))
		{
			e = l->ligNo & 3;
			d = &DAT_05b39bf0[e];
			*d = *l;
			d->stgNo = stg;
			d->actNo = act;
			d->ligNo = e;
		}
	}
}

// FUNCTION: SADX 0x0049ff50
void le_set_paenv(int stg, int act, int lig)
{
	struct LE_PALIGHT_ENV *pa;
	memset(&DAT_05b39ce0, 0, sizeof(DAT_05b39ce0));
	pa = le_find_paenv(stg, act, lig);
	if (pa == 0)
	{
		pa = le_find_paenv(stg, 0, lig);
	}
	if (pa == 0)
	{
		pa = le_find_paenv(0, 0, lig);
	}
	if (pa)
	{
		DAT_05b39ce0 = *pa;
		lig = lig < 0 ? -lig : lig;
		if (lig == 6)
		{
			DAT_05b39ce0.chrNo = 6;
		}
		else if (lig == 8)
		{
			DAT_05b39ce0.chrNo = 8;
		}
	}
	if (!(DAT_05b39ce0.flgs & 2))
	{
		DAT_05b39ce0.vec = DAT_05b39bf0[0].vec;
	}
}
