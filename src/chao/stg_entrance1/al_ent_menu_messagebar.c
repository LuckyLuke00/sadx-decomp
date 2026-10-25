#include "decls.h"
extern struct task *DAT_05b33048;

// FUNCTION: SADX 0x00474930
void MessageBarClear()
{
	AlMsgTelopClear((struct SAlMsgTelop *)DAT_05b33048->awp->work.ptr[0]);
}
