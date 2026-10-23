#include "decls.h"

// FUNCTION: SADX 0x007da5c0
void dark_dest(struct task *tp)
{
	le_DeleteLight(2);
	lig_cpyPalette(0, 8);
}

// STUB: SADX 0x007da5e0
void dark_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x007da690
void dark_on()
{
	DAT_060cca74 = CreateElementalTask(0, 1, dark_cons);
}
