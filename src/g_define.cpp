#include "decls.h"
#include "advertise.h"
void FUN_00402d00();
extern int DAT_06299468;

extern void* DAT_060ee7d0;
extern void* DAT_06298cec;
extern void* DAT_060eea80;
extern void* DAT_06276c40;
extern void* DAT_06274ae4;
extern void* DAT_06276c28;
extern void* DAT_0629c338;

// FUNCTION: SADX 0x00402aa0
void LoadBosschaos0models()
{
	void* var1 = DAT_060ee7d0 = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->FUN_004035e0(std::string("bosschaos0models"));
	if (var1 != 0)
	{
		DAT_06298cec = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->GetFuncAddress(DAT_060ee7d0, "___LANDTABLEBOSSCHAOS0");
		DAT_060eea80 = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->GetFuncAddress(DAT_060ee7d0, "___BOSSCHAOS0LAND_OBJECTS");
		DAT_06276c40 = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->GetFuncAddress(DAT_060ee7d0, "___BOSSCHAOS0_OBJECTS");
		DAT_06274ae4 = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->GetFuncAddress(DAT_060ee7d0, "___BOSSCHAOS0_ACTIONS");
		DAT_06276c28 = ((Magic::Base::Singleton<SOCSystem>*)&DAT_0629c338)->GetSubject()->GetFuncAddress(DAT_060ee7d0, "___BOSSCHAOS0_TEXLISTS");
	}
}

// STUB: SADX 0x00402cd0
void LoadModules(void *param)
{
}

// FUNCTION: SADX 0x00402db0
int FUN_00402db0()
{
	FUN_00402d00();
	return (int)&DAT_06299468;
}
