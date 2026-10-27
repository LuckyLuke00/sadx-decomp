#include "decls.h"
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

// STUB: SADX 0x008c8a70
struct task *SetDisplayChaosEmerald(struct NJS_POINT3 *pos, int color)
{
	return (struct task *)0;
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
