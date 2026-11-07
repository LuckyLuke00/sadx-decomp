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

// STUB: SADX 0x008a4bd0
static void DispATask(struct task *tp)
{
}

// STUB: SADX 0x008a4cc0
static void ExecATask(struct task *tp)
{
}

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
	var1->timer.l = 0;
	var1->value.l = 0;
	tp->exec = ExecATask;
	tp->disp = DispATask;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
