#include "decls.h"

// GLOBAL: SADX 0x03febac0
static struct CCL_INFO colliInfo[1];

static void _exec(struct task *pTask);
static void disp(struct task *pTask);
extern "C" double atan2(double v, double u);
extern int DAT_060cf238;
static void dest(struct task *pTask);

// STUB: SADX 0x00837a10
static void disp(struct task *pTask)
{
}

// FUNCTION: SADX 0x00837bc0
static void dest(struct task *pTask)
{
	int *local_8 = (int *)pTask->awp;
	if (local_8[5] == 0)
	{
		local_8[5] = 1;
		if (DAT_060cf238 > 0)
		{
			DAT_060cf238--;
		}
	}
}

// STUB: SADX 0x00837bf0
static void _exec(struct task *pTask)
{
}

// FUNCTION: SADX 0x00837db0
void EnemyMountainTgtMissile(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, struct colliwk *pIgnoreColliWk)
{
	struct task *local_8 = CreateElementalTask(2, 3, _exec);
	struct taskwk *local_c;
	float *local_10;
	if (local_8)
	{
		local_c = local_8->twp;
		CCL_Init(local_8, colliInfo, 1, 3);
		EnemyInitialize(local_8, local_c);
		local_10 = (float *)MAlloc(0x24);
		local_8->awp = (struct anywk *)local_10;
		local_c->pos = *pos;
		local_c->ang.y = (long)(atan2((double)vec->z, (double)vec->x) * 65536.0 / -6.283184);
		local_10[0] = local_10[1] = local_10[2] = 0.0f;
		((int *)local_10)[3] = 0x1f4;
		((int *)local_10)[5] = 0;
		((int *)local_10)[6] = 0;
		local_10[7] = -9999.0f;
		((struct colliwk **)local_10)[8] = pIgnoreColliWk;
		DAT_060cf238++;
		local_8->exec = _exec;
		local_8->disp = disp;
		local_8->dest = dest;
	}
}
