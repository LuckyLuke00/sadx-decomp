#include "decls.h"

extern struct NJS_POINT3 *DAT_060c453c;
extern struct NJS_POINT3 DAT_060c4544;
float njSqrt(float param_1);
float ghUnitVector(const struct NJS_POINT3 *r4, struct NJS_POINT3 *r5);
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);

// FUNCTION: SADX 0x00707080
static __declspec(safebuffers) void CameraE101Tgt(struct _OBJ_CAMERAPARAM *pParam)
{
	struct taskwk *local_14 = (struct taskwk *)DAT_05baf368;
	struct NJS_POINT3 local_10;
	struct NJS_POINT3 *local_18;
	float local_4;
	*(float *)((char *)camcont_wp + 0xc) = DAT_060c4544.x;
	*(float *)((char *)camcont_wp + 0x10) = DAT_060c4544.y;
	local_18 = DAT_060c453c;
	*(float *)((char *)camcont_wp + 0x14) = DAT_060c4544.z;
	local_10.x = local_18->x - local_14->pos.x;
	local_10.y = local_18->y - local_14->pos.y;
	local_10.z = local_18->z - local_14->pos.z;
	local_10.x *= 0.5;
	local_10.y *= 0.5;
	local_10.z *= 0.5;
	local_4 = local_10.y * local_10.y + local_10.x * local_10.x + local_10.z * local_10.z;
	if (njSqrt(local_4) >= 40.0f)
	{
		ghUnitVector(&local_10, &local_10);
		local_10.x *= 40.0;
		local_10.y *= 40.0;
		local_10.z *= 40.0;
	}
	*(float *)((char *)camcont_wp + 0x18) = local_14->pos.x + local_10.x;
	*(float *)((char *)camcont_wp + 0x1c) = local_14->pos.y + local_10.y;
	*(float *)((char *)camcont_wp + 0x20) = local_14->pos.z + local_10.z;
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
