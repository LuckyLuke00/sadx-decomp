#include <math.h>
#include "decls.h"
struct NJS_TEXLIST;
struct NJS_TEXANIM;
extern struct NJS_TEXLIST texlist_get_emblem;
extern float DAT_00956ba8;
extern float DAT_0095c8d0;
extern void dispGetEmblem(struct task *);
extern void destGetEmblem(struct task *);
extern long NeonuLoadTexture(struct NJS_TEXLIST *);
extern struct task *CreateElementalTask(unsigned short, long, void (*)(struct task *));
extern void ADX_Close();
extern struct task *ADXTaskInit();

extern int DAT_05b3e05c;
extern int DAT_05cc3574;
extern char DAT_05cc3631;
extern unsigned char DAT_05bb00a9;
extern unsigned long DAT_05cccf84;
extern int DAT_05b9d838;
extern short *DAT_05baf368;
extern struct taskwk *DAT_05b42a7c;
extern char DAT_05ccca18;
extern char emblem_num[0x20];

void FUN_0055de60(struct _SC_NUMBERS *);
void Exec(struct task *);
void Disp(struct task *);

// FUNCTION: SADX 0x0049e0a0
void GetEmblem(struct SAVE_DATA *psd, long no)
{
	long local_8g = no / 8;
	long local_cg = 1 << (no % 8);

	*((char *)psd + local_8g + 0x240) |= local_cg;
	if (DAT_05b3e05c == 5 || DAT_05b3e05c == 10)
	{
		if (DAT_05cc3574 == 0)
		{
			DAT_05cc3631 = 1;
		}
		else
		{
			CreateSaveData();
		}
	}
	CheckEmbleAchievement(psd);
}

// FUNCTION: SADX 0x0049e130
int FUN_0049e130(struct SAVE_DATA *param_1)
{
	int local_14 = 0;
	unsigned char *local_ci = (unsigned char *)param_1 + 0x240;
	int local_8g;
	unsigned char local_dg;

	for (local_8g = 0x11; local_8g > 0; local_8g--)
	{
		local_dg = *local_ci;
		while (local_dg)
		{
			if (local_dg & 1)
			{
				local_14++;
			}
			local_dg = local_dg >> 1;
		}
		local_ci++;
	}
	return local_14;
}

// FUNCTION: SADX 0x0049e1a0
int FUN_0049e1a0(int param_1)
{
	if (param_1 >= 5)
	{
		param_1--;
	}
	if (param_1 >= 2)
	{
		param_1--;
	}
	return param_1 + 0x6f;
}

// FUNCTION: SADX 0x0049e1d0
long GetEmblemNumberofStageClear(long chara, long stage, long level)
{
	long local_10 = 0;
	long local_8g;
	unsigned short local_cj;

	if (stage == 0)
	{
		local_10 = 100;
		local_10 += level * 5;
	}
	else if (stage <= 14)
	{
		for (local_8g = 0; local_8g < chara + 1; local_8g++)
		{
			if (chara == local_8g)
			{
				local_cj = 0xffff >> (15 - stage);
				local_cj &= em_stage_table[local_8g];
			}
			else
			{
				local_cj = em_stage_table[local_8g];
			}
			while (local_cj)
			{
				if (local_cj & 1)
				{
					local_10++;
				}
				local_cj = local_cj >> 1;
			}
		}
		local_10--;
		local_10 += level * 32;
	}
	else if (stage > 0x22 && stage <= 0x26)
	{
		local_10 = stage + 0x3d;
		local_10 += level * 5;
	}
	else if (stage == 0x27 || stage == 0x28 || stage == 0x29)
	{
		local_10 = 0x6a;
		local_10 += level;
	}
	return local_10;
}

// FUNCTION: SADX 0x0049e2f0
void GetEmblemofEnding(struct SAVE_DATA *psd, long chara)
{
	GetEmblem(psd, FUN_0049e1a0(chara));
}

// FUNCTION: SADX 0x0049e310
long CheckEmblemofEnding(struct SAVE_DATA *psd, long chara)
{
	return FUN_0049d410((int)psd, FUN_0049e1a0(chara));
}

// FUNCTION: SADX 0x0049e330
long CheckEmblemofStageClear(struct SAVE_DATA *psd, long chara, long stage, long level)
{
	if (!DAT_05bb00a9)
	{
		return FUN_0049d410((int)psd, GetEmblemNumberofStageClear(chara, stage, level));
	}
	else
	{
		return 1 << FUN_0049f2a0(stage, level) & DAT_05cccf84;
	}
}

// FUNCTION: SADX 0x0049e830
void dispEmblem(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_emblem);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y)
	{
		njRotateY(0, local_8->ang.y);
	}
	late_DrawObjectMesh((struct obj *)local_8->counter.ptr, 0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0049e8b0
void FUN_0049e8b0(struct task *param_1)
{
	FreeTask(param_1);
}

// FUNCTION: SADX 0x0049e8d0
struct task *FUN_0049e8d0(struct NJS_POINT3 *param_1)
{
	struct task *local_8 = CreateElementalTask(2, 3, ObjectGetEmblem);

	if (local_8)
	{
		local_8->twp->mode = 0;
		local_8->twp->pos.x = param_1->x;
		local_8->twp->pos.y = param_1->y;
		local_8->twp->pos.z = param_1->z;
		if (DAT_05baf368[2] & 1)
		{
			PadReadOff();
		}
		return local_8;
	}
	return 0;
}

// FUNCTION: SADX 0x0049e950
void ObjectGetEmblem(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	local_8->ang.x = 0;
	local_8->ang.z = 0;
	local_8->mode = 0;
	local_8->counter.f = 0.0f;
	local_8->wtimer = 0;
	local_8->value.l = 0;
	local_8->timer.f = 0.0f;
	local_8->scl.x = 1.0f;
	if (DAT_05baf368[2] & 1)
	{
		PadReadOff();
	}
	*(float *)(emblem_num + 0xc) = ScreenRaitoX * 320.0;
	*(float *)(emblem_num + 0x10) = ScreenRaitoY * 370.0;
	*(float *)(emblem_num + 0x18) = ScreenRaitoX * 2.5;
	tp->exec = Exec;
	tp->disp = Disp;
}

// FUNCTION: SADX 0x0049ea10
void Exec(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	float local_10m;
	float local_cj;
	float local_18;
	float local_14;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (DAT_05baf368[2] & 1)
	{
		PadReadOff();
	}
	switch (local_8g->mode)
	{
	case 0:
		local_8g->mode = 1;
		local_8g->wtimer = 0;
		local_8g->value.l = FUN_0049e130((struct SAVE_DATA *)&DAT_05ccca18);
		dsPlay_oneshot(12, 0, 0, 0);
		break;
	case 1:
		local_8g->wtimer++;
		if (local_8g->wtimer > 0x2d)
		{
			local_8g->wtimer = 0;
			local_8g->mode = 2;
		}
		local_10m = DAT_05b42a7c->pos.x - local_8g->pos.x;
		local_cj = DAT_05b42a7c->pos.z - local_8g->pos.z;
		local_8g->ang.y = (long)(atan2((double)local_10m, (double)local_cj) * 65536.0 / 6.283184);
		*(long *)(emblem_num + 8) = local_8g->value.l;
		FUN_0055de60((struct _SC_NUMBERS *)emblem_num);
		break;
	case 2:
		local_8g->wtimer++;
		if (local_8g->wtimer == 12)
		{
			local_8g->wtimer = 0;
			*(long *)(emblem_num + 0x1c) = -1;
		}
		else if (local_8g->wtimer == 6)
		{
			*(long *)(emblem_num + 0x1c) = 0x3fffffff;
		}
		FUN_0055de60((struct _SC_NUMBERS *)emblem_num);
		local_8g->counter.f -= 0.02f;
		if (local_8g->counter.f <= -1.0)
		{
			local_8g->counter.f = -1.0f;
			local_8g->mode = 3;
			if (isCheckGGApper_Emblem())
			{
				InitGGMessage();
			}
			else
			{
				PadReadOn();
				FreeTask(tp);
			}
		}
		else
		{
			local_18 = DAT_05b42a7c->pos.x - local_8g->pos.x;
			local_14 = DAT_05b42a7c->pos.z - local_8g->pos.z;
			local_8g->ang.y = (long)(atan2((double)local_18, (double)local_14) * 65536.0 / 6.283184);
			local_8g->scl.x += 0.08f;
		}
		break;
	case 3:
		if (!isGGMessageEnable())
		{
			PadReadOn();
			FreeTask(tp);
		}
		break;
	}
	Disp(tp);
}

// FUNCTION: SADX 0x0049ec90
void Disp(struct task *tp)
{
	struct taskwk *local_cg = tp->twp;
	float local_8g = local_cg->scl.x;

	___njSetTexture(&texlist_emblem);
	SaveConstantAttr();
	OnConstantAttr(0, 0x100000);
	SetMaterial(local_cg->counter.f, 0.0f, 0.0f, 0.0f);
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	if (local_cg->ang.y)
	{
		njRotateY(0, local_cg->ang.y);
	}
	FUN_0067d2d0(0, local_8g, local_8g, local_8g);
	late_DrawObjectMesh(object_o_emblm_emblm, 0);
	njPopMatrix(1);
	ResetMaterial();
	LoadConstantAttr();
}

// FUNCTION: SADX 0x0049ed70
struct task *InitGetEmblem()
{
	struct task *local_8;

	if (DAT_05bb00a9)
	{
		return 0;
	}
	local_8 = CreateElementalTask(2, 6, dispGetEmblem);
	if (local_8)
	{
		ADX_Close();
		NeonuLoadTexture(&texlist_get_emblem);
		ADXTaskInit();
		*(short *)((char *)local_8->twp + 6) = 0;
		*((char *)local_8->twp) = 0;
		*(float *)((char *)local_8->twp + 0x20) = DAT_00956ba8;
		*(float *)((char *)local_8->twp + 0x24) = DAT_0095c8d0;
		*(void **)((char *)local_8 + 0x18) = destGetEmblem;
		return local_8;
	}
	return 0;
}

// FUNCTION: SADX 0x0049f280
void destGetEmblem(struct task *tp)
{
	late_ReleaseTexture(&texlist_get_emblem);
}
