#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x008207a0
void DrawA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (*(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsDrawModel(model_knbn_01_kanban01_kanban01);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00820810
void DrawB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (*(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsDrawModel(model_knbn_02_kanban02_kanban02);
	njPopMatrix(1);
}
