#include "decls.h"

// GLOBAL: SADX 0x041eb7bc
static struct NJS_SPRITE sprite_wing_light;

extern struct obj object_skydeck_vent_vent[1];
void FUN_007d21b0(...);

// STUB: SADX 0x0083eba0
void SetCloudSkydeck(struct task *tp)
{
}

// STUB: SADX 0x0083ec00
void CutCloudSkydeck(struct task *tp)
{
}

// FUNCTION: SADX 0x0083edf0
void ObjectSkydeck_vent_Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 250.0f))
	{
		___njSetTexture(&texlist_obj_skydeck);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.x + var1->ang.z)
		{
			njRotateZ(0, (unsigned short)((unsigned short)var1->ang.x + (unsigned short)var1->ang.z));
		}
		if (var1->ang.y)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		late_DrawObjectClip(object_skydeck_vent_vent, 1, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0083efe0
void ObjectSkydeck_signal_Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		float var2 = (float)var1->ang.y * 0.0625;

		float var3 = 0.5f + njSin(var1->counter.b[3] * var1->ang.x) * 0.5f;

		if (FUN_004c39c0(tp) == 0)
		{
			var3 = var1->value.f * var3;
		}
		___njColorBlendingMode(0, 7);
		___njColorBlendingMode(1, 0xa);
		SetMaterial(var3, var1->scl.x, var1->scl.y, var1->scl.z);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		___njFogDisable();
		sprite_wing_light.sx = var2;
		sprite_wing_light.sy = var2;
		___njDrawSprite3D(&sprite_wing_light, 0, 0x32);
		___njFogEnable();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0083f3d0
void ObjectSkydeck_vent(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->scl.z = 0.0f;
			tp->disp = ObjectSkydeck_vent_Draw;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			break;
		case 1:
		{
			int var2 = (int)(GetWindSkydeck(var1->pos.x, var1->pos.z) * 32.0f);
			if (var1->ang.z < var2)
			{
				var1->scl.z += var1->scl.y;
			}
			else
			{
				var1->scl.z -= var1->scl.x;
			}
			var1->ang.z += (int)var1->scl.z;
			if (var1->ang.z > 0x4000)
			{
				var1->ang.z = 0x4000;
				var1->scl.z *= -0.5f;
			}
			if (var1->ang.z < -0x2000)
			{
				var1->ang.z = -0x2000;
				var1->scl.z *= -0.5f;
			}
			break;
		}
		}
		ObjectSkydeck_vent_Draw(tp);
	}
}

// FUNCTION: SADX 0x0083f4b0
void ObjectSkydeck_decal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		if (var1->mode == 1)
		{
			if (SkydeckCheck_break(var1->pos.x, var1->pos.y, var1->pos.z) == 0)
			{
				return;
			}
			DeadOut(tp);
			return;
		}
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		tp->disp = ObjectSkydeck_decal_Draw;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		break;
	case 1:
		if (SkydeckCheck_break(var1->pos.x, var1->pos.y, var1->pos.z) == 0)
		{
			break;
		}
		var1->ang.z += -256;
		var1->pos.y += 3.4000000953674316;
		var1->pos.x += 3.5;
		break;
	}
	ObjectSkydeck_decal_Draw(tp);
}

// STUB: SADX 0x0083f580
void ObjectSkydeck_signal(struct task *tp)
{
}
