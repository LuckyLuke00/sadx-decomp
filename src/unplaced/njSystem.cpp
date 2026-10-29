#include "decls.h"
extern int DAT_0629c4a0;
extern void (*DAT_0629c734)(void);
extern int DAT_0629c540;
extern int DAT_0629c6c4;
extern int DAT_0629c4f0;
extern int DAT_0629c4f4;
extern int DAT_0629c4f8;
extern int DAT_0629c4fc;
extern unsigned int DAT_05ad966c;
extern void (*DAT_0629c740[32])(void);
extern void (*DAT_0629c4a4)(void);
extern void (*DAT_0629c4a8)(void);
extern void (*DAT_0629c730)(int);
extern int DAT_0629c738;

// FUNCTION: SADX 0x00425150
void njSetTextureMemorySize(unsigned long size)
{
	DAT_0629c4a0 = size;
}

// FUNCTION: SADX 0x00425160
void njSetVSyncFunction(void (*func)(void))
{
	DAT_0629c734 = func;
}

// FUNCTION: SADX 0x00425170
void njControl3D(unsigned long flag)
{
	DAT_0629c6c8 = flag;
}

// FUNCTION: SADX 0x00425180
void njSetConstantAttr(int and_attr, int or_attr)
{
	DAT_0629c540 = and_attr;
	DAT_0629c6c4 = or_attr;
}

// FUNCTION: SADX 0x004251a0
void njSetConstantMaterial(NJS_ARGB *mat)
{
	if (mat)
	{
		DAT_0629c4f0 = ((int *)mat)[0];
		DAT_0629c4f4 = ((int *)mat)[1];
		DAT_0629c4f8 = ((int *)mat)[2];
		DAT_0629c4fc = ((int *)mat)[3];
	}
}

// FUNCTION: SADX 0x004251d0
void njEntryWaitVSyncFunc(void (*param_1)(void))
{
	DAT_0629c740[DAT_05ad966c++] = param_1;
}

// FUNCTION: SADX 0x004251f0
void njDeleteWaitVSyncFunc(void (*param_1)(void))
{
	unsigned int var1;
	unsigned int var2;

	var1 = DAT_05ad966c;
	for (var2 = 0; var2 != var1; var2++)
	{
		if (DAT_0629c740[var2] == param_1)
		{
			DAT_0629c740[var2] = 0;
			if (var1 != 1)
			{
				DAT_0629c740[var2] = DAT_0629c740[var1 - 1];
				DAT_05ad966c = var1 - 1;
				return;
			}
		}
	}
}

// FUNCTION: SADX 0x00425240
void njExecWaitVsyncFunc(void)
{
	void (**var1)(void);
	unsigned int var2;

	for (var2 = 0, var1 = DAT_0629c740; var2 != DAT_05ad966c; var2++, var1++)
	{
		(*var1)();
	}
	if (DAT_0629c4a4)
	{
		DAT_0629c4a4();
	}
	if (DAT_0629c4a8)
	{
		DAT_0629c4a8();
	}
	if (DAT_0629c734)
	{
		DAT_0629c734();
	}
	if (DAT_0629c730)
	{
		DAT_0629c730(DAT_0629c738);
	}
}

// FUNCTION: SADX 0x004252a0
void njInitWaitVsyncFunc(void)
{
	DAT_05ad966c = 0;
}
