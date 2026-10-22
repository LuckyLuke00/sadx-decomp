#include "decls.h"
extern void FUN_0041b120(int param_1, int param_2);
extern void stSetBaseMatrix(float (*param_1)[16]);
extern void *DAT_05ab39ac;
void njStartMotionLink(struct NJS_MOTION_LINK const *, float);
void stSetBaseMatrix(float (*)[16]);
void _njCnkPushPopMotionLink(struct cnkobj const *);
extern int DAT_0629c518;
extern int DAT_05ada5b8;
void FUN_0041b120(int param_1, int param_2);

// STUB: SADX 0x00435fd0
void njCnkDrawMotion(struct cnkobj const *param_1, struct NJS_MOTION const *param_2, float param_3)
{
}

// FUNCTION: SADX 0x00436030
void njCnkDrawMotionLink(struct cnkobj const *param_1, struct NJS_MOTION_LINK const *param_2, float param_3)
{
	void (__thiscall *fp)(int, int);

	njStartMotionLink(param_2, param_3);
	DAT_05ada5b8 = 1;
	stSetBaseMatrix((float (*)[16])DAT_0629c518);
	fp = (void (__thiscall *)(int, int))FUN_0041b120;
	((void (__thiscall *)(void *, int, int))fp)(DAT_05ab39ac, 0, 0);
	((void (__thiscall *)(void *, int, int))fp)(DAT_05ab39ac, 1, 0);
	_njCnkPushPopMotionLink(param_1);
}

// STUB: SADX 0x00436090
void _njCnkDrawModel(struct NJS_CNK_MODEL *param_1)
{
}

// STUB: SADX 0x004361a0
void njCnkDrawModel(struct NJS_CNK_MODEL *param_1)
{
}

// STUB: SADX 0x00436200
void njCnkDrawObject(struct cnkobj *param_1)
{
}
