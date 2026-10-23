#include "decls.h"
extern struct NJS_TEXLIST texlist_obj_mountain;
extern struct NJS_ACTION action_shu_jin02m_null1;
int FUN_004c39c0(struct task *param_1);
void Object_Mountain_Syuujin_Display(struct task *tp);
void Object_Mountain_Syuujin_Move_B(struct task *tp);

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

// STUB: SADX 0x0082f570
void Object_Mountain_Syuujin_G(struct task *tp)
{
}
