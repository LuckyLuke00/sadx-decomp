#include "decls.h"

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
