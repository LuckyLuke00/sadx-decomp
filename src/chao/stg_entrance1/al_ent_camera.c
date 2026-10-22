#include "decls.h"
void AL_EntCameraFunc();
void CameraSetCollisionCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);
extern struct _camcontwk *camcont_wp;
extern float posy;
extern float posz;
extern long angx;

// FUNCTION: SADX 0x00472a90
void AL_EntCameraFunc()
{
	posz = posz - 0.05000000074505806;
	if (posz < -11.0)
	{
		posz = -11.0;
	}
	*(int *)((char *)camcont_wp + 0x24) = angx;
	*(int *)((char *)camcont_wp + 0x28) = 0;
	*(int *)((char *)camcont_wp + 0x2c) = 0;
	*(float *)((char *)camcont_wp + 0xc) = 0.0;
	*(float *)((char *)camcont_wp + 0x10) = posy;
	*(float *)((char *)camcont_wp + 0x14) = posz;
}

// FUNCTION: SADX 0x00472b10
void AL_EntCameraSet()
{
	CameraSetCollisionCameraFunc((void (__cdecl *)(_OBJ_CAMERAPARAM *))AL_EntCameraFunc, 1, 3);
	posy = 9.0f;
	angx = 0xfb00;
	posz = 5.0f;
}
