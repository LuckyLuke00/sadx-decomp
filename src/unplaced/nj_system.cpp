#include "decls.h"
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
void njSetBackColor(Uint32 col1, Uint32 col2, Uint32 col3)
{
	DAT_05ad9604 = col1;
	DAT_05ad9608 = col2;
	DAT_05ad960c = col3;
	DAT_05ad9610 = col3;
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
void njInitVertexBuffer(long op, long om, long tp, long tm, long pt)
{
	if (DAT_05ad9640)
	{
		syFree(DAT_05ad9640);
		DAT_05ad9640 = 0;
	}
	if (op < 0)
	{
		op = 0;
	}
	if (om < 0)
	{
		om = 0;
	}
	if (tp < 0)
	{
		tp = 0;
	}
	if (tm < 0)
	{
		tm = 0;
	}
	if (pt < 0)
	{
		pt = 0;
	}
	DAT_05ad9634 = (op + om + tp + tm + pt) * 4;
	if (DAT_05ad9634 != 0)
	{
		DAT_05ad9640 = (void (__cdecl *)(struct obj *))syMalloc(DAT_05ad9634);
	}
}
