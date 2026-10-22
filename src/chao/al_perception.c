#include "decls.h"

// FUNCTION: SADX 0x00463330
int FUN_00463330(struct task *param_1)
{
	int var1;
	int var2;

	var1 = *(int *)((char *)param_1 + 0x20);
	var2 = 0;
	if (*(int *)((char *)var1 + 0x7f8) != 0)
	{
		if (*(short *)((char *)var1 + 0x808) >= 0)
		{
			var2 = var1 + 0x80c + *(short *)((char *)var1 + 0x808) * 0x1c;
		}
	}
	return var2;
}

// STUB: SADX 0x00463370
struct task *AL_GetFoundPlayerTask(struct task *tp)
{
	return (struct task *)0;
}

// STUB: SADX 0x004633a0
int FUN_004633a0(struct task *tp)
{
	return (int)0;
}

// STUB: SADX 0x004633e0
struct task *AL_GetFoundFruitTask(struct task *tp)
{
	return (struct task *)0;
}

// STUB: SADX 0x00463410
struct al_perception_link *AL_GetFoundTree(struct task *tp)
{
	return (struct al_perception_link *)0;
}

// STUB: SADX 0x00463450
int FUN_00463450(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x00463490
struct task *AL_GetFoundToyTask(struct task *tp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x004634c0
void AL_PerceptionInit(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	AL_ClearPerceptionAll(tp);
	*(float *)((char *)var1 + 0x7e0) = 50.0f;
	*(float *)((char *)var1 + 0x7ec) = 40.0f;
	*(int *)((char *)var1 + 0x7e4) = 0x4e38;
	*(int *)((char *)var1 + 0x7e8) = 0x271c;
	*(float *)((char *)var1 + 0x7f0) = 40.0f;
}
