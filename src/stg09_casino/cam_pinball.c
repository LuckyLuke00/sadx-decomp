#include "decls.h"
extern struct taskwk *DAT_05b42a7c;
extern unsigned char DAT_060dbca7;
static void Normal(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00887ea0
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

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
	*(float *)((char *)DAT_05b42a7c + 8) = var1->pos.x;
	*(float *)((char *)DAT_05b42a7c + 0xc) = var1->pos.y;
	*(float *)((char *)DAT_05b42a7c + 0x10) = var1->pos.z;
	tp->exec = Normal;
}
