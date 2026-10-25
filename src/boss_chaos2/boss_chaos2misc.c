#include "decls.h"
extern struct NJS_ARGB DAT_0286f1d8;
extern struct NJS_ARGB DAT_0286f1c8;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006e7820
void Chaos2BallExplodeDisplay(struct task *tp)
{
	struct taskwk *var1;
	static struct NJS_ARGB var2;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 0xa);
		___njColorBlendingMode(1, 0xa);
		___njSetConstantMaterial(&DAT_0286f1c8);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (DAT_05b42a7c->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)DAT_05b42a7c->ang.y);
		}
		if (DAT_05b42a7c->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)DAT_05b42a7c->ang.x);
		}
		late_DrawSprite3D(&sprite_c2_flash, (int)var1->counter.f, 0x30, 4);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
}

// FUNCTION: SADX 0x006e78e0
void Chaos2BallExplode(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->counter.f = 0.0f;
		tp->disp = Chaos2BallExplodeDisplay;
		local_8->mode = 1;
	case 1:
		local_8->counter.f = local_8->counter.f + 0.2666666805744171f;
		if (local_8->counter.f >= 8.0f)
		{
			DestroyTask(tp);
			return;
		}
	}
	Chaos2BallExplodeDisplay(tp);
}

// STUB: SADX 0x006e7940
void dispMiniBallSprite(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x006e7c60
void Chaos2ColumnMain(struct task *tp)
{
	if (DAT_05b9d838 == 0)
	{
		Chaos2ColumnDispay(tp);
	}
}

// STUB: SADX 0x006e7c70
void Chaos2Column(struct task *tp)
{
}
