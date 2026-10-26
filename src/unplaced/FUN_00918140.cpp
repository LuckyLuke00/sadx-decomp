#include "decls.h"
extern char *DAT_060ee5b8;

// FUNCTION: SADX 0x00918140
void FUN_00918140()
{
	*(int *)(DAT_060ee5b8 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918150
void FUN_00918150()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x29) = *(char *)(var1 + 0x28);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918170
void FUN_00918170()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x29) = *(char *)(var1 + 1);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918190
void FUN_00918190()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x28) = *(char *)(var1 + 5);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009181b0
void FUN_009181b0()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x28) = *(char *)(var1 + 4);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009181d0
void FUN_009181d0()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x28) = *(char *)(var1 + 9);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009181f0
void FUN_009181f0()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x28) = *(char *)(var1 + 8);
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918210
void FUN_00918210()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0x28) = *(char *)(var1 + 0x29);
	*(int *)(var1 + 0x50) = 9;
}
