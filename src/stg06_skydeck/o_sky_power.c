#include "decls.h"

// FUNCTION: SADX 0x008410b0
void ObjectSkyMeka(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 4040100.0f))
	{
		return;
	}
	if (DAT_05ccde90)
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		SetObjectTexture();
		ds_DrawObjectClip(object_skymain_nc_obj_meka_obj_meka, 1.0f);
		njPopMatrix(1);
	}
	else
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			*(void **)((char *)var1 + 8) = action_skymain_nc_obj_meka;
			tp->dest = destChaos7Float;
			tp->disp = dispSkyPower;
			if (var1->scl.x < 0.0f)
			{
				var1->timer.f = 15.0f;
			}
			break;
		case 1:
			dispSkyPower(tp);
			break;
		}
	}
}

// FUNCTION: SADX 0x00841180
void ObjectSkyTutu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 4040100.0f))
	{
		return;
	}
	if (DAT_05ccde90)
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		SetObjectTexture();
		ds_DrawObjectClip(object_skymain_nc_obj_tutu_obj_tutu, 1.0f);
		njPopMatrix(1);
	}
	else
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			*(void **)((char *)var1 + 8) = action_skymain_nc_obj_tutu;
			tp->dest = destChaos7Float;
			tp->disp = dispSkyPower;
			break;
		case 1:
			dispSkyPower(tp);
			break;
		}
	}
}
