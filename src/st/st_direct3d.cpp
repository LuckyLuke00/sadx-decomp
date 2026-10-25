#include "decls.h"
void FUN_00426740(void);
void FUN_00426820(void);
extern int DAT_0629c6c8;
extern int DAT_05ab6ea0;
struct _sSTVERTEXSTREAM;
extern char DAT_05ab46c0[64];
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
	char *var1;

	var1 = (char *)&DAT_05ab46c0;
	do
	{
		stVSRelease((struct _sSTVERTEXSTREAM *)var1);
		var1 += 0x24;
	}
	while (var1 != (char *)0x5ab4804);
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

// FUNCTION: SADX 0x004273a0
void stDrawModel(long *param_1, short *param_2)
{
	stPreCalcMatrix();
	if (param_1 != 0)
	{
		FUN_00426580((int)param_1);
		int var1 = DAT_0629c6c8;
		if ((var1 & 0x10) != 0)
		{
			FUN_00426740();
			DAT_05ab6ea0 = DAT_05ab6ea0 | 0x200;
		}
		else if ((var1 & 0x20) != 0)
		{
			FUN_00426820();
			DAT_05ab6ea0 = DAT_05ab6ea0 | 0x200;
		}
		else
		{
			DAT_05ab6ea0 = DAT_05ab6ea0 & 0xfffffdff;
		}
	}
	if (param_2 != 0)
	{
		stDrawPlist(param_2);
	}
}
