#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x004333e0
void njTranslateEx(void *v)
{
	float local_8;
	float var1;
	float local_c;
	float *var2;

	local_8 = *(float *)v;
	var1 = *(float *)((char *)v + 4);
	local_c = *(float *)((char *)v + 8);
	var2 = (float *)DAT_0629c518;
	var2[12] = var1 * var2[4] + local_8 * var2[0] + local_c * var2[8] + var2[12];
	var2[13] = var2[5] * var1 + var2[1] * local_8 + var2[9] * local_c + var2[13];
	var2[14] = var2[6] * var1 + var2[2] * local_8 + var2[10] * local_c + var2[14];
	var2[15] = var2[7] * var1 + var2[3] * local_8 + var2[11] * local_c + var2[15];
}
