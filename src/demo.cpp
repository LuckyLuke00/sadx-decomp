#include "decls.h"
extern int DAT_05cda178;
extern short DAT_05cda158;
extern short DAT_05cda15c;

// FUNCTION: SADX 0x0059bdc0
void DemoInput()
{
	if (DAT_05cda178 != 0)
	{
		DemoInputDestructor();
	}
	DAT_05cda178 = (int)syMalloc(0x20000);
	DAT_05cda158 = 0x1555;
	DAT_05cda15c = 0;
}

// FUNCTION: SADX 0x0059be00
void DemoInputDestructor()
{
	if (DAT_05cda178 != 0)
	{
		syFree((void *)DAT_05cda178);
		DAT_05cda178 = 0;
		DAT_05cda158 = 0;
		DAT_05cda15c = 0;
	}
}
