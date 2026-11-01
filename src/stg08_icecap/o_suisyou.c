#include "decls.h"

// GLOBAL: SADX 0x045da208
static struct CCL_INFO object_c_info[6];

static void Normal(struct task *tp);
static void Disp(struct task *pTask);

// STUB: SADX 0x00860d40
static void Disp(struct task *pTask)
{
}

// STUB: SADX 0x00860e50
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x00861090
void ObjectSuisyouB(struct task *tp)
{
	CCL_Init(tp, &object_c_info[2], 1, 4);
	tp->exec = Normal;
	tp->disp = Disp;
	tp->twp->mode = 1;
}

// FUNCTION: SADX 0x008610c0
void ObjectSuisyouBM(struct task *tp)
{
	CCL_Init(tp, &object_c_info[3], 1, 4);
	tp->exec = Normal;
	tp->disp = Disp;
	tp->twp->mode = 2;
}
