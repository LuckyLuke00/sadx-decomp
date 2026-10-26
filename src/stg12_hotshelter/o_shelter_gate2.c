#include "decls.h"
void DispATask(struct task *tp);
static void InitATask(struct task *tp);
static void ExecATask(struct task *tp);
static void DispATask(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008a4a90
static void InitATask(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008a4bd0
static void DispATask(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008a4cc0
static void ExecATask(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008a4f00
void ObjShelterGate2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	InitATask(tp);
	var1->mode = 0;
	tp->exec = ExecATask;
	tp->disp = DispATask;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x008a4f30
void ObjShelterGate13(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	InitATask(tp);
	var1->mode = 1;
	*(int *)((char *)var1 + 0xc) = 0;
	*(int *)((char *)var1 + 0x10) = 0;
	tp->exec = ExecATask;
	tp->disp = DispATask;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
