#include "decls.h"
extern void *DAT_06276c40;

// FUNCTION: SADX 0x006e6a90
void changeHeadColorChaos0(int flag)
{
	void *var1 = *(void **)((char *)DAT_06276c40 + 0x18);
	void *var2 = *(void **)((char *)var1 + 4);
	void *var3 = *(void **)((char *)var2 + 0x10);
	if (flag & 1)
	{
		*(int *)((char *)var3 + 0x10) = (*(int *)((char *)var3 + 0x10) & 0x1fffffff) | 0x20000000;
		return;
	}
	*(int *)((char *)var3 + 0x10) = 0x94718400;
}

// STUB: SADX 0x006e6ac0
void __shakeChaos0Head(struct task *tp)
{
}

// STUB: SADX 0x006e6d20
void setShakeHeadParam(float param)
{
}
