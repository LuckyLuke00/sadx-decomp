#include <math.h>
#include "decls.h"

extern int DAT_05b9328c;
extern int DAT_05b93290;
extern int DAT_05b93294;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;

void njPushMatrix(float *m);
void njRotateZ(float *m, int ang);
void njCalcVector(float *m, struct NJS_POINT3 *v, struct NJS_POINT3 *out);
void FUN_0067d2d0(float *m, float x, float y, float z);
void njPopMatrix(int n);

// FUNCTION: SADX 0x004c3560
void FUN_004c3560()
{
	int angle;

	if (DAT_05b9328c > 0)
	{
		float scale;
		struct NJS_POINT3 tmp;
		struct NJS_POINT3 verts[3] = { { -5.0f, -5.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }, { 5.0f, -5.0f, 0.0f } };
		unsigned long rgb[3];
		struct NJS_POINT2 sp[3];
		struct NJS_POINT2COL info;

		angle = (int)(atan2((double)DAT_05b93290, (double)DAT_05b93294) * 65536.0 / 6.283184);
		info.p = sp;
		info.col = (union NJS_COLOR *)rgb;
		info.num = 3;
		njPushMatrix(_nj_unit_matrix_);
		if ((angle & 0xffff) != 0)
		{
			njRotateZ(0, (unsigned short)(angle & 0xffff));
		}
		scale = DAT_05b9328c / 32.0;
		if (scale < 1.0)
		{
			scale = 1.0f;
		}
		if (scale > 3.0)
		{
			scale = 3.0f;
		}
		FUN_0067d2d0(0, scale, scale, scale);
		njCalcVector(0, &verts[0], &tmp);
		sp[0].x = tmp.x + DAT_0629c6ec;
		sp[0].y = tmp.y + DAT_0629c6f0;
		rgb[0] = 0xf00000f0;
		njCalcVector(0, &verts[1], &tmp);
		sp[1].x = tmp.x + DAT_0629c6ec;
		sp[1].y = tmp.y + DAT_0629c6f0;
		rgb[1] = 0x8000ff00;
		njCalcVector(0, &verts[2], &tmp);
		sp[2].x = tmp.x + DAT_0629c6ec;
		sp[2].y = tmp.y + DAT_0629c6f0;
		rgb[2] = 0xf00000f0;
		njPopMatrix(1);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		njDrawTriangle2D(&info, 1, -1.0f, 0x60);
	}
}
