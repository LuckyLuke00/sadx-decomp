#include "decls.h"
extern int DAT_060cc904;

// STUB: SADX 0x007d7ae0
void chg_frogshape(signed char shapeNo)
{
}

// FUNCTION: SADX 0x007d7bc0
void shapefrog_dest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	BufferModelRestore();

	if (var1->counter.ptr != 0)
	{
		Free(var1->counter.ptr);
		var1->counter.ptr = 0;
	}
}

// STUB: SADX 0x007d7e70
void shapefrog_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x007d7ed0
struct task *set_shapefrog()
{
	struct task *var1;
	var1 = CreateElementalTask(2, 5, shapefrog_cons);
	if (var1 != 0)
	{
		DAT_060cc904 = (int)var1;
		return var1;
	}
	return (struct task *)DAT_060cc904;
}
