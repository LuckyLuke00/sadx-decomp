#include "decls.h"
extern char DAT_023b7114[20480];

// FUNCTION: SADX 0x00497210
void SetClip_0500(int ClipLevel)
{
	int *var1;
	if (ClipLevel > 0)
	{
		for (var1 = (int *)DAT_023b7114; (int)var1 <= (int)&DAT_023b7114[0x1a4c]; var1 += 9)
		{
			*var1 &= 0x7fffffff;
		}
	}
}
