#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_obj_shareobj;
extern struct obj object_tp_obj_planet01_planet01[1];
extern struct obj object_tp_obj_planet02_planet02[1];
extern struct obj object_tp_obj_planet03_planet03[1];

// FUNCTION: SADX 0x008d45a0
void ObjectTPPlanetI(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->btimer = 3;
	execTPPlanet(tp);
}

// STUB: SADX 0x008d45d0
void execTPPlanet(struct task *tp)
{
}

// FUNCTION: SADX 0x008d4720
void dispTPPlanet(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetTexture(&texlist_obj_shareobj);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(0, (unsigned short)local_8->ang.x);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(0, (unsigned short)local_8->ang.y);
	}
	if (local_8->counter.ptr == &object_tp_obj_planet01_planet01[0] ||
	    local_8->counter.ptr == &object_tp_obj_planet02_planet02[0] ||
	    local_8->counter.ptr == &object_tp_obj_planet03_planet03[0])
	{
		late_DrawObjectEx((struct obj *)local_8->counter.ptr, 0);
	}
	else
	{
		___dsSetPalette(2);
		___dsDrawObject((struct obj *)local_8->counter.ptr);
		___dsSetPalette(0);
	}
	njPopMatrix(1);
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
