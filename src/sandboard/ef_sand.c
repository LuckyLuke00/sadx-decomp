#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
extern struct particle_entry SandParticleEntry;
extern "C" int rand(void);
void effectSand(struct sp_task *task_p, struct sp_link *link_p);

// STUB: SADX 0x007e6ff0
void effectSand(struct sp_task *task_p, struct sp_link *link_p)
{
}

// FUNCTION: SADX 0x007e7090
void CreateSand2(struct particle_info *effect_p)
{
	struct sp_task *var1;
	float var2;
	var1 = SpCreateTask(SandParticleEntry.link, effectSand);
	if (var1 != 0)
	{
		var2 = (float)rand() * 3.0517578125e-05;
		var1->ang = 0x1000 - (int)(var2 * -4096.0);
		var2 = (float)rand() * 3.0517578125e-05;
		var1->frame = var2 * 4.0;
		var1->scl = effect_p->scl;
		var1->pos = effect_p->pos;
		var1->spd = effect_p->velo;
		var1->argb = effect_p->argb;
		var1->work[0].ptr = effect_p;
	}
}
