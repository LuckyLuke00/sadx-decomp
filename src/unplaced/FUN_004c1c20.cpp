#include "decls.h"

extern int DAT_05b92e24;
extern struct NJS_TEXLIST DAT_05b42c40[32];

// FUNCTION: SADX 0x004c1c20
void FUN_004c1c20()
{
	int i;

	for (i = 0; i < DAT_05b92e24; i++)
	{
		if (DAT_05b42c40[i].textures != 0)
		{
			__try
			{
				late_ReleaseTexture(&DAT_05b42c40[i]);
				DAT_05b42c40[i].textures = 0;
				DAT_05b42c40[i].nbTexture = 0;
			}
			__except (1)
			{
			}
		}
	}
	DAT_05b92e24 = 0;
}
