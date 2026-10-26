#include "decls.h"
extern struct obj _object_tr2crash_tr2crash[1];
extern int DAT_060cb5d8;

// FUNCTION: SADX 0x0072a410
void FUN_0072a410(void)
{
	struct obj *var1 = _object_tr2crash_tr2crash[0].child;
	struct obj *var2 = var1->sibling;
	DAT_060cb5d8 = (int)var2->sibling;
	var2->sibling = 0;
}
