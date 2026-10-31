#include "decls.h"

// GLOBAL: SADX 0x03feb4a8
static struct CCL_INFO object_c_info[5];

extern struct NJS_ACTION action_kassha1st_st[1];
static void Draw(struct task *tp);

// FUNCTION: SADX 0x00833700
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 200.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		SaveControl3D();
		njControl3D(0x10);
		SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		ds_ActionClip(action_kassha1st_st, var1->counter.f, 1.0f);
		njPopMatrix(1);
		ResetMaterial();
		LoadControl3D();
	}
}

// FUNCTION: SADX 0x008337e0
void ObjectMountainGliding(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			CCL_Init(tp, (struct CCL_INFO *)&object_c_info, 5, 4);
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			var1->counter.f = 0.0f;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, NULL);
			}
			Draw(tp);
			var1->counter.f += 0.5;
			if (var1->counter.f >= 59.0)
			{
				var1->counter.f = 0.0f;
			}
			dsPlay_timer_v(0x85, (int)var1, 1, 0, 0xa, var1->pos.x, var1->pos.y, var1->pos.z);
			break;
		case 2:
			DeadOut(tp);
			break;
		}
	}
}
