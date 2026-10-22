#include "decls.h"
extern unsigned char DAT_060c3350;

// FUNCTION: SADX 0x006f8810
void Chaos6HTtaileff(struct task *tp)
{
	DAT_060c3350 = 1;
	tp->exec = objNormalT;
	tp->disp = objDisplayT;
}

// FUNCTION: SADX 0x006f8830
void Chaos6HTtaileffDisappear()
{
	DAT_060c3350 = 0;
}
