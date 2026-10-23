#include "decls.h"

// STUB: SADX 0x0088d030
void ObjectCasino_eff_kinka1_End(struct task *tp)
{
}

// FUNCTION: SADX 0x0088d4f0
void ObjectCasino_eff_kinka1(struct task *tp)
{
	tp->disp = ObjectCasino_eff_kinka1_Draw;
	tp->exec = ObjectCasino_eff_kinka1_Exec;
	tp->dest = ObjectCasino_eff_kinka1_End;
}
