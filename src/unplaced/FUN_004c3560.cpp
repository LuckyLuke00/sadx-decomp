#include <math.h>
#include "decls.h"

extern int DAT_05b9328c;
extern int DAT_05b93290;
extern int DAT_05b93294;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;

void njPushMatrix(float *param_1);
void njRotateZ(float *param_1, int param_2);
void njCalcVector(float *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void njPopMatrix(int param_1);

// FUNCTION: SADX 0x004c3560
void FUN_004c3560()
{
	int local_8;

	if (DAT_05b9328c > 0)
	{
		float local_28r;
		struct NJS_POINT3 local_34p;
		struct NJS_POINT3 local_58g[3] = { { -5.0f, -5.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }, { 5.0f, -5.0f, 0.0f } };
		unsigned long local_64[3];
		struct NJS_POINT2 local_24s[3];
		struct NJS_POINT2COL local_74;

		local_8 = (int)(atan2((double)DAT_05b93290, (double)DAT_05b93294) * 65536.0 / 6.283184);
		local_74.p = local_24s;
		local_74.col = (union NJS_COLOR *)local_64;
		local_74.num = 3;
		njPushMatrix(_nj_unit_matrix_);
		if ((local_8 & 0xffff) != 0)
		{
			njRotateZ(0, (unsigned short)(local_8 & 0xffff));
		}
		local_28r = DAT_05b9328c / 32.0;
		if (local_28r < 1.0)
		{
			local_28r = 1.0f;
		}
		if (local_28r > 3.0)
		{
			local_28r = 3.0f;
		}
		FUN_0067d2d0(0, local_28r, local_28r, local_28r);
		njCalcVector(0, &local_58g[0], &local_34p);
		local_24s[0].x = local_34p.x + DAT_0629c6ec;
		local_24s[0].y = local_34p.y + DAT_0629c6f0;
		local_64[0] = 0xf00000f0;
		njCalcVector(0, &local_58g[1], &local_34p);
		local_24s[1].x = local_34p.x + DAT_0629c6ec;
		local_24s[1].y = local_34p.y + DAT_0629c6f0;
		local_64[1] = 0x8000ff00;
		njCalcVector(0, &local_58g[2], &local_34p);
		local_24s[2].x = local_34p.x + DAT_0629c6ec;
		local_24s[2].y = local_34p.y + DAT_0629c6f0;
		local_64[2] = 0xf00000f0;
		njPopMatrix(1);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		njDrawTriangle2D(&local_74, 1, -1.0f, 0x60);
	}
}
