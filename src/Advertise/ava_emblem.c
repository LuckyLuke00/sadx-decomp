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

// STUB: SADX 0x00597c50
int AvaGetTrialEmblem(enum AvaCharEnum chnum, long stage, long level)
{
	return (int)0;
}
