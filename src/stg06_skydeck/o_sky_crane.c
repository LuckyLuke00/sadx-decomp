#include "decls.h"
void FUN_008895d0(struct task *param_1);

// FUNCTION: SADX 0x0083fb10
void ObjectSkydeck_crane_Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 400.0f))
	{
		___njSetTexture(&texlist_obj_skydeck);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		ds_DrawObjectClip(object_skymain_kr_skymain_kr, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0083fd10
void ObjectSkydeck_crane_hang_Draw(struct task *tp)
{
	struct NJS_POINT3 p;
	p.x = tp->twp->pos.x;
	p.y = tp->twp->scl.z;
	p.z = tp->twp->pos.z;
	DrawShadow(&tp->twp->ang, &p, 1.0f);
}

// FUNCTION: SADX 0x0083ffb0
void ObjectSkydeck_crane(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2;
	struct task *var3;

	if (!CheckRangeOut(tp))
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			tp->disp = ObjectSkydeck_crane_Draw;
			tp->dest = FUN_008895d0;
			var2 = CreateChildTask(2, ObjectSkydeck_crane_hang, tp);
			var2->twp->smode = 0;
			var3 = CreateChildTask(2, ObjectSkydeck_crane_hang, tp);
			var3->twp->smode = 1;
			break;
		case 1:
			*(int *)((char *)var1 + 0x18) += 0x88;
			break;
		}
		ObjectSkydeck_crane_Draw(tp);
		ObjectSkydeck_com_GCM(tp);
		LoopTaskC(tp);
	}
}
