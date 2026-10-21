#include "decls.h"
#include <stdlib.h>

// GLOBAL: SADX 0x02c0cb1c
static struct particle_info land_smoke;
float njCos(int param_1);
float njSin(int param_1);
void CreateAddSmoke(struct particle_info *effect);

// FUNCTION: SADX 0x007071f0
void SetE101HoverSmoke(struct taskwk *pTaskWk, float fGroundY)
{
	float var1 = pTaskWk->pos.y - fGroundY;
	int var2 = pTaskWk->ang.y;
	float local_c = njCos(var2) * -10.0;
	float local_8 = njSin(var2) * -10.0;
	float local_18;
	if (var1 > 0.0f && var1 < 30.0)
	{
		local_18 = rand() * 0.000030517578125;
		var2 = (int)(local_18 * 360.0 * 65536.0 / 360.0);
		var1 = (21.0 - var1) * 0.25;
		land_smoke.scl = var1 * 0.10000000149011612 + 0.5;
		land_smoke.pos.x = pTaskWk->pos.x + local_c + njCos(var2) * 7.0;
		land_smoke.pos.y = fGroundY + 1.5;
		land_smoke.pos.z = pTaskWk->pos.z + local_8 + njSin(var2) * 7.0;
		local_18 = rand() * 0.000030517578125;
		land_smoke.velo.x = (local_18 - 0.5) * var1;
		land_smoke.velo.y = 0.0f;
		local_18 = rand() * 0.000030517578125;
		land_smoke.velo.z = (local_18 - 0.5) * var1;
		CreateAddSmoke(&land_smoke);
	}
}
