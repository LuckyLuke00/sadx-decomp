#include "decls.h"
void FUN_00477cf0(int param_1);
long FUN_00478350(int param_1);
void FUN_00477c40(void *param_1, void *param_2);
float njSqrt(float param_1);

// FUNCTION: SADX 0x00477b80
float ghUnitVector(const struct NJS_POINT3 *r4, struct NJS_POINT3 *r5)
{
	float var1;
	float local_10;
	float local_c;
	float local_8;

	var1 = r4->x;
	local_10 = r4->y;
	local_c = r4->z;
	local_8 = 1.0f / njSqrt(var1 * var1 + local_10 * local_10 + local_c * local_c);
	r5->x = var1 * local_8;
	r5->y = local_10 * local_8;
	r5->z = local_c * local_8;
	return local_8;
}

// FUNCTION: SADX 0x00477c00
float FUN_00477c00(float *param_1, float *param_2)
{
	float var1;
	float var2;

	var1 = *param_2 - *param_1;
	var2 = param_2[2] - param_1[2];
	return var1 * var1 + 0.0 + var2 * var2;
}

// STUB: SADX 0x00477c40
void FUN_00477c40(void *param_1, void *param_2)
{
}

// STUB: SADX 0x00477c60
void *FUN_00477c60(void)
{
	return (void *)0;
}

// STUB: SADX 0x00477cf0
void FUN_00477cf0(int param_1)
{
}

// STUB: SADX 0x00477ef0
int FUN_00477ef0(struct task *tp)
{
	return (int)0;
}

// STUB: SADX 0x00478180
void FUN_00478180(struct task *tp)
{
}

// STUB: SADX 0x00478350
long FUN_00478350(int param_1)
{
	return (long)0;
}

// STUB: SADX 0x00478360
void FUN_00478360(struct task *task_p)
{
}

// FUNCTION: SADX 0x00478480
void hintbox_edit_print()
{
	njPrintC(0x110013, "<-CAM Dist(def. 80.0)");
	njPrintC(0x110014, "<-CAM Hight");
	njPrintC(0x110015, "<-Message ID");
}

// STUB: SADX 0x004785b0
void FUN_004785b0(struct task *task_p)
{
}

// STUB: SADX 0x00478750
void hintbox_exec(struct task *task_p)
{
}
