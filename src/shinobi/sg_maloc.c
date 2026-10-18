#include <string.h>

#include "decls.h"

void *_SOCMalloc(unsigned int size, const char *file, int line);
void _SOCFree(void *p, const char *file, int line);

// FUNCTION: SADX 0x0042b3b0
void *syMalloc(unsigned int size)
{
	return _SOCMalloc(size, "..\\src\\shinobi\\sg_maloc.c", 209);
}

// FUNCTION: SADX 0x0042b3d0
void *syCalloc(unsigned int count, unsigned int size)
{
	unsigned int total = count * size;
	void *p;
	p = _SOCMalloc(total, "..\\src\\shinobi\\sg_maloc.c", 288);
	memset(p, 0, total);
	return p;
}

// FUNCTION: SADX 0x0042b400
void syFree(void *p)
{
	if (p != 0)
	{
		_SOCFree(p, "..\\src\\shinobi\\sg_maloc.c", 334);
	}
}
