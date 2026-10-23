#include "decls.h"
static void ObjectCasinoEarthShakeExec(struct task *tp);

// STUB: SADX 0x0088d7c0
static void ObjectCasinoEarthShakeExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0088d8a0
void ObjectCasinoEarthShake(struct task *tp)
{
	tp->exec = ObjectCasinoEarthShakeExec;
}

// STUB: SADX 0x0088d8b0
struct task *CreateEarthShake_Casino(struct NJS_POINT3 *pos, float rad, float shake)
{
	return (struct task *)0;
}
