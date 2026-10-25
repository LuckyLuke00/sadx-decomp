#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_sunabo_sb_sabos_sb_sabos[1];

// STUB: SADX 0x007e7e00
void ObjectSmallCactusA(struct task *task_p)
{
}

// STUB: SADX 0x007e7e20
void ObjectSmallCactusB(struct task *task_p)
{
}

// FUNCTION: SADX 0x007e80d0
void dispPiece(struct task *task_p)
{
	if (DAT_05b9d838 == 0)
	{
		struct taskwk *var1;
		struct motionwk *var2;
		var1 = task_p->twp;
		var2 = task_p->mwp;
		MirenEffSaveState();
		MirenEffChangeAlpha(*(float *)((char *)var2 + 0x20));
		___njFogDisable();
		MirenObjDrawCharColliObjectNoScale(object_sunabo_sb_sabos_sb_sabos, var1, 0);
		___njFogEnable();
		MirenEffLoadState();
	}
}
