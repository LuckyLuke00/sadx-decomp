#include "decls.h"
extern struct task *DAT_05b33048;

// STUB: SADX 0x00474840
struct task *MessageBarCreate(struct task *parent_tp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x00474930
void MessageBarClear()
{
	AlMsgTelopClear((struct SAlMsgTelop *)DAT_05b33048->awp->work.ptr[0]);
}

// STUB: SADX 0x00474950
void MessageBarAdd(signed char MsgId)
{
}
