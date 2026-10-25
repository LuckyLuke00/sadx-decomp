#include "decls.h"
struct task;

// FUNCTION: SADX 0x00442cb0
void FUN_00442cb0(struct task *param_1)
{
	*(const unsigned long **)((char *)param_1 + 0x20) = AlMsgStrLoad("ChaoDX_Message_System");
}
