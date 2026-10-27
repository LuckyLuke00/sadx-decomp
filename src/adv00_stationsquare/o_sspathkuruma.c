#include "decls.h"

// STUB: SADX 0x006828a0
void Exec(struct task *tp)
{
}

// STUB: SADX 0x00683120
void CarBumpPlayer(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x00683410
void KurumaDestructor(struct task *tp)
{
	struct colliwk *var1;

	var1 = (struct colliwk *)tp->twp->value.ptr;
	if (var1)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1);
		ReleaseMobileLandObject((struct obj *)var1);
	}
}

// STUB: SADX 0x00683f50
struct task *CreateSSPathkuruma(long n)
{
	return (struct task *)0;
}
