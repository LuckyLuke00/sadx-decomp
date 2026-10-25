#include "decls.h"
static void Draw(struct task *tp);
extern struct obj object_neon4_neon_d_neon_d[1];
extern struct NJS_TEXLIST texlist_neon4;
extern struct obj object_neon3_neon_c_neon_c[1];
extern struct NJS_TEXLIST texlist_neon3;
extern struct obj object_neon2_neon_b_neon_b[1];
extern struct NJS_TEXLIST texlist_neon2;
extern struct obj object_neon1_neon_a_neon_a[1];
extern struct NJS_TEXLIST texlist_neon1;

#pragma optimize("", off)
// STUB: SADX 0x00820a80
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00820c90
void ObjectHighwayNeon01(struct task *tp)
{
	struct taskwk *var1;
	long var2;

	var1 = tp->twp;
	var2 = CheckRangeOut(tp);
	if (var2 == 0)
	{
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		tp->exec = ObjectHighwayNeonRegular;
		var1->counter.l = (long)object_neon1_neon_a_neon_a;
		var1->value.l = (long)&texlist_neon1;
		var1->btimer = (unsigned char)var2;
	}
}

// STUB: SADX 0x00820cd0
void ObjectHighwayNeon02(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->disp = Draw;
	tp->exec = ObjectHighwayNeonRegular;
	*(struct obj **)&var1->counter.l = &object_neon2_neon_b_neon_b[0];
	*(struct NJS_TEXLIST **)&var1->value.l = &texlist_neon2;
	var1->btimer = 1;
}

// FUNCTION: SADX 0x00820d10
void ObjectHighwayNeon03(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		tp->exec = ObjectHighwayNeonRegular;
		var1->counter.ptr = object_neon3_neon_c_neon_c;
		var1->value.ptr = &texlist_neon3;
		var1->btimer = 2;
	}
}

// FUNCTION: SADX 0x00820d50
void ObjectHighwayNeon04(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		tp->exec = ObjectHighwayNeonRegular;
		var1->counter.ptr = object_neon4_neon_d_neon_d;
		var1->value.ptr = &texlist_neon4;
		var1->btimer = 3;
	}
}
