#include "decls.h"

static void CollisionSceneChangerRegular(struct task *tp);

// FUNCTION: SADX 0x008e1c90
void CollisionSceneChanger(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	float local_cj;
	float local_10;
	float local_14q;
	// GLOBAL: SADX 0x04c7bda0
	static struct CCL_INFO object_c_info[1] =
	{
		{ 0, 3, 0xb0, 0, 0, { 0.0f, 0.0f, 0.0f }, 5.0f, 5.0f, 5.0f, 0.0f, 0, 0, 0 }
	};

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 6);
		local_cj = (local_8g->scl.x += 1.0) * 5.0;
		local_10 = (local_8g->scl.y += 1.0) * 5.0;
		local_14q = (local_8g->scl.z += 1.0) * 5.0;
		local_8g->cwp->info->a = local_cj;
		local_8g->cwp->info->b = local_10;
		local_8g->pos.y = local_10 + local_8g->pos.y;
		local_8g->cwp->info->c = local_14q;
		SET_COLLI_RANGE(local_8g->cwp, local_cj * local_cj + local_10 * local_10 + local_14q * local_14q);
	}
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = CollisionSceneChangerRegular;
}

// FUNCTION: SADX 0x008e1dc0
void CollisionSceneChangerRegular(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;

	if (CheckRangeOut(tp) != 0)
		return;
	if (FUN_004c39c0(tp) == 0)
	{
		if ((local_8g->cwp->flag & 1) != 0 && CheckPadReadMode() == 1)
		{
			DoSceneChange(*(int *)((char *)local_8g + 0x1c));
			FreeTask(tp);
			return;
		}
		else
		{
			EntryColliList(local_8g);
		}
	}
	else
	{
		njPrintC(0x110011, "-> ROTATION Y");
		njPrintC(0x110012, "-> STAGE & ENTRANCE & ACT");
		njPrintC(0x110013, "-> SCALE X");
		njPrintC(0x110014, "-> SCALE Y");
		njPrintC(0x110015, "-> SCALE Z");
		FUN_005b5aa0(0x110016, *(unsigned short *)((char *)local_8g + 0x1c));
		njPushMatrix(0);
		FUN_0067d830(0, local_8g->pos.x, (1.0f + local_8g->scl.y) * 5.0 + local_8g->pos.y, local_8g->pos.z);
		if (local_8g->ang.y != 0)
			njRotateY(0, (Uint16)local_8g->ang.y);
		FUN_0067d2d0(0, 1.0f + local_8g->scl.x, 1.0f + local_8g->scl.y, 1.0f + local_8g->scl.z);
		SetMaterial(0.1f, 1.0f, 0.8f, 0.2f);
		___dsDrawObject(&object_hakoirimusume[0]);
		njPopMatrix(1);
		ResetMaterial();
	}
}
