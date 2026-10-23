#include "decls.h"
extern int DAT_060c20a8;
void start_demo_camera_water(struct _OBJ_CAMERAPARAM *pParam);
extern float DAT_060c20d4;
void start_demo_camera(struct _OBJ_CAMERAPARAM *pParam);
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_chaos4_object;
extern struct obj object_c4_s_sora_hare_s_sora_hare;
extern int DAT_060c20c4;

// FUNCTION: SADX 0x006ee2b0
void Chaos4CameraLookMe(struct NJS_POINT3 *pos)
{
	DAT_060c20c4 = (int)pos;
}

// STUB: SADX 0x006ee2c0
void chaos4_camera_angle_y_adjust()
{
}

// FUNCTION: SADX 0x006ee390
void Dsp_Air()
{
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_chaos4_object);
		Tmit_MaterialInit();
		njPushMatrix(0);
		___dsDrawObject(&object_c4_s_sora_hare_s_sora_hare);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x006ee590
void start_demo_camera(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x006ee630
void start_demo_camera_water(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x006ee8e0
void Chaos4StartDemoCameraSet()
{
	DAT_060c20d4 = 0.0f;
	CameraSetEventCameraFunc(start_demo_camera, 0, 2);
}

// FUNCTION: SADX 0x006ee900
void Chaos4StartDemoCameraSet2()
{
	DAT_060c20a8 = 0x1555;
	CameraSetEventCameraFunc(start_demo_camera_water, 0, 2);
}

// STUB: SADX 0x006eeac0
void chaos4_camera(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x006eeb40
void Chaos4_CameraTestSet(struct NJS_POINT3 *cam_int_pos)
{
}
