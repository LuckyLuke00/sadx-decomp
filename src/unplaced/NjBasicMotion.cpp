#include "decls.h"
extern void *DAT_01c76fa0;

// FUNCTION: SADX 0x0067e380
void njActionOld(struct NJS_ACTION const *action, float frame)
{
	struct obj *var1;
	struct NJS_MOTION *var2;

	var1 = action->object;
	var2 = action->motion;
	njStartMotionObj(var2, frame);
	*(void **)((char *)DAT_01c76fa0 + 0xc) = _njDrawModel;
	_njBeginModel();
	_njPushPopMotion(var1);
	_njEndModel();
}

// FUNCTION: SADX 0x0067e3c0
void njGetDrawMotion(struct obj const *object, struct NJS_MOTION const *motion, struct NJS_MOTION_DATA *data, float frame)
{
	*(void **)((char *)DAT_01c76fa0 + 0x0) = data->pos;
	*(void **)((char *)DAT_01c76fa0 + 0x8) = data->ang;
	*(void **)((char *)DAT_01c76fa0 + 0x4) = data->scl;
	njStartMotionObj(motion, frame);
	_njPushPopGetMotionDataArray(object);
}

// FUNCTION: SADX 0x0067e410
void njGetAction(struct NJS_ACTION const *action, struct NJS_MOTION_DATA *data, float frame)
{
	struct obj *var1;
	struct NJS_MOTION *var2;

	var1 = action->object;
	var2 = action->motion;
	*(void **)((char *)DAT_01c76fa0 + 0x0) = data->pos;
	*(void **)((char *)DAT_01c76fa0 + 0x8) = data->ang;
	*(void **)((char *)DAT_01c76fa0 + 0x4) = data->scl;
	njStartMotionObj(var2, frame);
	_njPushPopGetMotionDataArray(var1);
}
