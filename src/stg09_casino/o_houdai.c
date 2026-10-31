#include "decls.h"
static void NormalR(struct task *tp);
static void NormalL(struct task *tp);
static void Disp(struct task *tp);

// STUB: SADX 0x00882820
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00882840
static void NormalL(struct task *tp)
{
}

// STUB: SADX 0x008828a0
static void NormalR(struct task *tp)
{
}

// FUNCTION: SADX 0x00882990
void ObjectHoudaiL(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = NormalL;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x008829b0
void ObjectHoudaiR(struct task *tp)
{
	tp->twp->mode = 1;
	tp->exec = NormalR;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
