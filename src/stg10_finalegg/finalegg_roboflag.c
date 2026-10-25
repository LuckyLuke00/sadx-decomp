#include "decls.h"
extern int DAT_060dd080[16];

// FUNCTION: SADX 0x00891090
void FinalEggClearAppearZERO()
{
	int var1;
	for (var1 = 0; var1 < 16; var1++)
		DAT_060dd080[var1] = 0;
}

// FUNCTION: SADX 0x008910f0
long FinalEggCheckAppearZERO(long no)
{
	return DAT_060dd080[no];
}

// FUNCTION: SADX 0x00891100
void FinalEggSetAppearZERO(long no)
{
	DAT_060dd080[no] = 1;
}
