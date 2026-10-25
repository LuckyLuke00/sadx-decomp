#include "decls.h"
extern unsigned char DAT_05cd14e0;
extern int DAT_05cd14f8;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// FUNCTION: SADX 0x00573e40
void FUN_00573e40(void)
{
	memset((void *)&DAT_05cd14e0, 0, 0x12);
	DAT_05cd14f8 = 0;
}
