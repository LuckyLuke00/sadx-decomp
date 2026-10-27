#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
void EffectJet(struct sp_task *tp, struct sp_link *lp);
extern struct particle_entry particle_jet;
extern "C" int rand(void);

// FUNCTION: SADX 0x0060d390
void CreateJet(struct particle_info *pinfo)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;

	local_8gk = particle_jet.link;
	local_ci = SpCreateTask(local_8gk, EffectJet);
	if (local_ci != NULL)
	{
		local_ci->pos = pinfo->pos;
		local_ci->spd = pinfo->velo;
		local_ci->scl = pinfo->scl * 0.15000000596046448;
		local_ci->no = 0;
		local_ci->frame = 0.0f;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->ang = (int)(local_14k * 65536.0);
		local_ci->argb = pinfo->argb;
		local_ci->work[0].ptr = pinfo;
	}
}

// FUNCTION: SADX 0x0060d470
void EffectJet(struct sp_task *tp, struct sp_link *lp)
{
	struct sp_link *local_cg;
	float local_8g;

	local_cg = (struct sp_link *)*(int *)((char *)tp + 0x44);
	*(float *)((char *)tp + 0x30) -= *(float *)((char *)local_cg + 8) * 0.10000000149011612;
	if (*(float *)((char *)tp + 0x30) < 0.0)
	{
		SpFreeTask(tp);
		return;
	}
	local_8g = 1.0f - *(float *)((char *)local_cg + 0xc);
	*(float *)((char *)tp + 0x24) = *(float *)((char *)tp + 0x24) * local_8g;
	*(float *)((char *)tp + 0x28) = *(float *)((char *)tp + 0x28) * local_8g + *(float *)((char *)local_cg + 0x10);
	*(float *)((char *)tp + 0x2c) = *(float *)((char *)tp + 0x2c) * local_8g;
	*(float *)((char *)tp + 0x18) += *(float *)((char *)tp + 0x24);
	*(float *)((char *)tp + 0x1c) += *(float *)((char *)tp + 0x28);
	*(float *)((char *)tp + 0x20) += *(float *)((char *)tp + 0x2c);
	*(float *)((char *)tp + 0x14) -= *(float *)((char *)tp + 0x14) * *(float *)((char *)local_cg + 4) * 0.15000000596046448 * 0.10000000149011612;
	return;
}
