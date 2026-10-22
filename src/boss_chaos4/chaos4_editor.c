#include "decls.h"
extern unsigned char DAT_060c2144;
extern unsigned char DAT_060c2145;

// FUNCTION: SADX 0x006f0320
void TubeCounterInit()
{
	DAT_060c2145 = 0;
	DAT_060c2144 = 0;
}

// FUNCTION: SADX 0x006f0330
void TubeCountUp()
{
	DAT_060c2144++;
}

// FUNCTION: SADX 0x006f0340
void TubeCountDown()
{
	DAT_060c2144--;
}

// FUNCTION: SADX 0x006f0350
int TubeCountGet()
{
	return DAT_060c2144;
}

// FUNCTION: SADX 0x006f0360
void HamonCountUp()
{
	DAT_060c2145++;
}

// FUNCTION: SADX 0x006f0370
void HamonCountDown()
{
	DAT_060c2145--;
}

// FUNCTION: SADX 0x006f0380
int HamonCountGet()
{
	return DAT_060c2145;
}
