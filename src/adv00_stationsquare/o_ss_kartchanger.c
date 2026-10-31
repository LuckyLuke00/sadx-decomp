#include "decls.h"
static void Exec(struct task *tp);
void FUN_007d21b0(...);

// STUB: SADX 0x00685a60
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00685bd0
void ObjectSSKartchanger(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->exec = Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	*(float *)((char *)var1 + 8) = (*(float *)((char *)var1 + 0x2c) + 1.0f) * 5.0f;
	*(float *)((char *)var1 + 0xc) = (*(float *)((char *)var1 + 0x30) + 1.0f) * 5.0f;
	*(float *)((char *)var1 + 0x10) = (*(float *)((char *)var1 + 0x34) + 1.0f) * 5.0f;
}
