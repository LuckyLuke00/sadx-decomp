#include "decls.h"
#include <stdlib.h>

// FUNCTION: SADX 0x005d8bf0
void CreateAnimal(short e_num, float xpos, float ypos, float zpos)
{
	int local_8g;
	float local_14h;
	int local_10m;
	float local_cj;
	short local_18;
	local_18 = (short)(DAT_05b9d724 | ((short)DAT_05b9d744 >> 8));
	local_8g = rand();
	local_14h = (float)local_8g / 32768.0f;
	if (local_14h < 0.1f)
	{
		local_18 = 4;
	}
	else
	{
		local_10m = rand();
		local_cj = (float)local_10m / 32768.0f;
		local_18 = (short)(local_cj * 3.99f);
	}
	Flicky_Create(xpos, ypos, zpos, animal[(local_18 & 0xff) * 5 + (short)local_18]);
}

// FUNCTION: SADX 0x005d8cc0
void CreateRareAnimal(float xpos, float ypos, float zpos)
{
	unsigned short local_8;
	local_8 = (unsigned short)((short)DAT_05b9d724 | (short)DAT_05b9d744);
	Flicky_Create(xpos, ypos, zpos, animal[(int)MinimalList[local_8 >> 8 & 0xff][4]]);
}
