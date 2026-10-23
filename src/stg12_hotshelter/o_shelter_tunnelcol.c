#include "decls.h"

// FUNCTION: SADX 0x008b5f40
void CreateTunnelcol()
{
	struct task *var1;

	var1 = CreateElementalTask(6, 3, ObjShelterTunnelcol);
	var1->twp->smode = 0;
	var1 = CreateElementalTask(6, 3, ObjShelterTunnelcol);
	var1->twp->smode = 1;
}
