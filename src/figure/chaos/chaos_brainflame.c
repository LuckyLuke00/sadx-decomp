#include "decls.h"
extern int DAT_05b9d838;
extern float DAT_05b3df40;
extern struct NJS_TEXANIM anim_c2_brain[1];
extern struct NJS_SPRITE sprite_c2_brain;

// STUB: SADX 0x008c5bb0
void Effect_ChaosBrainFlame(struct task *tp)
{
}

// STUB: SADX 0x008c5c80
void Effect_ChaosBrainFlameDisplay(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	anim_c2_brain[0].texid = local_8->timer.w[1];
	*(float *)&DAT_05b3df40 = 50.0f;
	late_DrawSprite3D(&sprite_c2_brain, 0, 0x30, 4);
	*(float *)&DAT_05b3df40 = 0.0f;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008c5d90
void Effect_ChaosCore(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->timer.l = 0;
		local_8->mode = 1;
		tp->disp = Effect_ChaosCoreDisplay;
		break;
	case 1:
		local_8->timer.w[0]++;
		if (local_8->timer.w[0] >= 2)
		{
			local_8->timer.w[0] -= 2;
			local_8->timer.w[1]++;
			if (local_8->timer.w[1] >= 0x10)
				local_8->timer.w[1] = 0;
		}
		if (local_8->counter.ptr != 0)
			local_8->pos = *(struct NJS_POINT3 *)local_8->counter.ptr;
		break;
	}
	Effect_ChaosCoreDisplay(tp);
}
