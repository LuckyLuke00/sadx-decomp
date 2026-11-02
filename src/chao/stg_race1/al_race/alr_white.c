#include "decls.h"
extern struct DAT_05b35c40 *DAT_05b35c40;

// FUNCTION: SADX 0x004898a0
void AlrWhite_Out(int nCount)
{
	struct DAT_05b35c40 *var1;
	struct DAT_05b35c40 *var2;

	var1 = DAT_05b35c40;
	if (var1 != 0)
	{
		var2 = *(struct DAT_05b35c40 **)((char *)var1 + 0x20);
		if (nCount > 0)
		{
			*(char *)var2 = 2;
			*(float *)((char *)var2 + 0x30) = (1.0f - *(float *)((char *)var2 + 0x2c)) / (float)nCount;
		}
		else
		{
			*(char *)var2 = 2;
			*(float *)((char *)var2 + 0x30) = 1.0f - *(float *)((char *)var2 + 0x2c);
		}
	}
}
