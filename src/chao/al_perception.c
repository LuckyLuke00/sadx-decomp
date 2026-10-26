#include "decls.h"

// FUNCTION: SADX 0x004632f0
long AL_CalcPerceptionAll(struct task *tp)
{
	long var1;

	AL_ClearPerceptionAll(tp);
	var1 = AL_SearchPlayer(tp);
	var1 |= AL_SearchChao(tp);
	var1 |= AL_SearchFruit(tp);
	var1 |= AL_SearchTree(tp);
	var1 |= AL_SearchToy(tp);
	return var1;
}

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

// FUNCTION: SADX 0x00463370
struct task *AL_GetFoundPlayerTask(struct task *tp)
{
	if (FUN_00463330(tp) != 0)
	{
		return GetPlayerTaskPointer(0);
	}
	return 0;
}

// FUNCTION: SADX 0x004633a0
int FUN_004633a0(struct task *param_1)
{
	int var1;
	int var2;

	var1 = (int)param_1->twp;
	var2 = 0;
	if (*(int *)((char *)var1 + 0xf28) != 0)
	{
		if (*(short *)((char *)var1 + 0xf38) >= 0)
		{
			var2 = var1 + 0xf3c + *(short *)((char *)var1 + 0xf38) * 0x1c;
		}
	}
	return var2;
}

// FUNCTION: SADX 0x004633e0
struct task *AL_GetFoundFruitTask(struct task *tp)
{
	struct task *var1 = (struct task *)FUN_004633a0(tp);
	if (var1 != 0)
	{
		struct task *var2 = (struct task *)var1->dest;
		if (var2 != 0)
		{
			struct task *var3 = (struct task *)*(int *)((char *)var2 + 0x3c);
			if (var3 != 0)
			{
				return var3;
			}
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00463410
struct al_perception_link *AL_GetFoundTree(struct task *tp)
{
	struct al_perception_link *var1;
	struct al_perception_link *var2;

	var1 = (al_perception_link *)tp->twp;
	var2 = NULL;
	if (*(int *)((char *)var1 + 0x12c0) != 0)
	{
		if (*(short *)((char *)var1 + 0x12d0) >= 0)
		{
			var2 = (struct al_perception_link *)((char *)var1 + 0x12d4 + *(short *)((char *)var1 + 0x12d0) * 0x1c);
		}
	}
	return var2;
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
