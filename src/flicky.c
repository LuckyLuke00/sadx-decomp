#include "decls.h"
struct motionwk;
extern struct obj object_al_barria_barria[1];
extern struct NJS_TEXLIST texlist_al_barria;
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3);
void FUN_00618530(struct FlickyEff *param_1, struct FlickyEff *param_2, int param_3);
void Flicky_transformBaloon(struct Flicky *__this, struct taskwk *twp);
void FUN_0061a280(struct Flicky *param_1, struct taskwk *param_2, int param_3);
void FUN_0061a3c0(struct Flicky *param_1, struct taskwk *param_2, int param_3);
void FUN_0061a500(struct taskwk *param_1, int param_2, int param_3);
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3);
void FUN_006184e0(int param_1, char *param_2);
void FUN_0061a500(struct taskwk *param_1, int param_2, int param_3);
void FUN_0061a820(struct Flicky *param_1, struct taskwk *param_2);
void FUN_0061ea50(struct NJS_POINT3 *param_1, unsigned short param_2);
void FUN_0061a180(int param_1, struct taskwk *param_2, struct task *param_3);
void FUN_0061a590(int param_1, struct taskwk *param_2);
void FUN_004ff320(int param_1);
struct FlickyEff;

// STUB: SADX 0x00617a00
struct taskwk *Flicky_Create(float xpos, float ypos, float zpos, void (*FlickyXXXX_New)(struct task *))
{
	return (struct taskwk *)0;
}

// FUNCTION: SADX 0x00617ae0
struct taskwk *Flicky_CreateInStayBaloon(float xpos, float ypos, float zpos, void (*FlickyXXXX_New)(struct task *))
{
	struct taskwk *local_8;

	local_8 = Flicky_Create(xpos, ypos, zpos, FlickyXXXX_New);
	if (local_8 != NULL)
	{
		local_8->wtimer |= 0x5000;
	}
	return local_8;
}

// FUNCTION: SADX 0x00617b30
void FlickyGoma_New(struct task *tp)
{
	Flicky_New(tp, 0);
}

// FUNCTION: SADX 0x00617b50
void FlickyPeng_New(struct task *tp)
{
	Flicky_New(tp, 1);
}

// FUNCTION: SADX 0x00617b70
void FlickySwal_New(struct task *tp)
{
	Flicky_New(tp, 4);
}

// FUNCTION: SADX 0x00617b90
void FlickyPeac_New(struct task *tp)
{
	Flicky_New(tp, 3);
}

// FUNCTION: SADX 0x00617bb0
void FlickyParr_New(struct task *tp)
{
	Flicky_New(tp, 5);
}

// FUNCTION: SADX 0x00617bd0
void FlickyKoal_New(struct task *tp)
{
	Flicky_New(tp, 0xd);
}

// FUNCTION: SADX 0x00617bf0
void FlickyWara_New(struct task *tp)
{
	Flicky_New(tp, 8);
}

// FUNCTION: SADX 0x00617c10
void FlickyDeer_New(struct task *tp)
{
	Flicky_New(tp, 6);
}

// FUNCTION: SADX 0x00617c30
void FlickyBany_New(struct task *tp)
{
	Flicky_New(tp, 7);
}

// FUNCTION: SADX 0x00617c50
void FlickyMogu_New(struct task *tp)
{
	Flicky_New(tp, 0xc);
}

// FUNCTION: SADX 0x00617c70
void FlickyElep_New(struct task *tp)
{
	Flicky_New(tp, 0xb);
}

// FUNCTION: SADX 0x00617c90
void FlickyLion_New(struct task *tp)
{
	Flicky_New(tp, 0xa);
}

// FUNCTION: SADX 0x00617cb0
void FlickyGori_New(struct task *tp)
{
	Flicky_New(tp, 9);
}

// FUNCTION: SADX 0x00617cd0
void FlickySkun_New(struct task *tp)
{
	Flicky_New(tp, 0xe);
}

// FUNCTION: SADX 0x00617cf0
void FlickyRako_New(struct task *tp)
{
	Flicky_New(tp, 2);
}

// STUB: SADX 0x00617d10
void Flicky_New(struct task *tp, int id)
{
}

// STUB: SADX 0x00617e60
void FUN_00617e60(struct task *param_1)
{
}

// FUNCTION: SADX 0x00617f00
void Flicky_executor(struct task *tp)
{
	struct taskwk *local_cg;
	int local_8g;

	local_cg = tp->twp;
	local_8g = local_cg->value.l;
	FUN_0061a180(local_8g, local_cg, tp);
	FUN_0061a590(local_8g, local_cg);
}

// FUNCTION: SADX 0x00617f40
void Flicky_displayer(struct task *tp)
{
	struct taskwk *local_cg;
	int local_8g;
	local_cg = tp->twp;
	local_8g = local_cg->value.l;
	FUN_0061a590(local_8g, local_cg);
}

// FUNCTION: SADX 0x00617f70
void Flicky_destructor(struct task *tp)
{
	struct taskwk *local_cg;
	void *local_8g;

	local_cg = tp->twp;
	local_8g = (void *)local_cg->value.l;
	if (local_8g != 0)
	{
		if ((local_cg->wtimer & 0x2000) != 0)
		{
			Free(*(void **)((char *)local_8g + 0x68));
		}
		if (*(void **)((char *)local_8g + 0x64) != 0)
		{
			(*(void (**)(struct task *))((char *)local_8g + 0x64))(tp);
		}
		Free(local_8g);
	}
	FreeTask(tp);
}

// STUB: SADX 0x006183a0
void Flicky_exe(struct Flicky *__this, struct taskwk *twp, struct task *tp)
{
}

// FUNCTION: SADX 0x006184e0
void FUN_006184e0(int param_1, char *param_2)
{
	switch (*param_2)
	{
	case 0:
		if ((*(unsigned short *)(param_2 + 6) & 0x100) != 0)
		{
			if ((*(unsigned short *)(param_2 + 6) & 0x40) == 0)
			{
				*param_2 = 2;
			}
		}
		else
		{
			if (*(short *)(param_2 + 0xc) > 600)
			{
				*param_2 = 1;
			}
		}
		break;
	}
}

// FUNCTION: SADX 0x00618530
void FUN_00618530(struct FlickyEff *param_1, struct FlickyEff *param_2, int param_3)
{
	if (*(short *)((char *)param_2 + 0xc) > 0x1e)
	{
		if ((*(unsigned short *)((char *)*(int *)((char *)param_2 + 0x38) + 4) & 1) != 0)
		{
			if (*(unsigned short *)((char *)*(int *)((char *)*(int *)((char *)param_2 + 0x38) + 0xa4)) == 0)
			{
				dsPlay_oneshot(0x1c, 0, 0, 0);
				if ((*(unsigned short *)((char *)param_2 + 6) & 0x40) != 0)
				{
					FUN_0061ea50((struct NJS_POINT3 *)((char *)param_2 + 0x20), *(unsigned short *)((char *)*(int *)((char *)param_1 + 0x68)));
				}
				FlickyEff_Particle_New((struct NJS_POINT3 *)((char *)param_2 + 0x20), *(unsigned short *)((char *)*(int *)((char *)param_1 + 0x68)), *(unsigned short *)((char *)param_2 + 6) & 8);
				if (*(unsigned char *)param_1 < 0xf)
				{
					FUN_004ff320(*(unsigned char *)param_1);
				}
				*(unsigned short *)((char *)param_2 + 6) = *(unsigned short *)((char *)param_2 + 6) | 0x8000;
			}
			else
			{
				if ((*(unsigned short *)((char *)*(int *)((char *)param_2 + 0x38) + 4) & 4) != 0)
				{
					BaloonScale_force((struct NJS_POINT3 *)((char *)param_1 + 0x20), 1);
				}
				else
				{
					BaloonScale_force((struct NJS_POINT3 *)((char *)param_1 + 0x20), 6);
				}
			}
		}
	}
}

// FUNCTION: SADX 0x00618630
void Flicky_transformBaloon(struct Flicky *__this, struct taskwk *twp)
{
	if ((twp->wtimer & 0x4000) == 0)
	{
		if (twp->timer.w[0] == 0xb4)
		{
			twp->wtimer &= 0xffffffbf;
			twp->wtimer |= 0x80;
			FUN_0061ea50((struct NJS_POINT3 *)((char *)twp + 0x20), __this->flickydata->color);
		}
		if (twp->timer.w[0] == 0xb5)
		{
			twp->wtimer &= 0xffffff7f;
		}
	}
	if ((twp->wtimer & 0x40) != 0)
	{
		FUN_0061a820(__this, twp);
	}
}

// STUB: SADX 0x00618db0
void Flicky_moveStalk(struct Flicky *__this, struct taskwk *twp)
{
}

// STUB: SADX 0x00618f70
void Flicky_moveHop(struct Flicky *__this, struct taskwk *twp)
{
}

// STUB: SADX 0x00619020
int Flicky_moveCmnOnTheFloor(struct Flicky *__this, struct taskwk *twp, struct NJS_POINT3 *target)
{
	return (int)0;
}

// STUB: SADX 0x00619150
void Flicky_moveStep(struct Flicky *__this, struct taskwk *twp)
{
}

// STUB: SADX 0x0061a180
void FUN_0061a180(int param_1, struct taskwk *param_2, struct task *param_3)
{
}

// FUNCTION: SADX 0x0061a280
void FUN_0061a280(struct Flicky *param_1, struct taskwk *param_2, int param_3)
{
	struct motionwk *local_8g;
	float local_cg;

	local_8g = *(struct motionwk **)(param_3 + 0x24);
	local_8g->spd.y -= 0.05000000074505806;
	param_2->pos.x += local_8g->spd.x;
	param_2->pos.y += local_8g->spd.y;
	param_2->pos.z += local_8g->spd.z;
	param_2->ang.x = 0;
	param_2->ang.z = 0;
	local_cg = Shadow(param_2, 0.3499999940395355);
	param_2->pos.y -= 1.0;
	if ((param_2->pos.y - 2.0) < local_cg)
	{
		param_2->pos.y = local_cg + 2.0;
		if (local_8g->spd.y < 0.0)
		{
			local_8g->spd.y *= -0.6000000238418579;
		}
		local_8g->spd.x *= 0.699999988079071;
		local_8g->spd.z *= 0.699999988079071;
	}
	if ((param_2->flag & 0x1000) != 0)
	{
		param_2->mode = 2;
		param_2->wtimer = 0;
	}
	else
	{
		EntryColliList(param_2);
	}
}

// FUNCTION: SADX 0x0061a3c0
void FUN_0061a3c0(struct Flicky *param_1, struct taskwk *param_2, int param_3)
{
	struct taskwk *local_8g;
	float local_cg;

	local_8g = (struct taskwk *)*(int *)((char *)param_3 + 0x24);
	*(float *)((char *)local_8g + 8) -= 0.05000000074505806f;
	*(float *)((char *)param_2 + 0x20) += *(float *)((char *)local_8g + 4);
	*(float *)((char *)param_2 + 0x24) += *(float *)((char *)local_8g + 8);
	*(float *)((char *)param_2 + 0x28) += *(float *)((char *)local_8g + 0xc);
	*(int *)((char *)param_2 + 0x14) = 0;
	*(int *)((char *)param_2 + 0x1c) = 0;
	local_cg = Shadow(param_2, 0.3499999940395355f);
	if (*(float *)((char *)param_2 + 0x24) - 2.0f < local_cg)
	{
		*(float *)((char *)param_2 + 0x24) = local_cg + 2.0f;
		if (*(float *)((char *)local_8g + 8) < 0.0f)
		{
			*(float *)((char *)local_8g + 8) *= -0.6000000238418579f;
		}
		*(float *)((char *)local_8g + 4) *= 0.699999988079071f;
		*(float *)((char *)local_8g + 0xc) *= 0.699999988079071f;
	}
	if (param_2->wtimer++ > 0xc8)
	{
		param_2->mode = 0;
		param_2->wtimer = 0;
	}
	EntryColliList(param_2);
}

// STUB: SADX 0x0061a500
void FUN_0061a500(struct taskwk *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0061a590
void FUN_0061a590(int param_1, struct taskwk *param_2)
{
}

// STUB: SADX 0x0061a600
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3)
{
}

// FUNCTION: SADX 0x0061a6d0
void Flicky_dsp(struct Flicky *param_1, struct taskwk *param_2, long param_3)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((param_2->wtimer & 0x40) != 0)
	{
		___njSetTexture(&texlist_al_barria);
		njPushMatrix(0);
		FUN_0067d830(0, param_2->pos.x, (float)((double)param_2->pos.y + 1.2000000476837158), param_2->pos.z);
		FUN_0067d2d0(0, param_1->bscl.x, param_1->bscl.y, param_1->bscl.z);
		njRotateXYZ(0, param_1->targetangle, param_1->targetangle + param_3, param_3);
		late_DrawObject(&object_al_barria_barria[0], 4);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0061a7b0
void FUN_0061a7b0(struct taskwk *param_1, struct CCL_INFO *param_2)
{
}

// STUB: SADX 0x0061aa60
void BaloonScale_force(struct NJS_POINT3 *__this, int flag)
{
}
