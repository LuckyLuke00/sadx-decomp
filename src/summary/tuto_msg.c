#include "decls.h"

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
