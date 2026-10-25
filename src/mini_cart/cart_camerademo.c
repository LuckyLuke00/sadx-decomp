#include "decls.h"
extern struct NJS_POINT3 DAT_060e0178;
extern short DAT_05b9d744;
extern long data_ele[6];
extern struct NJS_POINT3 *CartCamDemoLine;
extern struct NJS_POINT3 *DAT_05b4292c;
extern struct NJS_POINT3 *DAT_05b42930;
extern int DAT_05ccdbe0;
void CartRacePrepareRace();

// FUNCTION: SADX 0x007e4f80
void cartCameraDemoCheckrer(struct task *tp)
{
	if (DAT_05ccdbe0 == 0)
	{
		FreeTask(tp);
		CartRacePrepareRace();
	}
}

// FUNCTION: SADX 0x007e4fa0
void SetCartCameraDemo()
{
	short var1 = DAT_05b9d744;
	int var2 = var1 & 0xff;
	CreateElementalTask(2, 3, cartCameraDemoCheckrer);
	CameraSetEventCamera(0x31, 0);
	long var3 = OpenCartSplineData((void *)((char *)CartCamDemoLine + var2 * 0x1e0), data_ele[var2]);
	DAT_05ccdbe0 = 1;
	DAT_05b4292c = &DAT_060e0178;
	DAT_05b42930 = (struct NJS_POINT3 *)(var3 - 0x3c);
}
