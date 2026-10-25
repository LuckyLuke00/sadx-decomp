#include "decls.h"
extern void *DAT_05b06804;
extern void *DAT_05b06824;
extern char DAT_05b067f8[];
extern char DAT_05b067e8;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// FUNCTION: SADX 0x004416c0
void ALMC_Init()
{
	___OutputDebugString("\nMemoryCard Init\n");
	memset(&DAT_05b067e8, 0, 0x40);
}

// STUB: SADX 0x004416e0
long ALMC_Mount(long slot)
{
	return (long)0;
}

// FUNCTION: SADX 0x00441710
void ALMC_Unmount(long slot)
{
	___OutputDebugString("Unmount slot %1d\n", slot);
	*(int *)(DAT_05b067f8 + slot * 0x20) = 0;
}

// FUNCTION: SADX 0x00441740
long ALMC_IsMount(long slot)
{
	return *(long *)(DAT_05b067f8 + slot * 0x20);
}

// FUNCTION: SADX 0x00441750
void ALMC_Exit()
{
	if (DAT_05b06804 != 0)
	{
		syFree(DAT_05b06804);
		DAT_05b06804 = 0;
	}
	if (DAT_05b06824 != 0)
	{
		syFree(DAT_05b06824);
		DAT_05b06824 = 0;
	}
	if (ALMC_IsMount(0) != 0)
	{
		ALMC_Unmount(0);
	}
	if (ALMC_IsMount(1) != 0)
	{
		ALMC_Unmount(1);
	}
	___OutputDebugString("\nMemoryCard Exit\n");
}

// STUB: SADX 0x004417d0
unsigned long ALMC_GetSystemSlot()
{
	return (unsigned long)0;
}
