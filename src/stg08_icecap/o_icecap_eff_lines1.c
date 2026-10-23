#include "decls.h"

// STUB: SADX 0x00868f20
void ObjectIcecap_eff_lines1_End(struct task *tp)
{
}

// FUNCTION: SADX 0x008691c0
void ObjectIcecap_eff_lines1(struct task *tp)
{
	tp->exec = ObjectIcecap_eff_lines1_Exec;
	tp->dest = ObjectIcecap_eff_lines1_End;
}
