#include "decls.h"
extern signed char DAT_05b37365;
extern signed char DAT_05b37368;
extern signed char DAT_05b37369;
extern signed char DAT_05b3736a;
extern unsigned char DAT_05b3733c;
extern unsigned char DAT_05b3733d;
extern unsigned char DAT_05b3733e;
extern unsigned char DAT_05b3733f;

// FUNCTION: SADX 0x00499380
void StartNumDisplay(unsigned char u8ID, unsigned char u8Num)
{
	DAT_05b3733c = 2;
	DAT_05b3733d = u8Num;
	DAT_05b3733e = 0;
	DAT_05b3733f = u8ID;
}

// FUNCTION: SADX 0x004993b0
void SetMiTimer(signed char s8Min, signed char s8Sec, signed char s8Frm)
{
	if (DAT_05b37365 == 0)
	{
		DAT_05b37368 = s8Min;
		DAT_05b37369 = s8Sec;
		DAT_05b3736a = s8Frm;
	}
}

// FUNCTION: SADX 0x004993e0
unsigned char GetMiTimerStatus()
{
	return DAT_05b37365;
}

// FUNCTION: SADX 0x004993f0
void AppearMiTimer()
{
	DAT_05b37365 = 1;
}
