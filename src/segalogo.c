#include "decls.h"
extern int DAT_05cd0f24;
extern int DAT_05cd0f1c;
extern int DAT_05cd0f18;
extern char DAT_0098c030[11];
extern int DAT_05cd0f2c;
extern int DAT_05cd0f28;
extern int DAT_05cda174;
extern int DAT_05cc3620;

// FUNCTION: SADX 0x005734b0
void InitSegaLogo()
{
	union NJS_COLOR col;
	InitMemory();
	InitTask();
	dsSetFade(0);
	___njSetBackColor(0, 0, 0);
	texLoadTexturePvmFile(DAT_0098c030, &texlist_segalogo);
	DAT_05cd0f1c = 0x10;
	DAT_05cd0f18 = 0;
	dsInitInt(1, 1);
	njSetWaitVsyncCount(1);
	col.argb.b = 0;
	col.argb.g = 0;
	col.argb.r = 0;
	col.argb.a = 0;
	SetOffsetColor(&col);
	ghInitPvrTexture();
	FUN_007d21b0((void *)3);
}

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

// STUB: SADX 0x00573590
long SegaLogo()
{
	return (long)0;
}

// STUB: SADX 0x00573790
void dsGoDemoLoop()
{
}

// STUB: SADX 0x005739a0
void dsInitTitle()
{
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

// STUB: SADX 0x00573b50
void DisplayLogo(unsigned char index)
{
}
