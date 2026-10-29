#include <string.h>

#include "decls.h"

void *_SOCMalloc(unsigned int param_1, const char *param_2, int param_3);
void _SOCFree(void *param_1, const char *param_2, int param_3);

// FUNCTION: SADX 0x0042b3b0
void *syMalloc(unsigned int nbytes)
{
	return _SOCMalloc(nbytes, "..\\src\\shinobi\\sg_maloc.c", 209);
}

// FUNCTION: SADX 0x0042b3d0
void *syCalloc(unsigned int nobj, unsigned int size)
{
	unsigned int var1 = nobj * size;
	void *var2;
	var2 = _SOCMalloc(var1, "..\\src\\shinobi\\sg_maloc.c", 288);
	memset(var2, 0, var1);
	return var2;
}

// FUNCTION: SADX 0x0042b400
void syFree(void *ap)
{
	if (ap != 0)
	{
		_SOCFree(ap, "..\\src\\shinobi\\sg_maloc.c", 334);
	}
}
