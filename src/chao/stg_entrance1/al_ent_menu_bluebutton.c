#include "decls.h"

// FUNCTION: SADX 0x004741c0
void BlueButtonModoruDestructor(struct task *tp)
{
	*(int *)((char *)DAT_05b33018 + 0xfc) = 0;
}

// FUNCTION: SADX 0x004741d0
void CreateBlueButtonModoru(struct task *tp, float xpos, float ypos, long id)
{
	struct task *var1;
	struct taskwk *var2;

	if (*(int *)((char *)DAT_05b33018 + 0xfc) == 0)
	{
		var1 = CreateChildTask(2, BlueButtonExecutor, tp);
		var1->disp = BlueButtonDisplayer;
		var1->dest = BlueButtonModoruDestructor;
		var2 = var1->twp;
		var2->pos.x = xpos;
		var2->smode = (signed char)id;
		var2->pos.y = ypos;
		var2->btimer = 1;
		var2->pos.z = 0.3f;
		var2->ang.x = 0x5d;
		var2->wtimer = 0x78;
		var2->ang.y = 0;
		*(int *)((char *)DAT_05b33018 + 0xfc) = (int)var1;
	}
}
