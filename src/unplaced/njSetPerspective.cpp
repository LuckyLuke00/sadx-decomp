#include "decls.h"
extern float DAT_0629c6e4;
extern double njTan(int param_1);
extern float DAT_0629c6e0;

// FUNCTION: SADX 0x0067e550
void njSetPerspective(long param_1)
{
	double local_c;
	local_c = (double)DAT_0629c6e4;
	local_c = local_c / (njTan((int)(param_1 / 2)) * 2.0);
	DAT_0629c6e0 = (float)local_c;
}
