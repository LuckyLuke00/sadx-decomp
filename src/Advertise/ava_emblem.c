#include "decls.h"

// FUNCTION: SADX 0x00597c20
long AvaGetTotalNumberEmblem()
{
	struct SAVE_DATA *local_8g;
	long local_cg;
	local_8g = GetSDp();
	local_cg = FUN_0049e130(local_8g);
	return local_cg;
}
