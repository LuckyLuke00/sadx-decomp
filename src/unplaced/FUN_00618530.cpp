#include "decls.h"
void FUN_004ff320(int param_1);
struct FlickyEff;

// FUNCTION: SADX 0x00618530
void FUN_00618530(struct FlickyEff *param_1, struct FlickyEff *param_2)
{
	if (*(short *)((char *)param_2 + 0xc) > 0x1e)
	{
		if ((*(unsigned short *)((char *)*(int *)((char *)param_2 + 0x38) + 4) & 1) != 0)
		{
			if (*(unsigned short *)((char *)*(int *)((char *)*(int *)((char *)param_2 + 0x38) + 0xa4)) == 0)
			{
				dsPlay_oneshot(0x1c, 0, 0, 0);
				if ((*(unsigned short *)((char *)param_2 + 6) & 0x40) != 0)
				{
					FUN_0061ea50((struct NJS_POINT3 *)((char *)param_2 + 0x20), *(unsigned short *)((char *)*(int *)((char *)param_1 + 0x68)));
				}
				FlickyEff_Particle_New((struct NJS_POINT3 *)((char *)param_2 + 0x20), *(unsigned short *)((char *)*(int *)((char *)param_1 + 0x68)), *(unsigned short *)((char *)param_2 + 6) & 8);
				if (*(unsigned char *)param_1 < 0xf)
				{
					FUN_004ff320(*(unsigned char *)param_1);
				}
				*(unsigned short *)((char *)param_2 + 6) = *(unsigned short *)((char *)param_2 + 6) | 0x8000;
			}
			else
			{
				if ((*(unsigned short *)((char *)*(int *)((char *)param_2 + 0x38) + 4) & 4) != 0)
				{
					BaloonScale_force((struct NJS_POINT3 *)((char *)param_1 + 0x20), 1);
				}
				else
				{
					BaloonScale_force((struct NJS_POINT3 *)((char *)param_1 + 0x20), 6);
				}
			}
		}
	}
}
