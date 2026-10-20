#include "decls.h"
long ERobKill();
long ERobKill(void);
struct task *Eggrob_GenerateEggrob(struct erctrlstr *);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05edc428;

// FUNCTION: SADX 0x005d1980
void ERobCtrlInitTP()
{
	DAT_05edc428 = 0;
}

// FUNCTION: SADX 0x005d1990
void ERobCtrlInit()
{
	DAT_05edc428 = 0;
	if ((((int)(DAT_05b9d724 << 8) | (int)DAT_05b9d744) != 0xa00))
	{
		if ((((int)(DAT_05b9d724 << 8) | (int)DAT_05b9d744) & 0xff00) != 0x1700)
		{
			if (EV_CheckCansel() == 0)
			{
				texLoadTexturePvmFile("EGGROB", &texlist_eggrob);
			}
		}
	}
	else
	{
		texLoadTexturePvmFile("EGGROB", &texlist_eggrob);
	}
}

// FUNCTION: SADX 0x005d1a00
long ERobStart(struct erctrlstr *cmd)
{
	ERobKill();
	if (DAT_05edc428 != 0) {
		return 0;
	}
	DAT_05edc428 = (int)Eggrob_GenerateEggrob(cmd);
	if (DAT_05edc428 == 0) {
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x005d1a40
long ERobKill(void)
{
	if (DAT_05edc428 == 0)
	{
		return 0;
	}
	FreeTask((struct task *)DAT_05edc428);
	DAT_05edc428 = 0;
	return 1;
}

// FUNCTION: SADX 0x005d1a80
long ERobByenara()
{
	if (DAT_05edc428 == 0)
	{
		return 0;
	}
	if (*(int *)(DAT_05edc428 + 0x20) == 0)
	{
		ERobKill();
		return 0;
	}
	*(unsigned char *)(*(int *)(DAT_05edc428 + 0x20) + 3) = *(unsigned char *)(*(int *)(DAT_05edc428 + 0x20) + 3) | 1;
	return 1;
}

// FUNCTION: SADX 0x005d1ad0
long ERobGetPosition(struct NJS_POINT3 *posp)
{
	if ((DAT_05edc428 == 0) || (posp == 0)) {
		return 0;
	}
	if (*(int *)(DAT_05edc428 + 0x20) == 0) {
		ERobKill();
		return 0;
	}
	int iVar1 = *(int *)(DAT_05edc428 + 0x20) + 0x20;
	*(int *)posp = *(int *)iVar1;
	*(int *)((char *)posp + 4) = *(int *)((char *)iVar1 + 4);
	*(int *)((char *)posp + 8) = *(int *)((char *)iVar1 + 8);
	return 1;
}
