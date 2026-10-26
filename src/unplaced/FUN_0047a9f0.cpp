#include "decls.h"
extern void *DAT_05b330e4;

// FUNCTION: SADX 0x0047a9f0
void FUN_0047a9f0()
{
	if (DAT_05b330e4)
	{
		if (*(int **)((char *)DAT_05b330e4 + 0x34))
		{
			(*(void (**)(void *))((char *)DAT_05b330e4 + 0x34))(DAT_05b330e4);
		}
	}
}
