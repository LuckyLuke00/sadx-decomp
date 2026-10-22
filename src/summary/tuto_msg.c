#include "decls.h"
extern void TutorialMsgTask(struct task *tp);
extern unsigned char DAT_05b367f8;

// STUB: SADX 0x00495300
int ChgTutorialMsgPage(struct task *tp, int flag)
{
	return (int)0;
}

// STUB: SADX 0x00495400
int GetTutoMsgPurposePage(struct task *tp)
{
	return (int)0;
}

// FUNCTION: SADX 0x00495410
int GetTutoMsgPage(struct task *tp)
{
	return tp->awp->work.ul[2];
}

// FUNCTION: SADX 0x00495420
void SetTutoMsgNextPage(struct task *tp, int next_page)
{
	*(int *)((char *)tp->awp + 0xc) = next_page;
}

// FUNCTION: SADX 0x00495430
int GetTutoMsgMode(struct task *tp)
{
	return tp->twp->mode;
}

// FUNCTION: SADX 0x00495440
void SetTutoMsgMode(struct task *tp, int mode)
{
	tp->twp->mode = (signed char)mode;
}

// FUNCTION: SADX 0x00495450
int GetTutoMsgStatus(struct task *tp)
{
	return tp->awp->work.ul[1];
}

// FUNCTION: SADX 0x00495460
unsigned char GetTutoNowPage()
{
	return DAT_05b367f8;
}

// STUB: SADX 0x00495470
void TutorialMsgTask(struct task *tp)
{
}

// STUB: SADX 0x00495530
void FUN_00495530(void)
{
}

// STUB: SADX 0x004955a0
void ReleaseTutorialBookTexture(int advplno)
{
}

// STUB: SADX 0x00495fd0
struct task *CreateTutorialMsgTask(int level, int advplno, struct NJS_POINT3 *pos)
{
	return (struct task *)0;
}
