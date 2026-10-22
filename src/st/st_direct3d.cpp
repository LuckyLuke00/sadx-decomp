#include "decls.h"
extern int DAT_05ab7c00;
extern void (*DAT_01c77460[256])(int);
extern int DAT_05ab45e0;

// STUB: SADX 0x00426520
void stFinishVertex(void)
{
}

// FUNCTION: SADX 0x00426570
void stSetQuadColor(unsigned long param_1)
{
	DAT_05ab45e0 = param_1;
}

// FUNCTION: SADX 0x00426580
void FUN_00426580(int param_1)
{
	int var2;

	while ((var2 = *(int *)param_1, (var2 & 0xffff) != 0xff))
	{
		if ((var2 & 0x8000) == 0)
		{
			DAT_05ab7c00 = 0;
		}
		DAT_01c77460[*(int *)param_1 & 0xff](param_1);
		param_1 += *(short *)(param_1 + 2) * 4 + 4;
	}
}

// STUB: SADX 0x00426980
void FUN_00426980(void)
{
}

// STUB: SADX 0x004269a0
void FUN_004269a0(void)
{
}

// STUB: SADX 0x00427210
void _stSetChunkMaterialD(unsigned long *param_1)
{
}

// STUB: SADX 0x00427230
void _stSetChunkMaterialA(unsigned long *param_1)
{
}

// STUB: SADX 0x00427250
void _stSetChunkMaterialDA(unsigned long *param_1)
{
}

// STUB: SADX 0x00427270
void _stSetChunkMaterialS(unsigned long *param_1)
{
}

// STUB: SADX 0x00427290
void _stSetChunkMaterialDS(unsigned long *param_1)
{
}

// STUB: SADX 0x004272b0
void _stSetChunkMaterialAS(unsigned long *param_1)
{
}

// STUB: SADX 0x004272d0
void _stSetChunkMaterialDAS(unsigned long *param_1)
{
}

// STUB: SADX 0x004272f0
void FUN_004272f0(void)
{
}

// STUB: SADX 0x004273a0
void stDrawModel(long *param_1, short *param_2)
{
}
