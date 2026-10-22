#include "decls.h"
extern int DAT_060b55f0;
extern int DAT_060b55f4;

// FUNCTION: SADX 0x0067c9c0
void chSetBillboardBlendNormal(void)
{
	DAT_060b55f4 = 0;
}

// FUNCTION: SADX 0x0067c9d0
void chResetBillboardColor(void)
{
	DAT_060b55f0 = -1;
}
