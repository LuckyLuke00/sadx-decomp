#include "decls.h"
extern struct task *DAT_060d0ac8;
extern struct task *DAT_060d0ac4;

// FUNCTION: SADX 0x0083d9b0
void ObjectSkydeck_kikanjyu1_End(struct task *tp)
{
	struct task *var1 = DAT_060d0ac8;
	while (var1 != 0)
	{
		struct task *var2 = *(struct task **)((char *)var1 + 0x20);
		struct task *var3 = *(struct task **)((char *)var1 + 0x24);
		struct task *var4 = var3;
		if (var2 == 0)
		{
			DAT_060d0ac8 = var3;
		}
		else
		{
			*(struct task **)((char *)var2 + 0x24) = var3;
		}
		var3 = *(struct task **)((char *)var1 + 0x24);
		if (var3 != 0)
		{
			*(struct task **)((char *)var3 + 0x20) = *(struct task **)((char *)var1 + 0x20);
		}
		Free(var1);
		var1 = var4;
	}
	if (DAT_060d0ac4 == tp)
	{
		DAT_060d0ac4 = 0;
	}
}

// STUB: SADX 0x0083da10
void ObjectSkydeck_kikanjyu1_Draw(struct task *tp)
{
}

// FUNCTION: SADX 0x0083de50
void ObjectSkydeck_kikanjyu1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_kikanjyu1_info, 2, 4);
	}
	tp->disp = ObjectSkydeck_kikanjyu1_Draw;
	tp->exec = ObjectSkydeck_kikanjyu1_Exec;
	tp->dest = ObjectSkydeck_kikanjyu1_End;
	var1->wtimer = 0;
}
