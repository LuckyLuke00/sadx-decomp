#include "decls.h"

// STUB: SADX 0x00701f70
void dispChaos7Object(struct task *tp)
{
}

// FUNCTION: SADX 0x007023d0
void ObjectChaos7RedCar(struct task *tp)
{
	tp->twp->btimer = 0;
	execChaos7Object(tp);
}

// FUNCTION: SADX 0x007023f0
void ObjectChaos7YellowCar(struct task *tp)
{
	tp->twp->btimer = 1;
	execChaos7Object(tp);
}

// FUNCTION: SADX 0x00702410
void ObjectChaos7BlueCar(struct task *tp)
{
	tp->twp->btimer = 2;
	execChaos7Object(tp);
}

// FUNCTION: SADX 0x00702430
void ObjectChaos7WallA(struct task *tp)
{
	tp->twp->btimer = 3;
	execChaos7Object(tp);
}

// FUNCTION: SADX 0x00702450
void ObjectChaos7WallB(struct task *tp)
{
	tp->twp->btimer = 4;
	execChaos7Object(tp);
}

// FUNCTION: SADX 0x00702470
void ObjectChaos7WallC(struct task *tp)
{
	tp->twp->btimer = 5;
	execChaos7Object(tp);
}
