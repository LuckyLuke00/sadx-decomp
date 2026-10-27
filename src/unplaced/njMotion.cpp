#include "decls.h"
extern struct NJS_MOTION *DAT_0629c400;
extern float DAT_0629c444;
void _njPushPopGetMotionDataArray(struct obj const *obj);
extern float *DAT_0629c440;
void njStartMotionObjEx(struct NJS_MOTION const *,float);
extern void (*DAT_05ada214)(struct obj *);
extern int DAT_0629c3b0;
extern int DAT_0629c3c0;
extern int DAT_05ada210;

// FUNCTION: SADX 0x004252b0
void njCnkSetShortAngleUser(void)
{
	DAT_05ada210 |= 1;
}

// FUNCTION: SADX 0x004252c0
void njCnkClrShortAngleUser(void)
{
	DAT_05ada210 &= 0xfffffffe;
}

// FUNCTION: SADX 0x004253a0
void njSetCurMotionInfoSlot(int param_1)
{
	DAT_0629c3b0 = (int)(&DAT_0629c3c0) + param_1 * 0x40;
}

// FUNCTION: SADX 0x004253c0
void njSetMotionCallback(void (*param_1)(struct obj *))
{
	DAT_05ada214 = param_1;
}

#pragma optimize("", off)
// STUB: SADX 0x004253d0
void njStartMotionObjEx(struct NJS_MOTION const *param_1,float param_2)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00425470
void njStartMotionLink(struct NJS_MOTION_LINK const *param_1,float param_2)
{
	DAT_0629c3b0 = (int)&DAT_0629c400;
	njStartMotionObjEx((struct NJS_MOTION const *)(*(int *)((char *)param_1 + 4)),*(float *)((char *)param_1 + 0xc));
	DAT_0629c3b0 = (int)&DAT_0629c3c0;
	njStartMotionObjEx((struct NJS_MOTION const *)(*(int *)param_1),*(float *)((char *)param_1 + 8));
	DAT_0629c444 = param_2;
}

// FUNCTION: SADX 0x004254c0
void njInitShape(float *param_1)
{
	DAT_0629c440 = param_1;
}

// FUNCTION: SADX 0x00425610
void njStartMotionObj(struct NJS_MOTION const *param_1,float param_2)
{
	DAT_0629c3b0 = (int)&DAT_0629c3c0;
	njStartMotionObjEx(param_1,param_2);
}

// STUB: SADX 0x00425640
void njMotionTransformEx(struct obj const *param_1)
{
}

// STUB: SADX 0x004258c0
void _njPushPopGetMotionDataArray(struct obj const *param_1)
{
}
