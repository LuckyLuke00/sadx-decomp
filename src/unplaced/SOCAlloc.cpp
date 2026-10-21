#include "decls.h"
#include <stdlib.h>

// FUNCTION: SADX 0x004337a0
void *_SOCMalloc(unsigned int param_1, const char *param_2, int param_3)
{
	return malloc(param_1);
}

// FUNCTION: SADX 0x004337c0
void _SOCFree(void *param_1, const char *param_2, int param_3)
{
	free(param_1);
}
