#include "decls.h"
extern float DAT_05ad95e4;
extern void *DAT_05ad95e8;
extern void gjPrintInit(void *,unsigned long,unsigned long);
extern int DAT_05ad95ec;

// FUNCTION: SADX 0x00423e60
void njInitPrint(unsigned long *texture, unsigned long size, unsigned long attr)
{
	DAT_05ad95e4 = 8.0f;
	DAT_05ad95ec = 0xffbfbfbf;
	DAT_05ad95e8 = syMalloc(0x1000);
	gjPrintInit(DAT_05ad95e8, 0x80, 0x800);
}

// FUNCTION: SADX 0x00423ea0
void njExitPrint(void)
{
	gjPrintExit();
}

// FUNCTION: SADX 0x00423eb0
void njPrintSize(unsigned short size)
{
	DAT_05ad95e4 = (float)size;
}

// FUNCTION: SADX 0x00423ed0
void njPrintColor(unsigned long c)
{
	DAT_05ad95ec = c;
}

// STUB: SADX 0x00423ee0
void njPrintC(int loc, char const *s)
{
}

// STUB: SADX 0x00424080
void njPrintH(int loc, unsigned long val, int digit)
{
}

// STUB: SADX 0x004240e0
void njPrintF(int loc, float val, int digit)
{
}
