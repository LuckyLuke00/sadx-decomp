#include "decls.h"
extern struct particle_entry SandParticleEntry;
extern "C" int rand(void);
void effectSand(struct sp_task *task_p, struct sp_link *link_p);

// STUB: SADX 0x007e6ff0
void effectSand(struct sp_task *task_p, struct sp_link *link_p)
{
}

// STUB: SADX 0x007e7090
void CreateSand2(struct particle_info *effect_p)
{
	struct sp_task *var1;
	int var2;
	float var3;
	int var4;
	float var5;
	var1 = SpCreateTask(SandParticleEntry.link, effectSand);
	if (var1)
	{
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05f;
		var1->ang = 0x1000 - (int)(var3 * -4096.0f);
		var4 = rand();
		var5 = (float)var4 * 3.0517578125e-05f;
		var1->frame = var5 * 4.0f;
		var1->scl = effect_p->scl;
		*(int *)&var1->pos.x = *(int *)&effect_p->pos.x;
		*(int *)&var1->pos.y = *(int *)&effect_p->pos.y;
		*(int *)&var1->pos.z = *(int *)&effect_p->pos.z;
		*(int *)&var1->spd.x = *(int *)&effect_p->velo.x;
		*(int *)&var1->spd.y = *(int *)&effect_p->velo.y;
		*(int *)&var1->spd.z = *(int *)&effect_p->velo.z;
		*(int *)&var1->argb.a = *(int *)&effect_p->argb.a;
		*(int *)&var1->argb.r = *(int *)&effect_p->argb.r;
		*(int *)&var1->argb.g = *(int *)&effect_p->argb.g;
		*(int *)&var1->argb.b = *(int *)&effect_p->argb.b;
		var1->work[0].ptr = effect_p;
	}
}
