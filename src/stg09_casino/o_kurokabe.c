#include "decls.h"
static void Normal(struct task *tp);
static void Disp(struct task *tp);
extern int DAT_060dbcb0;

#pragma optimize("", off)
// STUB: SADX 0x00882e80
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00882ea0
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00882ec0
void ObjectKurokabe(struct task *tp)
{
	DAT_060dbcb0 &= 0xffffff3f;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = ExplosionRockDestructor;
}
