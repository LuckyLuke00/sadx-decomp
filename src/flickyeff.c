#include "decls.h"
void Wa_new(struct task *tp);
void dispWa_new(struct task *tp);

// FUNCTION: SADX 0x0061ed90
void Wa_new(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->timer.w[1]++;
	switch (local_8->mode)
	{
		case 0:
			local_8->counter.f += 0.02f;
			if (local_8->counter.f > 0.5f)
			{
				local_8->mode = 1;
			}
			break;
		case 1:
			local_8->timer.w[0]++;
			if (local_8->timer.w[0] > 3)
			{
				local_8->timer.w[0] = 3;
			}
			local_8->counter.f += 0.015f;
			if (local_8->counter.f >= 1.0f)
			{
				FreeTask(tp);
				return;
			}
			break;
	}
	dispWa_new(tp);
}

// FUNCTION: SADX 0x0061ee70
void dispWa_new(struct task *tp)
{
	struct taskwk *local_30g;
	struct NJS_ARGB argb;
	float local_2c;
	local_30g = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	local_2c = 1.0 - local_30g->counter.f * 1.7999999523162842;
	if (local_2c < -0.800000011920929)
	{
		local_2c = -0.800000011920929;
	}
	argb = getARGB(local_30g->smode, 1.0 - local_30g->counter.f, local_2c);
	___njSetConstantMaterial(&argb);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	njTranslateV(0, &local_30g->pos);
	___njDrawSprite3D(&sprite_particle_waka, local_30g->timer.w[0], 0x32);
	njPopMatrix(1);
	argb.b = 0.0;
	argb.g = argb.b;
	argb.r = argb.g;
	argb.a = argb.r;
	___njSetConstantMaterial(&argb);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// FUNCTION: SADX 0x0061efd0
struct NJS_ARGB getARGB(int colormode, float alpha, float rate_color)
{
	struct NJS_ARGB local_18;

	local_18.a = alpha;
	switch (colormode)
	{
		case 0:
			local_18.r = 1.0f;
			local_18.b = rate_color;
			local_18.g = rate_color;
			break;
		case 1:
			local_18.r = rate_color;
			local_18.b = rate_color;
			local_18.g = 1.0f;
			break;
		case 2:
			local_18.r = rate_color;
			local_18.b = 1.0f;
			local_18.g = rate_color;
			break;
		case 3:
			local_18.r = 1.0f;
			local_18.b = 1.0f;
			local_18.g = 1.0f;
			break;
		case 4:
			local_18.r = 1.0f;
			local_18.b = rate_color;
			local_18.g = 1.0f;
			break;
		case 5:
			local_18.r = 1.0f;
			local_18.b = 1.0f;
			local_18.g = rate_color;
			break;
		case 6:
			local_18.r = rate_color;
			local_18.b = 1.0f;
			local_18.g = 1.0f;
			break;
		default:
			local_18.r = 0.5f;
			local_18.b = 0.7f;
			local_18.g = 1.0f;
			break;
	}
	return local_18;
}
