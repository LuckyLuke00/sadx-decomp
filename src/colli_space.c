#include "decls.h"
#include <math.h>
extern struct CCL_INFO cuberange_info[1];
extern struct CCL_INFO cube_info[1];
extern struct CCL_INFO cylinder_info[1];
extern struct CCL_INFO sphere_info[1];
extern long DAT_05b42598;

#define njRotateX(param_1, param_2) if ((param_2) != 0) njRotateX((param_1), (unsigned short)(param_2))
#define njRotateY(param_1, param_2) if ((param_2) != 0) njRotateY((param_1), (unsigned short)(param_2))

static void ColliSpaceEditMode(struct task *tp, unsigned short form);
static void ColliOttottoRangeEditMode(struct task *tp);
static long CS_CheckCollisionPlayer2NoWater(struct CCL_INFO *pinf, struct taskwk *ctwp);

// FUNCTION: SADX 0x0061cc20
void ColliSphere(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 0);
	}
	else
	{
		CheckRangeOut(tp);
		switch (local_8->mode)
		{
		case 0:
			CCL_Init(tp, &sphere_info[0], 1, 4);
			FUN_0061d220(local_8);
			local_8->mode = 1;
			break;
		case 1:
			EntryColliList(local_8);
			break;
		default:
			local_8->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061ccb0
static void ColliSpaceEditMode(struct task *tp, unsigned short form)
{
	struct NJS_POINT3 local_40h;
	struct NJS_POINT3 local_34h;
	struct NJS_POINT3 local_28z;
	long local_18o;
	struct taskwk *local_14s = tp->twp;
	float local_10l = local_14s->scl.x + 10.0;
	float local_ci = local_14s->scl.y + 10.0;
	float local_8g = local_14s->scl.z + 10.0;

	ResetMaterial();
	njPushMatrix(0);
	njTranslateV(0, &local_14s->pos);
	njRotateY(0, local_14s->ang.y);
	switch (form)
	{
	case 0:
		FUN_0067d2d0(0, local_10l * (double)0.1f, local_10l * (double)0.1f, local_10l * (double)0.1f);
		njEasyDrawObject(&object_sphere01);
		break;
	case 1:
		FUN_0067d2d0(0, local_10l * (double)0.1f, local_ci * (double)0.1f, local_10l * (double)0.1f);
		njEasyDrawObject(object_cylinder01);
		break;
	case 3:
		FUN_0067d2d0(0, local_10l * (double)0.2f, local_ci * (double)0.2f, local_8g * (double)0.2f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		break;
	case 8:
		njPushMatrix(0);
		FUN_0067d830(0, 0.0f, 0.0f, 10.0f);
		FUN_0067d2d0(0, 0.1f, 0.1f, 2.0f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		njPopMatrix(1);
		njPushMatrix(0);
		FUN_0067d830(0, 0.0f, 0.0f, 20.0f);
		njRotateX(0, 0x2000);
		FUN_0067d830(0, 0.0f, 0.0f, -3.0f);
		FUN_0067d2d0(0, 0.1f, 0.1f, 0.7f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		njPopMatrix(1);
		njPushMatrix(0);
		FUN_0067d830(0, 0.0f, 0.0f, 20.0f);
		njRotateX(0, 0xe000);
		FUN_0067d830(0, 0.0f, 0.0f, -3.0f);
		FUN_0067d2d0(0, 0.1f, 0.1f, 0.7f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		njPopMatrix(1);
		FUN_0067d2d0(0, local_10l * (double)0.2f, local_ci * (double)0.2f, 0.1f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		if (FUN_004c39c0(tp))
		{
			if (local_14s->btimer > 25)
				njPrintC(0x80008, "< WALL >");
			else
				njPrintC(0x80008, "<      >");
			if (local_14s->btimer++ > 50)
				local_14s->btimer = 0;
			njPrintC(0x110010, "->             ");
			njPrintC(0x110011, "-> ROT Y       ");
			njPrintC(0x110012, "->             ");
			njPrintC(0x110013, "-> YOKO        ");
			njPrintC(0x110014, "-> TATE        ");
			njPrintC(0x110015, "->             ");
		}
		break;
	case 10:
		local_28z.x = local_10l;
		local_28z.y = 0.0f;
		local_28z.z = 0.0f;
		for (local_18o = 0; local_18o < 32; local_18o++)
		{
			njPushMatrix(_nj_unit_matrix_);
			njRotateY(0, local_18o << 11);
			njCalcPoint(0, &local_28z, &local_34h);
			njPopMatrix(1);
			njPushMatrix(_nj_unit_matrix_);
			njRotateY(0, (local_18o + 1) << 11);
			njCalcPoint(0, &local_28z, &local_40h);
			njPopMatrix(1);
			DrawLineV(&local_34h, &local_40h);
		}
		break;
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0061d220
void FUN_0061d220(struct taskwk *param_1)
{
	struct CCL_INFO *local_8 = param_1->cwp->info;
	local_8->a = param_1->scl.x + 10.0;
	local_8->b = param_1->scl.y + 10.0;
	local_8->c = param_1->scl.z + 10.0;
	CalcColliRange(param_1->cwp);
}

// FUNCTION: SADX 0x0061d280
void ColliCylinder(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 1);
	}
	else
	{
		CheckRangeOut(tp);
		switch (local_8->mode)
		{
		case 0:
			CCL_Init(tp, &cylinder_info[0], 1, 4);
			FUN_0061d220(local_8);
			local_8->mode = 1;
			break;
		case 1:
			EntryColliList(local_8);
			break;
		default:
			local_8->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061d310
void ColliCube(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 3);
		return;
	}
	CheckRangeOut(tp);
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cube_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d3a0
void ColliWall(struct task *tp)
{
	// GLOBAL: SADX 0x026ba220
	static struct CCL_INFO wall_info[1] =
	{
		{ 0, 9, 0x77, 0xe0, 0, { 0.0f, 0.0f, 0.0f }, 40.0f, 30.0f, 10.0f, 0.0f, 0, 0, 0 }
	};
	struct taskwk *local_8 = tp->twp;
	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 8);
	}
	else
	{
		CheckRangeOut(tp);
		switch (local_8->mode)
		{
		case 0:
			CCL_Init(tp, &wall_info[0], 1, 8);
			FUN_0061d220(local_8);
			local_8->mode = 1;
			break;
		case 1:
			EntryColliList(local_8);
			break;
		default:
			local_8->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061d430
void ColliCircle(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 0xa);
		return;
	}
	CheckRangeOutWithR(tp, 9000000.0f);
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &circle_info[0], 1, 8);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d4d0
void ColliOttottoRange(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckRangeOut(tp) != 0)
		return;
	if (CheckEditMode() != 0)
	{
		ColliOttottoRangeEditMode(tp);
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cuberange_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		local_8->id = 0xc;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d570
static void ColliOttottoRangeEditMode(struct task *tp)
{
	struct taskwk *local_14s = tp->twp;
	float local_10l = local_14s->scl.x + 10.0;
	float local_ci = local_14s->scl.y + 10.0;
	float local_8g = local_14s->scl.z + 10.0;

	ResetMaterial();
	njPushMatrix(0);
	njTranslateV(0, &local_14s->pos);
	njRotateY(0, local_14s->ang.y);
	njPushMatrix(0);
	FUN_0067d2d0(0, local_10l * (double)0.2f, local_ci * (double)0.2f, local_8g * (double)0.2f);
	njEasyDrawObject(object_no_name_cuuube01_cuuube01);
	njPopMatrix(1);
	njPushMatrix(0);
	FUN_0067d830(0, 0.0f, 0.0f, 20.0f);
	njRotateX(0, 0x2000);
	FUN_0067d830(0, 0.0f, 0.0f, -3.0f);
	FUN_0067d2d0(0, 0.1f, 0.1f, 0.7f);
	njEasyDrawObject(object_no_name_cuuube01_cuuube01);
	njPopMatrix(1);
	njPushMatrix(0);
	FUN_0067d830(0, 0.0f, 0.0f, 20.0f);
	njRotateX(0, 0xe000);
	FUN_0067d830(0, 0.0f, 0.0f, -3.0f);
	FUN_0067d2d0(0, 0.1f, 0.1f, 0.7f);
	njEasyDrawObject(object_no_name_cuuube01_cuuube01);
	njPopMatrix(1);
	FUN_0067d2d0(0, local_10l * (double)0.2f, local_ci * (double)0.2f, 0.1f);
	njEasyDrawObject(object_no_name_cuuube01_cuuube01);
	if (FUN_004c39c0(tp))
	{
		if (local_14s->btimer > 25)
			njPrintC(0x80008, "< OTTOTTO >");
		else
			njPrintC(0x80008, "<      >");
		if (local_14s->btimer++ > 50)
			local_14s->btimer = 0;
		njPrintC(0x110010, "->             ");
		njPrintC(0x110011, "-> ROT Y       ");
		njPrintC(0x110012, "->             ");
		njPrintC(0x110013, "-> YOKO        ");
		njPrintC(0x110014, "-> TATE        ");
		njPrintC(0x110015, "-> O OKU3      ");
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0061d8b0
void ColliBigWaterJumpRange(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (CheckEditMode() != 0)
	{
		ColliSpaceEditMode(tp, 3);
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cuberange_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		local_8->id = 0xd;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d950
void ColliNoWaterRange(struct task *tp)
{
	struct colliwk *local_14s;
	struct taskwk *local_10l;
	long local_ci;
	struct taskwk *local_8g = tp->twp;

	if (CheckRangeOut(tp))
		return;
	if (CheckEditMode())
	{
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		if (local_8g->ang.z)
			njRotateZ(0, (unsigned short)local_8g->ang.z);
		njRotateY(0, local_8g->ang.y);
		njRotateX(0, local_8g->ang.x);
		FUN_0067d2d0(0, local_8g->scl.x * (double)0.2f, local_8g->scl.y * (double)0.2f, local_8g->scl.z * (double)0.2f);
		njEasyDrawObject(object_no_name_cuuube01_cuuube01);
		njPopMatrix(1);
	}
	else
	{
		switch (local_8g->mode)
		{
		case 0:
			local_8g->mode = 1;
			break;
		case 1:
			for (local_ci = 1; local_ci >= 0; local_ci--)
			{
				local_10l = DAT_05baf368[local_ci];
				if (!local_10l)
					continue;
				local_14s = local_10l->cwp;
				if (!local_14s)
					continue;
				if (CS_CheckCollisionPlayer2NoWater(local_14s->info, local_8g))
					GetPlayerWorkPointer((unsigned char)local_ci)->shadow.Attr_top &= 0xffbffffd;
			}
			if (DAT_05b42a7c)
			{
				camera_sphere_info[0].center = DAT_05b42a7c->pos;
				if (CS_CheckCollisionPlayer2NoWater(&camera_sphere_info[0], local_8g))
					DAT_05b42598 = 1;
			}
			break;
		default:
			local_8g->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061db50
static long CS_CheckCollisionPlayer2NoWater(struct CCL_INFO *pinf, struct taskwk *ctwp)
{
	struct NJS_POINT3 local_48h;
	float local_3cp;
	struct NJS_POINT3 local_38gj;
	float local_2cm;
	struct NJS_POINT3 local_28z;
	float local_18o;
	float local_14s;
	float local_10l;
	float local_ci;
	float local_8g;

	local_48h = pinf->center;
	local_28z = ctwp->pos;
	local_14s = njScalor(&ctwp->scl) + pinf->a;

	if (njSqrt((local_48h.x - local_28z.x) * (local_48h.x - local_28z.x) +
		(local_48h.y - local_28z.y) * (local_48h.y - local_28z.y) +
		(local_48h.z - local_28z.z) * (local_48h.z - local_28z.z)) > local_14s)
		return 0;
	local_38gj.x = local_48h.x - local_28z.x;
	local_38gj.y = local_48h.y - local_28z.y;
	local_38gj.z = local_48h.z - local_28z.z;
	njPushMatrixEx();
	njUnitMatrix(0);
	if (ctwp->ang.z)
		njRotateZ(0, (unsigned short)ctwp->ang.z);
	njRotateX(0, ctwp->ang.x);
	njRotateY(0, ctwp->ang.y);
	njInvertMatrix(0);
	njCalcPoint(0, &local_38gj, &local_38gj);
	njPopMatrix(1);
	local_14s = pinf->a;
	local_ci = local_38gj.x + local_14s;
	local_8g = local_38gj.y + local_14s;
	local_18o = local_38gj.z + local_14s;
	local_10l = fabs(ctwp->scl.x);
	local_3cp = fabs(ctwp->scl.y);
	local_2cm = fabs(ctwp->scl.z);
	if (local_ci <= local_10l && local_ci >= -local_10l &&
		local_8g <= local_3cp && local_8g >= -local_3cp &&
		local_18o <= local_2cm && local_18o >= -local_2cm)
		return 1;
	return 0;
}
