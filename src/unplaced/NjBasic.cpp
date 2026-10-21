#include "decls.h"
extern void *DAT_05ad9a9c;

// FUNCTION: SADX 0x0042ba90
void njSetMaterialCallBackFunc(void (*param_1)(void))
{
	DAT_05ad9a9c = param_1;
}
