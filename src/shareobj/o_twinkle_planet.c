#include "decls.h"

// FUNCTION: SADX 0x008d45a0
void ObjectTPPlanetI(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->btimer = 3;
	execTPPlanet(tp);
}

// FUNCTION: SADX 0x008d4820
void ObjectTPPlanetII(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->btimer = 4;
	execTPPlanet(tp);
}

// FUNCTION: SADX 0x008d4850
void ObjectTPPlanetIII(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	*(unsigned char *)((char *)local_8 + 3) = 5;
	execTPPlanet(tp);
}

// FUNCTION: SADX 0x008d4880
void ObjectTPMeteoriteI(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	*(char *)((char *)local_8 + 3) = 0;
	execTPPlanet(tp);
}

// FUNCTION: SADX 0x008d48b0
void ObjectTPMeteoriteII(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->btimer = 1;
	execTPPlanet(tp);
}

// FUNCTION: SADX 0x008d48e0
void ObjectTPMeteoriteIII(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->btimer = 2;
	execTPPlanet(tp);
}
