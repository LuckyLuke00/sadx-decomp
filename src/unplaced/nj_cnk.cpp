#include "decls.h"
extern void FUN_0041b120(int, int);
extern void stSetBaseMatrix(float (*)[16]);
extern void njStartMotionObj(struct NJS_MOTION const *param_1, float param_2);
extern void _njCnkPushPopMotion(struct cnkobj const *);
void FUN_0041b120(int param_1,int param_2);
void _njCnkPushPopMotion(struct cnkobj const *);
extern void _njCnkDrawObject(struct cnkobj *param_1);
extern void FUN_0041b120(int param_1, int param_2);
extern void stSetBaseMatrix(float (*param_1)[16]);
extern void *DAT_05ab39ac;
void stSetBaseMatrix(float (*)[16]);
extern int DAT_0629c518;
extern int DAT_05ada5b8;
void FUN_0041b120(int param_1, int param_2);

// STUB: SADX 0x00435fd0
void njCnkDrawMotion(struct cnkobj const *object, struct NJS_MOTION const *motion, float frame)
{
	void (__thiscall *fp)(int, int);

	njStartMotionObj(motion, frame);
	DAT_05ada5b8 = 1;
	stSetBaseMatrix((float (*)[16])DAT_0629c518);
	fp = (void (__thiscall *)(int, int))FUN_0041b120;
	((void (__thiscall *)(void *, int, int))fp)(DAT_05ab39ac, 0, 0);
	((void (__thiscall *)(void *, int, int))fp)(DAT_05ab39ac, 1, 0);
	_njCnkPushPopMotion(object);
}

// STUB: SADX 0x00436030
void njCnkDrawMotionLink(struct cnkobj const *object, struct NJS_MOTION_LINK const *motionlink, float frame)
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
void njCnkDrawModel(struct NJS_CNK_MODEL *model)
{
}

// STUB: SADX 0x00436200
void njCnkDrawObject(struct cnkobj *object)
{
}
