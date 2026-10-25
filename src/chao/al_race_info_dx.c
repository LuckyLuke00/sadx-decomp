#include "decls.h"
extern char DAT_060ca138;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// STUB: SADX 0x00712c30
int calcNearStatusValue(int base)
{
	return (int)0;
}

// FUNCTION: SADX 0x00712ca0
void ADV1_ALR_ClearEntryStatus()
{
	memset(&DAT_060ca138, 0, 0xcc0);
}

// STUB: SADX 0x00712cc0
struct al_status *ADV1_ALR_GetEntryStatus(int num)
{
	return (struct al_status *)0;
}
