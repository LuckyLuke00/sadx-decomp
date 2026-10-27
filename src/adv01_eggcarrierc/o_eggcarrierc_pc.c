#include "decls.h"
static void ecp_actman(struct task *task_p);
extern int DAT_05b3ebbc;
extern const struct HintMessageTable *ECHintTablePointer[5];

// FUNCTION: SADX 0x0069e580
static void ecp_actman(struct task *task_p)
{
	struct anywk *var1;
	int var2;

	var1 = task_p->awp;
	if (var1->work.ul[0] == 0)
	{
		var2 = (DAT_05b9d744 & 0xff);
		EC_CPcSet();
		var1->work.ul[1] = var2;
		var1->work.ul[0] = 1;
	}
	else
	{
		if (var1->work.ul[1] != (DAT_05b9d744 & 0xff))
		{
			EC_CPcDelete();
			var1->work.ul[0] = 0;
		}
	}
}

// FUNCTION: SADX 0x0069e5d0
void _ECPeopleInitialize()
{
	struct task *var2;
	void *var1;
	HintMessageDataInit(ECHintTablePointer[DAT_05b3ebbc]);
	var2 = CreateElementalTask(0, 1, ecp_actman);
	if (var2 != NULL)
	{
		var1 = CAlloc(1, 8);
		if (var1 != NULL)
		{
			var2->awp = (struct anywk *)var1;
			ecp_actman(var2);
			return;
		}
		DestroyTask(var2);
	}
}
