#include "decls.h"
static void Object_Mountain_Syuujin_Move_G(struct task *tp);
extern struct NJS_TEXLIST texlist_obj_mountain;
extern struct NJS_ACTION action_shu_jin02m_null1;
int FUN_004c39c0(...);
void Object_Mountain_Syuujin_Display(struct task *tp);
void Object_Mountain_Syuujin_Move_B(struct task *tp);

// FUNCTION: SADX 0x0082f270
void Object_Mountain_Syuujin_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		njScaleV(NULL, &var1->scl);
		late_ActionClipMesh((struct NJS_ACTION *)var1->counter.ptr, var1->timer.f, 4, FUN_004a1e90((float *)&var1->scl));
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0082f310
void Object_Mountain_Syuujin_Move_B(struct task *tp)
{
	float var1;
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var2 = tp->twp;
		var1 = (float)(var2->ang.z * 0.1);
		var2->timer.f = var1 + var2->timer.f;
		if (var2->timer.f > 29.0)
		{
			var2->timer.f = 0.0;
		}
		var2->wtimer += 0x570;
		var2->scl.x = njSin(var2->wtimer) * 0.10000000149011612 + 1.0;
		Object_Mountain_Syuujin_Display(tp);
	}
}

// FUNCTION: SADX 0x0082f390
void Object_Mountain_Syuujin_Move_R(struct task *tp)
{
	float var1;
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var2 = tp->twp;
		var1 = (float)(var2->ang.z * 0.1);
		var2->timer.f = var1 + var2->timer.f;
		if (var2->timer.f > 29.0)
		{
			var2->timer.f = 0.0;
		}
		var2->wtimer += 0x570;
		var2->scl.y = njSin(var2->wtimer) * 0.10000000149011612 + 1.0;
		Object_Mountain_Syuujin_Display(tp);
	}
}

// FUNCTION: SADX 0x0082f410
static void Object_Mountain_Syuujin_Move_G(struct task *tp)
{
	float var1;
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var2 = tp->twp;
		var1 = (float)(var2->ang.z * 0.1);
		var2->timer.f = var1 + var2->timer.f;
		if (var2->timer.f > 29.0)
		{
			var2->timer.f = 0.0;
		}
		Object_Mountain_Syuujin_Display(tp);
	}
}

// FUNCTION: SADX 0x0082f470
void Object_Mountain_Syuujin_B(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->scl.x == 0.0f)
	{
		var1->scl.x = 1.0f;
	}
	if (var1->scl.y == 0.0f)
	{
		var1->scl.y = 1.0f;
	}
	if (var1->scl.z == 0.0f)
	{
		var1->scl.z = 1.0f;
	}
	var1->value.ptr = &texlist_obj_mountain;
	var1->counter.ptr = &action_shu_jin02m_null1;
	if (FUN_004c39c0(tp))
	{
		tp->exec = Object_Mountain_Syuujin_Display;
		return;
	}
	tp->disp = Object_Mountain_Syuujin_Display;
	tp->exec = Object_Mountain_Syuujin_Move_B;
}

// FUNCTION: SADX 0x0082f4f0
void Object_Mountain_Syuujin_R(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->scl.x == 0.0f)
	{
		var1->scl.x = 1.0f;
	}
	if (var1->scl.y == 0.0f)
	{
		var1->scl.y = 1.0f;
	}
	if (var1->scl.z == 0.0f)
	{
		var1->scl.z = 1.0f;
	}
	var1->value.l = (int)&texlist_obj_mountain;
	var1->counter.l = (int)&action_shu_jin02m_null1;
	if (FUN_004c39c0(tp))
	{
		tp->exec = Object_Mountain_Syuujin_Display;
		return;
	}
	tp->disp = Object_Mountain_Syuujin_Display;
	tp->exec = Object_Mountain_Syuujin_Move_R;
}

// FUNCTION: SADX 0x0082f570
void Object_Mountain_Syuujin_G(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->scl.x == 0.0f)
	{
		var1->scl.x = 1.0f;
	}
	if (var1->scl.y == 0.0f)
	{
		var1->scl.y = 1.0f;
	}
	if (var1->scl.z == 0.0f)
	{
		var1->scl.z = 1.0f;
	}
	var1->value.l = (int)&texlist_obj_mountain;
	var1->counter.l = (int)&action_shu_jin02m_null1;
	if (FUN_004c39c0(tp))
	{
		tp->exec = Object_Mountain_Syuujin_Display;
		return;
	}
	tp->disp = Object_Mountain_Syuujin_Display;
	tp->exec = Object_Mountain_Syuujin_Move_G;
}
