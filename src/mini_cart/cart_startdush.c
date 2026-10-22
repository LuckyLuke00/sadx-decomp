#include "decls.h"
extern int DAT_060cd26c;

// STUB: SADX 0x007e4e70
void setDashParam(struct task *tp)
{
}

// FUNCTION: SADX 0x007e4f60
void InitStartDushCheck()
{
	CreateElementalTask(2, 3, startDushCheck);
	DAT_060cd26c = 0;
}
