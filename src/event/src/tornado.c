#include "decls.h"
extern struct CCL_INFO DAT_0336d714;

// FUNCTION: SADX 0x007df680
struct task *CreateEventObjectTR(void)
{
	struct task *var1 = CreateElementalTask(2, 5, SOC_EventObject);
	SetEventWork(var1->twp);
	CCL_Init(var1, &DAT_0336d714, 1, 4);
	return var1;
}
