#include "decls.h"
extern int DAT_05cd0f2c;
extern int DAT_05cd0f28;
extern int DAT_05cda174;
extern int DAT_05cc3620;

// FUNCTION: SADX 0x00573550
void InitDemoSequence()
{
	InitSegaLogo();
	DAT_05cda174 = 0;
	DAT_05cd0f24 = 0;
	DAT_05cd0f28 = 0;
	DAT_05cc3620 = 0;
	CreateInitData();
}

// STUB: SADX 0x00573a50
int dsReturnCheck()
{
	return (int)0;
}

// FUNCTION: SADX 0x00573ad0
void GM_WaitEventDemo(struct task *tp)
{
	tp->exec = GM_WaitEventDemo_exec;
	ADX_Close();
	EV_Load2(DAT_05cd0f28);
	EV_Exec2();
	if (tp->exec != GM_WaitEventDemo_exec)
	{
		CreateElementalTask(0, 0, GM_WaitEventDemo_exec);
	}
}

// FUNCTION: SADX 0x00573b20
void GM_WaitEventDemo_exec(struct task *tp)
{
	if (EV_CheckCansel() == 0)
	{
		FreeTask(tp);
		DemoInputDestructor();
		DAT_05cd0f2c = 0xffffffff;
	}
}
