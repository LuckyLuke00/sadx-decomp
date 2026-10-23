#include "decls.h"
extern void *DAT_05ad9a9c;

// STUB: SADX 0x0042b7e0
void _njEndModel(void)
{
}

// STUB: SADX 0x0042b810
void _njTransformObject(struct obj *obj, void (*param_2)(struct NJS_MODEL *))
{
}

// FUNCTION: SADX 0x0042ba90
void njSetMaterialCallBackFunc(void (*param_1)(void))
{
	DAT_05ad9a9c = param_1;
}
