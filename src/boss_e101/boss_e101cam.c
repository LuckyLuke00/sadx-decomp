#include "decls.h"
#include "../ghmath.h"

extern struct NJS_POINT3 *DAT_060c453c;
extern struct NJS_POINT3 DAT_060c4544;
float njSqrt(float param_1);
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);

// FUNCTION: SADX 0x00707080
static void CameraE101Tgt(struct _OBJ_CAMERAPARAM *pParam)
{
	struct taskwk *var1 = DAT_05baf368[0];
	struct NJS_POINT3 vec;
	struct NJS_POINT3 *var2;
	float local_18;
	*(float *)((char *)camcont_wp + 0xc) = DAT_060c4544.x;
	*(float *)((char *)camcont_wp + 0x10) = DAT_060c4544.y;
	var2 = DAT_060c453c;
	*(float *)((char *)camcont_wp + 0x14) = DAT_060c4544.z;
	vec.x = var2->x - var1->pos.x;
	vec.y = var2->y - var1->pos.y;
	vec.z = var2->z - var1->pos.z;
	vec.x *= 0.5;
	vec.y *= 0.5;
	vec.z *= 0.5;
	local_18 = vec.y * vec.y + vec.x * vec.x + vec.z * vec.z;
	if (njSqrt(local_18) >= 40.0f)
	{
		ghUnitVector(&vec, &vec);
		vec.x *= 40.0;
		vec.y *= 40.0;
		vec.z *= 40.0;
	}
	*(float *)((char *)camcont_wp + 0x18) = var1->pos.x + vec.x;
	*(float *)((char *)camcont_wp + 0x1c) = var1->pos.y + vec.y;
	*(float *)((char *)camcont_wp + 0x20) = var1->pos.z + vec.z;
}

// FUNCTION: SADX 0x007071b0
void StartCameraE101_Tgt(struct NJS_POINT3 *pTgtPos, struct NJS_POINT3 *pEyePos)
{
	DAT_060c453c = pTgtPos;
	DAT_060c4544.x = pEyePos->x;
	DAT_060c4544.y = pEyePos->y;
	DAT_060c4544.z = pEyePos->z;
	CameraSetEventCameraFunc(CameraE101Tgt, 0, 2);
}
