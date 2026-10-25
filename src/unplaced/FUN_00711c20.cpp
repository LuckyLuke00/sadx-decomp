#include "decls.h"
extern int DAT_060c6120;
extern int DAT_060c6124;
extern int DAT_060c6128;
extern int DAT_060c612c;

// FUNCTION: SADX 0x00711c50
void FUN_00711c50(int param_1, int param_2, int param_3, int param_4)
{
	DAT_060c6120 = param_1;
	DAT_060c6124 = param_2;
	DAT_060c6128 = param_3;
	DAT_060c612c = param_4;
}
