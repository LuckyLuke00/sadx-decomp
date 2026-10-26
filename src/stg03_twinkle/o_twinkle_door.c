#include "decls.h"
extern struct obj object_park03_lr_door_lr_door[];
extern struct obj object_park03_lr_door_lr_door[1];
extern struct obj object_park03_lr_doorb_lr_doorb[1];
void destChaos7Float(struct task *tp);
void dispTPDoor(struct task *tp);
unsigned long CheckEditMode();

// FUNCTION: SADX 0x00812e70
void dispTPDoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->scl);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)(*(int *)((char *)var1 + 8)), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00813000
void execTPDoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = tp->ptp;
	struct taskwk *var3 = var2->twp;
	if (CheckEditMode())
	{
		var1->counter.l = (long)&object_park03_lr_door_lr_door;
		dispTPDoor(tp);
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		var1->scl.z = 0.0f;
		var1->counter.l = (long)&object_park03_lr_door_lr_door;
		var1->scl.y = 0.0f;
		var1->scl.x = 0.0f;
		tp->dest = destChaos7Float;
		tp->disp = dispTPDoor;
		break;
	case 1:
		var1->scl.y = var3->scl.y;
		dispTPDoor(tp);
		return;
	}
}

// FUNCTION: SADX 0x00813200
void execTPDoorB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = tp->ptp;
	struct taskwk *var3 = var2->twp;
	if (CheckEditMode())
	{
		var1->counter.l = (long)&object_park03_lr_doorb_lr_doorb;
		dispTPDoor(tp);
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		var1->scl.z = 0.0f;
		var1->counter.l = (long)&object_park03_lr_doorb_lr_doorb;
		var1->scl.y = 0.0f;
		var1->scl.x = 0.0f;
		tp->dest = destChaos7Float;
		tp->disp = dispTPDoor;
		break;
	case 1:
		var1->scl.y = var3->scl.y;
		dispTPDoor(tp);
		return;
	}
}

// FUNCTION: SADX 0x00813880
void dispTPDoorWithMirror(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->scl);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)var1->counter.l, 1.0f);
		njPopMatrix(1);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->scl);
		FUN_0067d830(NULL, var1->pos.x + 50.0f, var1->pos.y, var1->pos.z);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)var1->counter.l, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00813960
void execTPDoorWithMirror(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = tp->ptp;
	struct taskwk *var3 = var2->twp;
	if (CheckEditMode())
	{
		var1->counter.l = (long)&object_park03_lr_doorb_lr_doorb;
		dispTPDoorWithMirror(tp);
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		var1->scl.z = 0.0f;
		var1->counter.l = (long)&object_park03_lr_doorb_lr_doorb;
		var1->scl.y = 0.0f;
		var1->scl.x = 0.0f;
		tp->dest = destChaos7Float;
		tp->disp = dispTPDoorWithMirror;
		break;
	case 1:
		var1->scl.y = var3->scl.y;
		dispTPDoorWithMirror(tp);
		return;
	}
}
