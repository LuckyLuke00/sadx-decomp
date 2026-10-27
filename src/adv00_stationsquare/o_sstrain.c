#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060b5fe0;

// FUNCTION: SADX 0x00690e40
void KasyaDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;

	if (dsCheckViewV(&var1->pos, 65.0f))
	{
		___njSetTexture(&texlist_ss_train);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_ActionClip(action_train_base, *(float *)((char *)var2 + 0x10), 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00691150
void sstrain_adxdestruct(struct task *tp)
{
	DAT_060b5fe0 = 0;
}

// FUNCTION: SADX 0x00691160
void sstrain_adxprove(struct task *tp)
{
	if ((((int)DAT_05b9d724 << 8) | (int)DAT_05b9d744) != 0x1a01)
	{
		DestroyTask(tp);
		return;
	}
}

// STUB: SADX 0x00691180
void sstrain_adxcontrol(struct task *tp)
{
}
