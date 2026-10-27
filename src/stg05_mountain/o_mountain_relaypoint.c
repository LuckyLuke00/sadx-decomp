#include "decls.h"
extern struct NJS_ACTION action_kasshatyuukei1a_st[];
extern struct NJS_ACTION action_kasshatyuukei1a_st[1];

// FUNCTION: SADX 0x00831f50
void RelaypointDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		ds_ActionClip(action_kasshatyuukei1a_st, var1->scl.x, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00832000
void RelaypointExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			var1->scl.x += *(float *)((char *)var1 + 0x34);
			if (var1->scl.y <= var1->scl.x)
			{
				var1->scl.x -= var1->scl.y;
				RelaypointDraw(tp);
				return;
			}
		}
		RelaypointDraw(tp);
	}
}

// FUNCTION: SADX 0x00832060
void ObjectMountainRelaypoint(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = 0.0;
	var1->scl.y = (float)(unsigned int)action_kasshatyuukei1a_st[0].motion->nbFrame;
	tp->exec = RelaypointExec;
	tp->disp = RelaypointDraw;
	var1->scl.z = 1.0;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
