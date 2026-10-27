#include "decls.h"
extern int DAT_05ad9abc;
extern int DAT_05ad9ac0;
extern int DAT_05ad9ac4;
extern int DAT_05ad9ac8;

// FUNCTION: SADX 0x00430c40
void stOptionInit(void)
{
	DAT_05ad9abc = 0;
	DAT_05ad9ac0 = 0;
	DAT_05ad9ac4 = 0;
	DAT_05ad9ac8 = 0;
	FUN_007d21b0("CTRLFLAG0", &DAT_05ad9abc);
	FUN_007d21b0("CTRLFLAG1", &DAT_05ad9ac0);
	FUN_007d21b0("CTRLFLAG2", &DAT_05ad9ac4);
	FUN_007d21b0("CTRLFLAG3", &DAT_05ad9ac8);
}
