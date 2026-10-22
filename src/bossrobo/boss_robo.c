#include "decls.h"
extern void (*DAT_05b9e0b0)();
void *syMalloc(unsigned int param_1);
void _boss_robo_epilog();
void changerroboinit();
extern struct NJS_POINT3 *DAT_060bb8cc;
extern void *DAT_060bb918;

// FUNCTION: SADX 0x006d68a0
void _boss_robo_epilog()
{
	changerroboend();
	if (DAT_060bb918 != 0)
	{
		syFree(DAT_060bb918);
		DAT_060bb918 = 0;
	}
}

// STUB: SADX 0x006d69a0
void Robo_GetPosHand(enum HAND_NUM nNum, struct NJS_POINT3 *pPos)
{
}

// STUB: SADX 0x006d69e0
void Robo_SetPosHand(enum HAND_NUM nNum, struct NJS_POINT3 *pPos)
{
}

// FUNCTION: SADX 0x006d6a20
long Robo_GetAngle()
{
	char *var1 = (char *)DAT_060bb8cc;
	char *var2 = (char *)*(long *)(var1 + 0x20); // Wait, mov ecx, [eax+20] loads a dword.
	return *(long *)(var2 + 0x18);
}

// STUB: SADX 0x006d85f0
void FUN_006d85f0(struct task *param_1)
{
}

// FUNCTION: SADX 0x006d8e50
void _boss_robo_prolog()
{
	DAT_060bb918 = syMalloc(0x49c00);
	changerroboinit();
	DAT_05b9e0b0 = _boss_robo_epilog;
}
