#include "decls.h"
extern int DAT_05edbde4;
extern int DAT_05edbde0;

// STUB: SADX 0x005aba60
long GetReleaseBoxOpenID()
{
	return (long)0;
}

// FUNCTION: SADX 0x005aba90
void InitReleaseBox()
{
	DAT_05edbde4 = 0;
	DAT_05edbde0 = 0;
}

// FUNCTION: SADX 0x005abbb0
struct task *IsReleaseBoxActive()
{
	return (struct task *)DAT_05edbde4;
}
