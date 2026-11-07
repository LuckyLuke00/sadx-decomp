#include "decls.h"
extern "C" int rand(void);
void initPole(struct task *pTask);
extern int DAT_060bd19c;

// FUNCTION: SADX 0x006e0f00
void PoleSet_Death()
{
	if (DAT_060bd19c != 0)
	{
		int *var1 = *(int **)((char *)DAT_060bd19c + 0x2c);
		*(int *)((char *)var1 + 0x360) = 0;
		int *var2 = (int *)((char *)var1 + 0x68);
		for (int var3 = 0; var3 < 8; var3++)
		{
			int var4 = rand();
			float var5 = (float)var4 * 3.0517578e-5f;
			*var2 = (int)(var5 * 29.0f + 1.0f);
			var2 = (int *)((char *)var2 + 0x6c);
		}
	}
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
