#include "decls.h"

// FUNCTION: SADX 0x00815930
void ObjectTPPirates(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2280100.0f) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			SetObjectTexture();
			njPushMatrix(NULL);
			njTranslateV(NULL, &var1->pos);
			if (var1->ang.y != 0)
			{
				njRotateY(NULL, (unsigned short)var1->ang.y);
			}
			ds_DrawObjectClip((struct obj *)&object_newship_oya_oya, 1.0f);
			njRotateY(NULL, 0x8000);
			ds_DrawObjectClip((struct obj *)&object_newship_oya_oya, 1.0f);
			njPopMatrix(1);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			tp->dest = ExplosionRockDestructor;
			CreateChildrenTask((struct childtaskset *)&cts_tpp, tp);
			break;
		case 1:
			LoopTaskC(tp);
			return;
		}
	}
}
