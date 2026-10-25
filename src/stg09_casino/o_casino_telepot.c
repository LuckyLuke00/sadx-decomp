#include "decls.h"
extern int DAT_060dc42c;

// STUB: SADX 0x0087af10
void ObjectCasinoTelepotEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0087b370
long ObjectCasinoGetTelepotStatus()
{
	return DAT_060dc42c != 0;
}
