#include "decls.h"

// FUNCTION: SADX 0x006877a0
long FUN_006877a0(struct task *param_1)
{
	return EntryColliList(param_1->twp);
}

// FUNCTION: SADX 0x006879e0
void ColliInit(struct task *tp)
{
	CCL_Init(tp, barricade_c_info, 1, 4);
	tp->exec = (void (__cdecl *)(struct task *))FUN_006877a0;
}
