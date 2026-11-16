#include "decls.h"
extern struct _OBJ_LANDENTRY objLandEntry[];

// FUNCTION: SADX 0x00497210
void SetClip_0500(int ClipLevel)
{
	int var1;
	if (ClipLevel > 0)
	{
		for (var1 = 283; var1 <= 470; var1++)
		{
			objLandEntry[var1].slAttribute &= 0x7fffffff;
		}
	}
}
