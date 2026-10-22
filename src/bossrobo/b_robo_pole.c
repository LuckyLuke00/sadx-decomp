#include "decls.h"
void initPole(struct task *pTask);
extern int DAT_060bd19c;

// STUB: SADX 0x006e0f00
void PoleSet_Death()
{
}

// FUNCTION: SADX 0x006e11f0
void destPole(struct task *pTask)
{
	DAT_060bd19c = 0;
}

// FUNCTION: SADX 0x006e1770
void PoleSet_Init()
{
	if (DAT_060bd19c != 0)
	{
		*(int *)((char *)DAT_060bd19c + 0x10) = (int)initPole;
	}
}
