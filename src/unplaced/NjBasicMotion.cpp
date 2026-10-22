#include "decls.h"
extern void *DAT_01c76fa0;

// FUNCTION: SADX 0x0067e380
void njActionOld(struct NJS_ACTION const *param_1, float param_2)
{
	struct obj *var1;
	struct NJS_MOTION *var2;

	var1 = param_1->object;
	var2 = param_1->motion;
	njStartMotionObj(var2, param_2);
	*(void **)((char *)DAT_01c76fa0 + 0xc) = _njDrawModel;
	_njBeginModel();
	_njPushPopMotion(var1);
	_njEndModel();
}

// FUNCTION: SADX 0x0067e3c0
void njGetDrawMotion(struct obj const *param_1, struct NJS_MOTION const *param_2, struct NJS_MOTION_DATA *param_3, float param_4)
{
	*(void **)((char *)DAT_01c76fa0 + 0x0) = param_3->pos;
	*(void **)((char *)DAT_01c76fa0 + 0x8) = param_3->ang;
	*(void **)((char *)DAT_01c76fa0 + 0x4) = param_3->scl;
	njStartMotionObj(param_2, param_4);
	_njPushPopGetMotionDataArray(param_1);
}

// STUB: SADX 0x0067e410
void njGetAction(struct NJS_ACTION const *param_1, struct NJS_MOTION_DATA *param_2, float param_3)
{
}
