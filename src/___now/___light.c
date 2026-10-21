#include "decls.h"
void lig_calcPalette(int no);
void FUN_00598720(int param_1);
void FUN_00405380(int param_1);
void FUN_00598740(int);

// STUB: SADX 0x00597f10
void dsReScaleLight()
{
}

// STUB: SADX 0x00597f60
void lig_setLight4gjpalNo(int c)
{
}

// FUNCTION: SADX 0x00597f90
void FUN_00597f90()
{
	lig_calcPalette(0);
	lig_calcPalette(2);
	lig_calcPalette(4);
	lig_calcPalette(6);
	FUN_00405380(0);
}

// FUNCTION: SADX 0x00597fd0
void lig_resetGjPaletteNo(int no)
{
	FUN_00598720((no & 0x7f) >> 1);
}

// STUB: SADX 0x00598890
void lig_flashPalette(int no)
{
}

// FUNCTION: SADX 0x005988f0
void FUN_005988f0()
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
	{
		FUN_00598740(local_8);
	}
}

// STUB: SADX 0x00598920
void lig_fillOffsetPalette(int no, unsigned long spe, int num)
{
}

// STUB: SADX 0x00598b00
void lig_convHalfBrightPalette(int no, float rate)
{
}
