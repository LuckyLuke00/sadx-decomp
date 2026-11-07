#include "decls.h"
extern struct taskwk *DAT_05b42a7c;
extern unsigned char DAT_060dbca7;
static void Normal(struct task *tp);

// STUB: SADX 0x00887ea0
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x00888080
void CameraPinball(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	CameraSetEventCamera(0x3e, 0);
	var1->btimer = 0xff;
	DAT_060dbca7 = 0x80;
	DAT_05b42a7c->scl.x = var1->scl.x;
	DAT_05b42a7c->scl.y = var1->scl.y;
	DAT_05b42a7c->scl.z = var1->scl.z;
	DAT_05b42a7c->counter.f = var1->pos.x;
	DAT_05b42a7c->timer.f = var1->pos.y;
	DAT_05b42a7c->value.f = var1->pos.z;
	tp->exec = Normal;
}
