#include "decls.h"
extern unsigned char DAT_05ad95e0;
extern int DAT_04c7c0c0;
long FUN_00423db0(const char *param_1, struct NJS_TEXLIST *param_2);

// FUNCTION: SADX 0x00423db0
long FUN_00423db0(const char *param_1, struct NJS_TEXLIST *param_2)
{
	char var1[256];
	int var2;

	var2 = param_1 != 0;
	var2 = var2 & (param_2 != 0);
	if (var2)
	{
		_njCheckFileName(var1, param_1, ".pvm");
		Sint8 *var3 = njOpenBinary(var1);
		DAT_05ad95e0 = 1;
		long var4 = njLoadTexturePvmMemory((unsigned char *)var3, param_2);
		DAT_05ad95e0 = 0;
		njCloseBinary(var3);
		return var4;
	}
	return -1;
}

// FUNCTION: SADX 0x00423e50
long FUN_00423e50(const char *param_1, struct NJS_TEXLIST *param_2)
{
	return FUN_00423db0(param_1, param_2);
}
