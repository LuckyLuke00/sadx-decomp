#include "decls.h"
extern float DAT_0629c508;
extern float DAT_0629c668;

// FUNCTION: SADX 0x0067e580
void njClipZ(float param_1, float param_2)
{
	if (param_1 > -1.0f)
	{
		param_1 = -1.0f;
	}
	if (param_1 < -65535.0f)
	{
		param_1 = -65535.0f;
	}
	if (param_2 > -1.0f)
	{
		param_2 = -1.0f;
	}
	if (param_2 < -65535.0f)
	{
		param_2 = -65535.0f;
	}
	DAT_0629c508 = -param_1;
	DAT_0629c668 = -param_2;
}
