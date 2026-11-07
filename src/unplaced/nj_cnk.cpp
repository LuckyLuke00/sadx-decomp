#include "decls.h"
#include "../advertise.h"
extern void stSetBaseMatrix(float (*)[16]);
extern void njStartMotionObj(struct NJS_MOTION const *param_1, float param_2);
extern void _njCnkPushPopMotion(struct cnkobj const *);
void _njCnkPushPopMotion(struct cnkobj const *);
extern void _njCnkDrawObject(struct cnkobj *param_1);
extern void stSetBaseMatrix(float (*param_1)[16]);
extern void *DAT_05ab39ac;
void stSetBaseMatrix(float (*)[16]);
extern int DAT_0629c518;
extern int DAT_05ada5b8;

// FUNCTION: SADX 0x00435fd0
void njCnkDrawMotion(const NJS_CNK_OBJECT *param_1, const NJS_MOTION *param_2, Float param_3)
{
	njStartMotionObj(param_2, param_3);
	DAT_05ada5b8 = 1;
	stSetBaseMatrix((float (*)[16])DAT_0629c518);
	((SOCRender *)DAT_05ab39ac)->FUN_0041b120(0, 0);
	((SOCRender *)DAT_05ab39ac)->FUN_0041b120(1, 0);
	_njCnkPushPopMotion(param_1);
}

// STUB: SADX 0x00436030
void njCnkDrawMotionLink(const NJS_CNK_OBJECT *param_1, const NJS_MOTION_LINK *param_2, Float param_3)
{
}

// STUB: SADX 0x00436090
void _njCnkDrawModel(struct NJS_CNK_MODEL *param_1)
{
}

// STUB: SADX 0x004360c0
void _njCnkDrawObject(struct cnkobj *param_1)
{
}

// STUB: SADX 0x004361a0
void njCnkDrawModel(struct NJS_CNK_MODEL *param_1)
{
}

// STUB: SADX 0x00436200
void njCnkDrawObject(NJS_CNK_OBJECT *param_1)
{
}
