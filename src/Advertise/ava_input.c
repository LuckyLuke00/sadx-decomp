#include "decls.h"
extern unsigned int *DAT_05b93264;
extern int DAT_05b92e44;

// FUNCTION: SADX 0x0055e260
int IsBtnDecide()
{
	return (DAT_05b92e44 & 4) | (DAT_05b92e44 & 8);
}

// FUNCTION: SADX 0x0055e280
int IsBtnCancel(void)
{
	return (DAT_05b92e44 & 2) | (DAT_05b92e44 & 0x400);
}

// FUNCTION: SADX 0x0055e2a0
int IsSOCAVAPress(int padno, int keys)
{
	return ((unsigned int **)&DAT_05b93264)[padno][4] & keys;
}
