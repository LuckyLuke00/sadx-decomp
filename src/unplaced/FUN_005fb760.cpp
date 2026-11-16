#include "decls.h"
#include "../advertise.h"
#include <new>
extern Magic::RenderCore::Texture *DAT_05edd944;
extern Magic::RenderCore::Texture *DAT_05edd954;
extern struct task *DAT_05edd91c;

// FUNCTION: SADX 0x005fb760
void FUN_005fb760()
{
	if (DAT_05edd91c)
	{
		DestroyTask(DAT_05edd91c);
	}
	if (DAT_05edd944)
	{
		delete DAT_05edd944;
		DAT_05edd944 = 0;
	}
	if (DAT_05edd954)
	{
		FUN_0041c2d0(DAT_05edd954);
		delete DAT_05edd954;
		DAT_05edd954 = 0;
	}
	FUN_005fa060();
}

// FUNCTION: SADX 0x005fb820
void FUN_005fb820()
{
	DAT_05edd91c->awp->work.sl[1] = 0xe;
}

// FUNCTION: SADX 0x005fbb40
void FUN_005fbb40()
{
	ghSetPvrTexMaterial(0xffffffff);
}
