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
	int ang;

	if (DAT_05b9328c > 0)
	{
		float im1;
		struct NJS_POINT3 f;
		struct NJS_POINT3 ljth5i[3] = { { -5.0f, -5.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }, { 5.0f, -5.0f, 0.0f } };
		unsigned long poly[3];
		struct NJS_POINT2 y[3];
		struct NJS_POINT2COL cov;

		ang = (int)(atan2((double)DAT_05b93290, (double)DAT_05b93294) * 65536.0 / 6.283184);
		cov.p = y;
		cov.col = (union NJS_COLOR *)poly;
		cov.num = 3;
		njPushMatrix(_nj_unit_matrix_);
		if ((ang & 0xffff) != 0)
		{
			njRotateZ(0, (unsigned short)(ang & 0xffff));
		}
		im1 = DAT_05b9328c / 32.0;
		if (im1 < 1.0)
		{
			im1 = 1.0f;
		}
		if (im1 > 3.0)
		{
			im1 = 3.0f;
		}
		FUN_0067d2d0(0, im1, im1, im1);
		njCalcVector(0, &ljth5i[0], &f);
		y[0].x = f.x + DAT_0629c6ec;
		y[0].y = f.y + DAT_0629c6f0;
		poly[0] = 0xf00000f0;
		njCalcVector(0, &ljth5i[1], &f);
		y[1].x = f.x + DAT_0629c6ec;
		y[1].y = f.y + DAT_0629c6f0;
		poly[1] = 0x8000ff00;
		njCalcVector(0, &ljth5i[2], &f);
		y[2].x = f.x + DAT_0629c6ec;
		y[2].y = f.y + DAT_0629c6f0;
		poly[2] = 0xf00000f0;
		njPopMatrix(1);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		njDrawTriangle2D(&cov, 1, -1.0f, 0x60);
	}
}
