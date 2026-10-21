#include "decls.h"
void FUN_0061a180(int param_1, struct taskwk *param_2, struct task *param_3);
void FUN_0061a590(int param_1, struct taskwk *param_2);

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

// FUNCTION: SADX 0x00617f00
void Flicky_executor(struct task *tp)
{
	struct taskwk *local_cg;
	int local_8g;

	local_cg = tp->twp;
	local_8g = *(int *)&local_cg->value;
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

// STUB: SADX 0x006184e0
void FUN_006184e0(int param_1, char *param_2)
{
}

// STUB: SADX 0x0061a590
void FUN_0061a590(int f, struct taskwk *twp)
{
}

// STUB: SADX 0x0061a7b0
void FUN_0061a7b0(struct taskwk *twp, struct CCL_INFO *info)
{
}
