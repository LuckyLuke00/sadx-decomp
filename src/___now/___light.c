#include "decls.h"
extern char DAT_05cd4080[24612];
void lig_flashPalette(int no);
void lig_calcPalette(int no);
void FUN_00598720(int param_1);
void FUN_00405380(int param_1);
void FUN_00598740(int);

// STUB: SADX 0x00597ce0
void lig_setLight(struct NJS_POINT3 *v, float r, float g, float b, float spe, float dif, float amb)
{
}

// STUB: SADX 0x00597ea0
void dsScaleLight(float a)
{
}

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

#pragma optimize("", off)
// STUB: SADX 0x00598740
void FUN_00598740(int param_1)
{
}
#pragma optimize("", on)

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

// STUB: SADX 0x005989a0
void lig_cpyPalette(int dstNo, int srcNo)
{
}

// STUB: SADX 0x005989e0
void lig_supplementPalette(int no, int src1, int src2, float fmix1)
{
}

// FUNCTION: SADX 0x00598b00
void lig_convHalfBrightPalette(int no, float rate)
{
	int local_8g;
	int local_cg;
	for (local_8g = 0; local_8g < 256; local_8g++)
	{
		local_cg = *(int *)((char *)DAT_05cd4080 + (no << 11) + (local_8g << 1) * 4);
		*(int *)((char *)DAT_05cd4080 + (no << 11) + (local_8g << 1) * 4) = ((unsigned int)local_cg >> 1) & 0x7f7f7f | 0xff000000;
		*(int *)((char *)DAT_05cd4080 + (no << 11) + (local_8g << 1) * 4 + 4) = 0xff000000;
	}
}
