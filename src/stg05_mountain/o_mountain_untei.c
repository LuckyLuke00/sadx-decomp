#include "decls.h"

// FUNCTION: SADX 0x00835d90
void Object_Mountain_Untei1(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 0;
		tp->twp->wtimer = 0x11;
		tp->twp->scl.x = 0.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = -3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835de0
void Object_Mountain_Untei2(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 1;
		tp->twp->wtimer = 0x11;
		tp->twp->scl.x = 0.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = -3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835e30
void Object_Mountain_Untei3(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 2;
		tp->twp->wtimer = 2;
		tp->twp->scl.x = -10.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = 3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835e80
void Object_Mountain_Untei6(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 3;
		tp->twp->wtimer = 5;
		tp->twp->scl.x = -10.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = 12.0f;
	}
	Object_Mountain_Untei(tp);
}
