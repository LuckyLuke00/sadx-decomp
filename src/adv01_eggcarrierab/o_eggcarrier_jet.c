#include "decls.h"
void late_ActionEx(NJS_ACTION *action, float frame, int flgs);
extern struct NJS_TEXLIST texlist_ec_sky;
void late_ActionEx(NJS_ACTION *action, float frame, int flgs);

// FUNCTION: SADX 0x006944c0
void JetDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_ec_sky);
	late_ActionEx((NJS_ACTION *)var1->timer.ptr, var1->value.f, 4);
}

// STUB: SADX 0x006944f0
void ObjectECJet(struct task *tp)
{
}
