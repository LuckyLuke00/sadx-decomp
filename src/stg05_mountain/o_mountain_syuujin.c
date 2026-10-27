#include "decls.h"
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
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		njScaleV((float *)0, &var1->scl);
		late_ActionClipMesh((struct NJS_ACTION *)var1->counter.ptr, *(float *)((char *)var1 + 0xc), 4, FUN_004a1e90((float *)&var1->scl));
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0082f310
void Object_Mountain_Syuujin_Move_B(struct task *tp)
{
}

// FUNCTION: SADX 0x0082f390
void Object_Mountain_Syuujin_Move_R(struct task *tp)
{
	float var1;
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var2 = tp->twp;
		var1 = (float)(*(int *)((char *)var2 + 0x1c) * 0.1);
		var2->timer.f = var1 + var2->timer.f;
		if (var2->timer.f > 29.0)
		{
			var2->timer.f = 0.0;
		}
		var2->wtimer += 0x570;
		*(float *)((char *)var2 + 0x30) = njSin(var2->wtimer) * 0.10000000149011612 + 1.0;
		Object_Mountain_Syuujin_Display(tp);
	}
}

// STUB: SADX 0x0082f410
void Object_Mountain_Syuujin_Move_G(struct task *tp)
{
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
	*(struct NJS_TEXLIST **)(&var1->value.f) = &texlist_obj_mountain;
	*(struct NJS_ACTION **)((char *)var1 + 8) = &action_shu_jin02m_null1;
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
	*(int *)((char *)var1 + 0x10) = (int)&texlist_obj_mountain;
	*(int *)((char *)var1 + 8) = (int)&action_shu_jin02m_null1;
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
	*(int *)((char *)var1 + 0x10) = (int)&texlist_obj_mountain;
	*(int *)((char *)var1 + 8) = (int)&action_shu_jin02m_null1;
	if (FUN_004c39c0(tp))
	{
		tp->exec = Object_Mountain_Syuujin_Display;
		return;
	}
	tp->disp = Object_Mountain_Syuujin_Display;
	tp->exec = Object_Mountain_Syuujin_Move_G;
}
