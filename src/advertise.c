#include "decls.h"
#include <math.h>
#include <new>
void FUN_00588890(int param_1);
extern unsigned char DAT_05cd2786;

// FUNCTION: SADX 0x0057cd20
void FUN_0057cd20()
{
	DAT_05cd2786 = 0;
}

// FUNCTION: SADX 0x00582ad0
float FUN_00582ad0(float param_1)
{
	float local_8;
	local_8 = (float)floor((double)param_1);
	return local_8;
}

// STUB: SADX 0x00582af0
void __fastcall FUN_00582af0(int param_1)
{
}

// STUB: SADX 0x00588890
void FUN_00588890(int param_1)
{
}

// STUB: SADX 0x005888f0
void * FUN_005888f0(void * param_1)
{
	return (void *)0;
}

// STUB: SADX 0x00588920
int FUN_00588920(struct NJS_POINT3 *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x005889a0
void FUN_005889a0(int param_1)
{
}

// STUB: SADX 0x005889f0
int FUN_005889f0(int *param_1)
{
	return (int)0;
}

// STUB: SADX 0x00588a10
int FUN_00588a10(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00588db0
void FUN_00588db0(struct obj *obj, int param_2)
{
}

// STUB: SADX 0x00589930
void FUN_00589930()
{
}

// STUB: SADX 0x0058a010
int FUN_0058a010(int *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0058a490
void FUN_0058a490(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0058a4b0
void FUN_0058a4b0(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0058a560
void *FUN_0058a560(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0058a5d0
void *FUN_0058a5d0(unsigned int param_1)
{
	return (void *)0;
}

// FUNCTION: SADX 0x0058a640
unsigned short * FUN_0058a640(unsigned short *param_1, unsigned short *param_2, unsigned short *param_3)
{
	for (; param_1 != param_2; param_1 = param_1 + 1)
	{
		if (*param_1 == *param_3)
			break;
	}
	return param_1;
}
