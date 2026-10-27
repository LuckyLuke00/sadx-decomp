#include "decls.h"
void syFree(void *param_1);
extern void *DAT_05ad9640;
extern int DAT_05ad9634;
extern unsigned long DAT_05ad9604;
extern unsigned long DAT_05ad9608;
extern unsigned long DAT_05ad960c;
extern unsigned long DAT_05ad9610;

// FUNCTION: SADX 0x00424580
void njWaitVSync(void)
{
	_gjExecServer();
	_gjDoneRender();
	_gjSwapBuffers();
	_gjRenderClear();
	_gjBeforeRender();
	_gjWaitVsync();
}

// FUNCTION: SADX 0x004245a0
void njSetBackColor(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
	DAT_05ad9604 = param_1;
	DAT_05ad9608 = param_2;
	DAT_05ad960c = param_3;
	DAT_05ad9610 = param_3;
}

// FUNCTION: SADX 0x00424810
void njExitSystem(void)
{
	if (DAT_05ad9640)
	{
		syFree(DAT_05ad9640);
		DAT_05ad9640 = 0;
		DAT_05ad9634 = 0;
	}
}

// FUNCTION: SADX 0x00424840
void njInitVertexBuffer(long param_1, long param_2, long param_3, long param_4, long param_5)
{
	if (DAT_05ad9640)
	{
		syFree(DAT_05ad9640);
		DAT_05ad9640 = 0;
	}
	if (param_1 < 0)
	{
		param_1 = 0;
	}
	if (param_2 < 0)
	{
		param_2 = 0;
	}
	if (param_3 < 0)
	{
		param_3 = 0;
	}
	if (param_4 < 0)
	{
		param_4 = 0;
	}
	if (param_5 < 0)
	{
		param_5 = 0;
	}
	DAT_05ad9634 = (param_1 + param_2 + param_3 + param_4 + param_5) * 4;
	if (DAT_05ad9634 != 0)
	{
		DAT_05ad9640 = (void (__cdecl *)(struct obj *))syMalloc(DAT_05ad9634);
	}
}
