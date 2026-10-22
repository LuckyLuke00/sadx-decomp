#include "decls.h"
extern float DAT_05ad95e4;
extern void *DAT_05ad95e8;
extern void *syMalloc(unsigned int param_1);
extern void gjPrintInit(void *,unsigned long,unsigned long);
extern int DAT_05ad95ec;

// FUNCTION: SADX 0x00423e60
void njInitPrint(unsigned long *param_1, unsigned long param_2, unsigned long param_3)
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
void njPrintSize(unsigned short param_1)
{
	DAT_05ad95e4 = (float)param_1;
}

// FUNCTION: SADX 0x00423ed0
void njPrintColor(unsigned long param_1)
{
	DAT_05ad95ec = param_1;
}

// STUB: SADX 0x00424080
void njPrintH(int param_1, unsigned long param_2, int param_3)
{
}

// STUB: SADX 0x004240e0
void njPrintF(int param_1, float param_2, int param_3)
{
}
