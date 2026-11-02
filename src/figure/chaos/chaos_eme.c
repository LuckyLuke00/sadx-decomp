#include "decls.h"
void ChaosEmerald(struct task *tp);
extern int DAT_060dfe78[7];

// FUNCTION: SADX 0x008c8a40
void InitChaosEmerald()
{
	int local_8;
	for (local_8 = 0; local_8 < 7; local_8 = local_8 + 1)
	{
		DAT_060dfe78[local_8] = 0;
	}
}

// FUNCTION: SADX 0x008c8a70
struct task *SetDisplayChaosEmerald(struct NJS_POINT3 *pos, int color)
{
	struct task *local_8g;
	struct taskwk *local_10;
	struct anywk *local_cj;

	if (DAT_060dfe78[color] != 0)
		DestroyTask((struct task *)DAT_060dfe78[color]);
	local_8g = CreateElementalTask(3, 2, ChaosEmerald);
	if (local_8g != 0)
	{
		local_10 = local_8g->twp;
		local_8g->awp = (struct anywk *)MAlloc(0x18);
		local_10->pos = *pos;
		local_10->value.b[0] = (signed char)(color * 3);
		local_cj = local_8g->awp;
		*(void **)((char *)local_cj + 0x14) = (void *)pos;
		DAT_060dfe78[color] = (int)local_8g;
	}
	return local_8g;
}

// STUB: SADX 0x008c8f40
void ChaosEmeraldDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x008c9030
void ReturnChaosEmerald()
{
	int local_8g;
	int local_cg;

	for (local_8g = 0; local_8g < 7; local_8g++)
	{
		local_cg = DAT_060dfe78[local_8g];
		if (local_cg != 0)
		{
			if (*(int *)(local_cg + 0x20) == 0)
			{
				continue;
			}
			if (((char *)*(int *)(local_cg + 0x20))[0] != 4)
			{
				((char *)*(int *)(local_cg + 0x20))[0] = 3;
			}
		}
	}
}
