#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x0082f850
void Object_Mountain_Futa_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		ds_DrawModelClip(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4), 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0082fa30
void Object_Mountain_Futa(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			CreateChildrenTask((struct childtaskset *)cts_mount_futa, tp);
			CCL_Init(tp, (struct CCL_INFO *)futa_colli, 1, 4);
			var1->mode = 1;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				if (*(int *)((char *)var1->cwp + 4) & 1)
				{
					if (GetPlayerNumber() != 3)
					{
						var1->mode = 2;
						*(int *)((char *)var1->cwp->info + 4) |= 0x10;
					}
				}
			}
			break;
		default:
			LoopTaskC(tp);
			EntryColliList(var1);
			return;
	}
	LoopTaskC(tp);
	EntryColliList(var1);
}
