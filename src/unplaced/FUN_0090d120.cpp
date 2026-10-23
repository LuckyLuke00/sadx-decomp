#include "decls.h"
extern char *DAT_060ee5b8;

// FUNCTION: SADX 0x0090d120
void FUN_0090d120()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[0xd];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d140
void FUN_0090d140()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) = *(char *)(var1 + 0xc);
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x0090d160
void FUN_0090d160()
{
}

// FUNCTION: SADX 0x0090d190
void FUN_0090d190()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) = *(char *)(var1 + 1);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d1b0
void FUN_0090d1b0()
{
	char *pcVar1;

	pcVar1 = DAT_060ee5b8;
	*(char *)(pcVar1 + 0xd) = *(char *)(pcVar1 + 5);
	*(int *)(pcVar1 + 0x50) = 4;
	return;
}

// FUNCTION: SADX 0x0090d1d0
void FUN_0090d1d0()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) = *(char *)(var1 + 4);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d1f0
void FUN_0090d1f0()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) = *(char *)(var1 + 9);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d210
void FUN_0090d210()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) = *(char *)(var1 + 8);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d230
void FUN_0090d230()
{
	*(int *)(DAT_060ee5b8 + 0x50) = 4;
}
