#include "decls.h"
static void FExec(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern int DAT_05b288a0;
extern int DAT_05b2889c;

// FUNCTION: SADX 0x00442db0
long AL_ConfirmLoadIsBusy()
{
	return DAT_05b2889c;
}

// FUNCTION: SADX 0x00442dc0
long AL_ConfirmLoadIsLoaded()
{
	return DAT_05b288a0;
}

// STUB: SADX 0x00442dd0
static void FExec(struct task *tp)
{
}

// FUNCTION: SADX 0x00443320
void AL_ConfirmLoadStart()
{
	if (DAT_05b2889c == 0)
	{
		DAT_05b2889c = 1;
		DAT_05b288a0 = 0;
		CreateElementalTask(0, 2, FExec);
	}
}
