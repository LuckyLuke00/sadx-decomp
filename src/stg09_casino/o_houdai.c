#include "decls.h"
static void NormalL(struct task *tp);
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00882820
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00882840
static void NormalL(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00882990
void ObjectHoudaiL(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = NormalL;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// STUB: SADX 0x008829b0
void ObjectHoudaiR(struct task *tp)
{
	tp->twp->mode = 1;
	tp->exec = (void (*)(struct task *))0x8828a0;
	tp->disp = (void (*)(struct task *))0x882820;
	tp->dest = (void (*)(struct task *))0x7d21b0;
}
