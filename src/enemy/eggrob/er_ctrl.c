#include "decls.h"
long ERobKill();
long ERobKill(void);
struct task *Eggrob_GenerateEggrob(struct erctrlstr *);
extern int DAT_05edc428;

// FUNCTION: SADX 0x005d1980
void ERobCtrlInitTP()
{
	DAT_05edc428 = 0;
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
