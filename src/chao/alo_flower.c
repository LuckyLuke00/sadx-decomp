#include "decls.h"
extern int DAT_05b9d838;
extern struct cnkobj object_breedingflower00_breedingflower00[1];
extern struct cnkobj object_breedingflower01_breedingflower01[1];
extern struct NJS_TEXLIST texlist_al_object;

// FUNCTION: SADX 0x0046c210
void ALO_NestFlowerExecutor(struct task *tp)
{
	struct task *var1;
	struct taskwk *var2;
	struct taskwk *var3;
	float var4;

	var1 = tp->ptp;
	var2 = var1->twp;
	var3 = tp->twp;
	if (var2->ang.x != 0)
	{
		var4 = var3->scl.x + 0.10000000149011612;
		var3->scl.x = var4;
		if (var4 > 1.0f)
		{
			var3->scl.x = 1.0f;
		}
	}
	else
	{
		var4 = var3->scl.x - 0.029999999329447746;
		var3->scl.x = var4;
		if (var4 < 0.0f)
		{
			var3->scl.x = 0.0f;
			FreeTask(tp);
		}
	}
	tp->disp(tp);
}

// FUNCTION: SADX 0x0046c2a0
void ALO_NestFlowerDisplayer(struct task *tp)
{
	struct taskwk *var1;
	float fVar2;

	var1 = tp->twp;
	fVar2 = var1->scl.x * 0.800000011920929;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetTexture(&texlist_al_object);
	njPushMatrixEx();
	njTranslateEx(&var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	FUN_0067d2d0(0, fVar2, fVar2, fVar2);
	___beforecnk();
	if (var1->smode != 0)
	{
		chCnkDrawObject((struct cnkobj *)&object_breedingflower01_breedingflower01);
		___aftercnk();
		njPopMatrixEx();
	}
	else
	{
		chCnkDrawObject((struct cnkobj *)&object_breedingflower00_breedingflower00);
		___aftercnk();
		njPopMatrixEx();
	}
}

// STUB: SADX 0x0046c350
struct task *ALO_CreateNestFlower(struct task *pNestTask, struct NJS_POINT3 *pPos)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0046c570
struct task *ALO_CreateNest(struct task *pChaoTask)
{
	struct task *var1;
	struct taskwk *var2;
	struct taskwk *var3;

	var1 = CreateChildTask(2, ALO_NestExecutor, pChaoTask);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var3 = pChaoTask->twp;
		var2->pos = var3->pos;
		*(int *)((char *)pChaoTask->twp + 0x4c) = 1;
	}
	return var1;
}
