#include "decls.h"
extern void *DAT_01c76fa0;
extern void (*DAT_05ada214)(struct obj *);
void njMotionTransformEx(struct obj const *);
extern void (*DAT_05ada218)(struct cnkobj const *);
extern int DAT_0629c3b0;

// FUNCTION: SADX 0x00432a60
void _njSetMDataCnt(int param_1)
{
	int var1;
	int var2;

	var1 = param_1 * 4;
	*(int *)((char *)DAT_0629c3b0 + 0x4) = var1;
	var2 = var1 * 2;
	*(int *)((char *)DAT_0629c3b0 + 0x8) = var2;
	var2 = *(int *)((char *)DAT_0629c3b0 + 0x0);
	*(int *)((char *)DAT_0629c3b0 + 0xc) = var2;
	var2 = *(int *)((char *)DAT_0629c3b0 + 0x4) + var2;
	*(int *)((char *)DAT_0629c3b0 + 0x10) = var2;
	*(int *)((char *)DAT_0629c3b0 + 0x1c) = 0;
}

// FUNCTION: SADX 0x00432ab0
void _njCnkPushPopMotion(struct cnkobj const *param_1)
{
	do
	{
		njPushMatrixEx();
		njMotionTransformEx((struct obj const *)param_1);
		if (DAT_05ada218)
		{
			DAT_05ada218(param_1);
		}
		if (param_1->model && (param_1->evalflags & 8) == 0)
		{
			_njCnkDrawModel(param_1->model);
		}
		if (param_1->child)
		{
			_njCnkPushPopMotion(param_1->child);
		}
		njPopMatrixEx();
		param_1 = param_1->sibling;
	} while (param_1);
}

// FUNCTION: SADX 0x00432b10
void _njCnkPushPopMotionLink(struct cnkobj const *param_1)
{
	struct cnkobj const *var1;

	var1 = param_1;
	do
	{
		njPushMatrixEx();
		njMotionLinkTransformEx((const struct obj *)var1);
		if (DAT_05ada218 != 0)
		{
			DAT_05ada218(var1);
		}
		if (var1->model != 0 && (var1->evalflags & 8) == 0)
		{
			_njCnkDrawModel(var1->model);
		}
		if (var1->child != 0)
		{
			_njCnkPushPopMotionLink(var1->child);
		}
		njPopMatrixEx();
		var1 = var1->sibling;
	} while (var1 != 0);
}

// FUNCTION: SADX 0x00432b70
void _njPushPopMotion(struct obj const *param_1)
{
	do
	{
		njPushMatrixEx();
		njMotionTransformEx(param_1);
		if (DAT_05ada214)
		{
			DAT_05ada214((struct obj *)param_1);
		}
		if (param_1->model && (param_1->evalflags & 8) == 0)
		{
			(*(void (**)(struct NJS_MODEL *))((char *)DAT_01c76fa0 + 0xc))(param_1->model);
		}
		if (param_1->child)
		{
			_njPushPopMotion(param_1->child);
		}
		njPopMatrixEx();
		param_1 = param_1->sibling;
	} while (param_1);
}

// STUB: SADX 0x00432bd0
int _njGetMotionFloat3(float * const param_1)
{
	return (int)0;
}

// STUB: SADX 0x00432c20
int _njGetMotionAngle1(long *param_1)
{
	return (int)0;
}

// STUB: SADX 0x00432c70
int _njGetMotionAngle3(long * const param_1)
{
	return (int)0;
}

// STUB: SADX 0x00432cc0
int _njGetMotionQuaternion(struct NJS_QUATERNION *param_1)
{
	return (int)0;
}
