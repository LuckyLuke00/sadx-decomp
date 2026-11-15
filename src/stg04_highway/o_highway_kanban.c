#include "decls.h"

// GLOBAL: SADX 0x03e71bbc
static struct CCL_INFO object_c_info[1];

void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x008207a0
void DrawA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
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
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	___dsDrawModel(model_knbn_02_kanban02_kanban02);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00820880
void ObjectHighwayKanbanA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->counter.ptr = object_knbn_01_kanban01_kanban01;
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, (struct CCL_INFO *)object_c_info, 1, 4);
				SET_COLLI_RANGE(var1->cwp, 10.0f);
			}
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = DrawA;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, 0);
			}
			DrawA(tp);
			break;
		}
	}
}

// FUNCTION: SADX 0x00820920
void ObjectHighwayKanbanB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->counter.ptr = object_knbn_02_kanban02_kanban02;
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, (struct CCL_INFO *)object_c_info, 1, 4);
				SET_COLLI_RANGE(var1->cwp, 10.0f);
			}
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = DrawB;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, 0);
			}
			DrawB(tp);
			break;
		}
	}
}
