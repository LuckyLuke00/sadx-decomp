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

// FUNCTION: SADX 0x0067c9e0
void chSetBillboardColor(float param_1, float param_2, float param_3, float param_4)
{
	unsigned int local_4;
	unsigned char local_8;
	local_4 = (unsigned int)(param_1 * 255.0);
	local_8 = (unsigned char)local_4;
	*(unsigned char *)((char *)&DAT_060b55f0 + 3) = local_8;
	local_4 = (unsigned int)(param_2 * 255.0);
	*(unsigned char *)((char *)&DAT_060b55f0 + 2) = (unsigned char)local_4;
	local_4 = (unsigned int)(param_3 * 255.0);
	*(unsigned char *)((char *)&DAT_060b55f0 + 1) = (unsigned char)local_4;
	local_4 = (unsigned int)(param_4 * 255.0);
	*(unsigned char *)((char *)&DAT_060b55f0 + 0) = (unsigned char)local_4;
}
