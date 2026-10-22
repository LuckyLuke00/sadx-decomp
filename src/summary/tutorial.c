#include "decls.h"
extern float DAT_05b36808;

// STUB: SADX 0x00496400
void FUN_00496400(int param_1)
{
}

// FUNCTION: SADX 0x00496430
float MiTutoGetFade()
{
	return DAT_05b36808;
}

// FUNCTION: SADX 0x00496670
struct task *CreateTutorialTask(int level, int advplno)
{
	struct task *var1;
	struct task *var2;
	struct task *var3;
	struct anywk *var4;
	var1 = CreateElementalTask(2, level, TutorialTask);
	if (var1)
	{
		var4 = (struct anywk *)CAlloc(1, 0xc);
		var1->awp = var4;
		var2 = CreateTutorialMsgTask(level + 1, advplno, 0);
		var1->twp->ang.x = (long)var2;
		var3 = CreateTutorialBgTask(level + 1, advplno, 0);
		var1->twp->ang.y = (long)var3;
		var4->work.ptr[0] = (void *)var2;
		var4->work.ptr[1] = (void *)var2;
		var4->work.ub[8] = (unsigned char)advplno;
		var1->dest = TutorialTaskDestructor;
	}
	return var1;
}
