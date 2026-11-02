#include "decls.h"
extern long (*ALBHV_SToyFunc[32])(struct task *);
extern "C" int rand(void);
void BookDisplayer(struct task *tp);

// STUB: SADX 0x004543a0
void ALO_ShabonDisplayer(struct task *tp)
{
}

// STUB: SADX 0x00454480
void ALO_ShabonExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x00454540
void ALO_ShabonDestructor(struct task *tp)
{
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}

// STUB: SADX 0x00454560
struct task *ALO_CreateShabon(struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVelo)
{
	return (struct task *)0;
}

// STUB: SADX 0x004548a0
long ALBHV_Houki(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00454970
long ALBHV_Garagara(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00454a40
long ALBHV_Hanabi(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00454b10
void BookExecutor(struct task *tp)
{
	struct taskwk *var1;
	float var2;

	var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var2 = var1->scl.y + 0.10000000149011612f;
		var1->scl.y = var2;
		if (var2 > 1.0f)
		{
			var1->scl.y = 1.0f;
			var1->mode = 1;
		}
		break;
	case 1:
		var1->scl.x = 15.0f;
		break;
	case 2:
		var2 = var1->scl.x + 0.15000000596046448f;
		var1->scl.x = var2;
		if (var2 > 23.0f)
		{
			var1->scl.x = 23.0f;
			var1->mode = 1;
		}
		break;
	case 4:
		var2 = var1->scl.y - 0.10000000149011612f;
		var1->scl.y = var2;
		if (var2 < 0.0f)
		{
			var1->scl.y = 0.0f;
			FreeTask(tp);
		}
		break;
	}
	tp->disp(tp);
}

// STUB: SADX 0x00454c10
void BookDisplayer(struct task *tp)
{
}

// STUB: SADX 0x00455110
long ALBHV_Doll(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004551f0
long ALBHV_Hopping(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x004552c0
long AL_DecideBehaviorSToy(struct task *tp)
{
	long BhvList[32];
	int var1;
	int local_94;
	int var2;
	float var3;
	int var4;

	local_94 = 0;
	for (var1 = 0; var1 < 0xc; var1++)
	{
		if (AL_KW_IsSToyFlagOn(tp, var1) != 0 && ALBHV_SToyFunc[var1] != 0)
		{
			BhvList[local_94] = var1;
			local_94++;
		}
	}
	if (local_94 > 0)
	{
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		var4 = (unsigned int)(var3 * ((float)local_94 - 9.999999747378752e-05));
		AL_SetBehavior(tp, ALBHV_SToyFunc[BhvList[var4]]);
		return 1;
	}
	return 0;
}
