#include "decls.h"
extern void syFree(void *param_1);
extern void *DAT_05edf79c;

// FUNCTION: SADX 0x0061fb00
void saito_exit()
{
	syFree(DAT_05edf79c);
}
