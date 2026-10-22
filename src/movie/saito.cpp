#include "decls.h"
extern void syFree(void *param_1);
extern void *DAT_05edf79c;

// STUB: SADX 0x0061f920
void saito_initX(struct CMoviePolyTag *tagp)
{
}

// FUNCTION: SADX 0x0061fb00
void saito_exit()
{
	syFree(DAT_05edf79c);
}
