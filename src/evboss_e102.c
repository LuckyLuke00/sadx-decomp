#include "decls.h"
extern struct obj object_ecb_bosscl_bosscl[1];
void WithdrawCollisionEntry(struct task *pTask, struct obj *pObject);

// FUNCTION: SADX 0x0061c030
void E102EggLiftCollisionDest(struct task *tp)
{
	WithdrawCollisionEntry(tp, &object_ecb_bosscl_bosscl[0]);
}
