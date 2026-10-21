#include "decls.h"
extern int DAT_06298cac;
extern int DAT_05cc3fe0;
extern int DAT_05cc3ff0;
extern int DAT_05cc4000;
extern int DAT_05cc4010;
extern int DAT_05cc4020;

// FUNCTION: SADX 0x0050d320
void _bigmot_init()
{
	DAT_05cc3fe0 = *(int *)(DAT_06298cac + 0x10);
	DAT_05cc3ff0 = *(int *)(DAT_06298cac + 0x10);
	DAT_05cc4000 = *(int *)(DAT_06298cac + 0x74);
	DAT_05cc4020 = *(int *)(DAT_06298cac + 0x78);
	DAT_05cc4010 = DAT_05cc4020;
}
