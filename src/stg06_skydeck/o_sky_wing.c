#include "decls.h"
extern short DAT_05b9d744;
extern float DAT_060d0da0;
extern float DAT_060d0da4;

// STUB: SADX 0x0083f690
int SkydeckCheck_break(float posx, float posy, float posz)
{
	if (*(char *)&DAT_05b9d744 != 1)
	{
		return 0;
	}
	if (posz < 0.0f)
	{
		return 0;
	}
	if (posx > DAT_060d0da4)
	{
		return 0;
	}
	if (posy > DAT_060d0da0)
	{
		return 0;
	}
	return 1;
}
