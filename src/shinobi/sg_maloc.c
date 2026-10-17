#include <string.h>

void *FUN_004337a0(unsigned int size, const char *file, int line);
void FUN_004337c0(void *p, const char *file, int line);

// FUNCTION: SADX 0x0042b3b0
void *syMalloc(unsigned int size)
{
	return FUN_004337a0(size, "..\\src\\shinobi\\sg_maloc.c", 209);
}

// FUNCTION: SADX 0x0042b3d0
void *syCalloc(unsigned int count, unsigned int size)
{
	unsigned int total = count * size;
	void *p;
	p = FUN_004337a0(total, "..\\src\\shinobi\\sg_maloc.c", 288);
	memset(p, 0, total);
	return p;
}

// FUNCTION: SADX 0x0042b400
void syFree(void *p)
{
	if (p != 0)
	{
		FUN_004337c0(p, "..\\src\\shinobi\\sg_maloc.c", 334);
	}
}
