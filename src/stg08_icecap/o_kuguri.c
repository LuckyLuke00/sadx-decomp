#include "decls.h"
static void Normal2(struct task *tp);
static void Disp2(struct task *tp);
extern unsigned char DAT_045d9f50;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern unsigned char DAT_045d9f51;

// STUB: SADX 0x0085de40
static void Disp2(struct task *tp)
{
}

// FUNCTION: SADX 0x0085df60
void late_Disp2(struct task *tp)
{
	late_SetFunc((void (__cdecl *)(void *))Disp2, tp, 22047.99f, 1);
}

// FUNCTION: SADX 0x0085df80
static void Normal2(struct task *tp)
{
	if ((DAT_05b9d724 << 8 | DAT_05b9d744) != 0x802)
	{
		FreeTask(tp);
		return;
	}
	if (DAT_045d9f51 != 0)
	{
		DAT_045d9f51--;
	}
	late_SetFunc((void (__cdecl *)(void *))Disp2, tp, 22047.99f, 1);
}

// FUNCTION: SADX 0x0085dfd0
void ObjectKuguriControl(struct task *tp)
{
	DAT_045d9f50 = 1;
	DAT_045d9f51 = 0;
	tp->exec = Normal2;
	tp->disp = late_Disp2;
}
