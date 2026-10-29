#include "decls.h"
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3);
void FUN_00618530(struct FlickyEff *param_1, struct FlickyEff *param_2, int param_3);
void Flicky_transformBaloon(struct Flicky *__this, struct taskwk *twp);
void FUN_0061a280(struct Flicky *param_1, struct taskwk *param_2, int param_3);
void FUN_0061a3c0(struct Flicky *param_1, struct taskwk *param_2, int param_3);
void FUN_0061a500(struct taskwk *param_1, int param_2, int param_3);
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3);
void Flicky_dsp(struct Flicky *__this, struct taskwk *twp);
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

#pragma optimize("", off)
// STUB: SADX 0x00617d10
void Flicky_New(struct task *tp, int id)
{
}
#pragma optimize("", on)

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

#pragma optimize("", off)
// STUB: SADX 0x0061a180
void FUN_0061a180(int param_1, struct taskwk *param_2, struct task *param_3)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0061a280
void FUN_0061a280(struct Flicky *param_1, struct taskwk *param_2, int param_3)
{
}

// STUB: SADX 0x0061a3c0
void FUN_0061a3c0(struct Flicky *param_1, struct taskwk *param_2, int param_3)
{
}

// STUB: SADX 0x0061a500
void FUN_0061a500(struct taskwk *param_1, int param_2, int param_3)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0061a590
void FUN_0061a590(int param_1, struct taskwk *param_2)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0061a600
void FUN_0061a600(struct task *param_1, struct taskwk *param_2, unsigned short param_3)
{
}

// STUB: SADX 0x0061a6d0
void Flicky_dsp(struct Flicky *__this, struct taskwk *twp)
{
}

// STUB: SADX 0x0061a7b0
void FUN_0061a7b0(struct taskwk *param_1, struct CCL_INFO *param_2)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0061aa60
void BaloonScale_force(struct NJS_POINT3 *__this, int flag)
{
}
#pragma optimize("", on)
