#include "decls.h"
#include <stdlib.h>

// FUNCTION: SADX 0x005d8bf0
void CreateAnimal(short e_num, float xpos, float ypos, float zpos)
{
	unsigned short local_8gk;
	unsigned short local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;
	local_ci = (unsigned short)(((DAT_05b9d724 << 8 | DAT_05b9d744) >> 8) & 0xff);
	local_10hk = rand();
	local_14k = (float)(local_10hk / 32768.0);
	if (local_14k < 0.10000000149011612)
	{
		local_8gk = 4;
	}
	else
	{
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_8gk = (unsigned short)(local_1co * 3.990000009536743);
	}
	Flicky_Create(xpos, ypos, zpos, animal[MinimalList[local_ci][local_8gk]]);
}

// FUNCTION: SADX 0x005d8cc0
void CreateRareAnimal(float xpos, float ypos, float zpos)
{
	unsigned short local_8;
	local_8 = (unsigned short)(((DAT_05b9d724 << 8 | DAT_05b9d744) >> 8) & 0xff);
	Flicky_Create(xpos, ypos, zpos, animal[(int)MinimalList[local_8][4]]);
}
