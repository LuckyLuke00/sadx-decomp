#include "decls.h"
void FUN_005e5770(struct task *param_1);
struct colliwk;
struct task;
void E102EnemyDest(struct task *tp);

// STUB: SADX 0x005d44b0
void SetEnemyDestractor(struct colliwk **list, int num)
{
}

// FUNCTION: SADX 0x005d4540
void E102EnemyDest(struct task *tp)
{
	struct motionwk *local_8g;
	void *local_cj;
	int local_10;

	local_8g = tp->mwp;
	if (local_8g != 0)
	{
		local_cj = *(void **)((char *)local_8g + 0x40);
		local_10 = 0;
		if ((*(unsigned short *)((char *)local_8g + 0x4e) & 0x1000) != 0)
		{
			if (local_cj != 0)
			{
				local_10 = *(int *)((char *)local_cj + 0x2c);
			}
			if (CheckEnemyAddTime(tp) != 0)
			{
				if (local_10 != 0)
				{
					E102AddRestTimeNew(*(struct task **)((char *)local_10 + 0x2c));
				}
				else
				{
					E102AddRestTimeNew(0);
				}
			}
		}
	}
	FUN_005e5770(tp);
	if (local_8g != 0 && *(void **)((char *)local_8g + 0x44) != 0)
	{
		(*(void (**)(struct task *))((char *)local_8g + 0x44))(tp);
	}
}

// STUB: SADX 0x005d45f0
struct task *SearchNotLockedEnemy(struct E102WK *ewk, struct colliwk **list, int num, float *dist2)
{
	return (struct task *)0;
}
