#include "decls.h"
struct NJS_MODEL;
void FUN_00571b20(int param_1);
struct obj;
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_ARGB DAT_0098bf28[4];
void FUN_00572380(struct obj *param_1, struct obj *param_2);
void FUN_005723e0(float param_1);
void FUN_00572f90(struct obj *param_1, struct obj *param_2);
void FUN_00573060(struct NJS_MODEL *param_1, struct obj *param_2);
extern struct obj object_sphere01;

// FUNCTION: SADX 0x00572380
void FUN_00572380(struct obj *param_1, struct obj *param_2)
{
	float local_8;

	local_8 = *(float *)((char *)param_1 + 0x14) * 0.10000000149011612;
	njPushMatrix(NULL);
	FUN_00572f90(param_1, param_2);
	FUN_005723e0(local_8);
	FUN_00573060(object_sphere01.model, param_1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005723e0
void FUN_005723e0(float param_1)
{
	FUN_0067d2d0(0, param_1, param_1, param_1);
}

// STUB: SADX 0x00572410
void FUN_00572410(struct obj *param_1, struct obj *param_2)
{
}

// STUB: SADX 0x005725a0
void FUN_005725a0(struct obj *param_1, struct obj *param_2)
{
}

// STUB: SADX 0x005726e0
void FUN_005726e0(struct obj *param_1, struct obj *param_2)
{
}

// STUB: SADX 0x005728e0
void FUN_005728e0(struct obj *param_1, struct obj *param_2)
{
}

// STUB: SADX 0x00572a80
void FUN_00572a80(struct obj *param_1, struct obj *param_2)
{
}

// FUNCTION: SADX 0x00572f90
void FUN_00572f90(struct obj *param_1, struct obj *param_2)
{
	int local_8g = (int)param_1->model;
	int local_cg;

	if ((local_8g & 0x20) == 0)
	{
		njTranslateV(NULL, (struct NJS_POINT3 *)((char *)param_2 + 0x20));
		if ((local_8g & 0x8000) == 0)
		{
			local_cg = (int)((char *)param_2 + 0x14);
			if ((local_8g & 0x200) != 0)
			{
				FUN_00571b20(local_cg);
				FUN_00573040(local_cg);
				FUN_008c2030(local_cg);
			}
			else
			{
				FUN_00573040(local_cg);
				FUN_008c2030(local_cg);
				FUN_00571b20(local_cg);
			}
		}
	}
	njTranslateV(NULL, (struct NJS_POINT3 *)((char *)param_1 + 8));
}

// FUNCTION: SADX 0x00573040
void FUN_00573040(int param_1)
{
	if (*(int *)((char *)param_1 + 8) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)param_1 + 8));
	}
	return;
}

// FUNCTION: SADX 0x00573060
void FUN_00573060(struct NJS_MODEL *param_1, struct obj *param_2)
{
	int local_8;

	local_8 = *(unsigned char *)((char *)param_2 + 3) & 3;
	if (local_8 < 4)
		___njSetConstantMaterial(&DAT_0098bf28[local_8]);
	___dsDrawModel(param_1);
	ResetMaterial();
}
