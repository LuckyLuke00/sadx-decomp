#include "decls.h"
extern void syFree(void *param_1);
extern void FUN_004c3310(int *param_1);
extern void FUN_004c1c20();
extern void MSG_Disp(struct MSGC *msgc);
extern void *DAT_05ccdebc;
extern int DAT_05ccdec0;
void syFree(void *param_1);
void GGMessageDest(struct task *tp);
extern char DAT_05ccdf08;

// STUB: SADX 0x0056f4b0
long isCheckGGApper_Mission()
{
	return (long)0;
}

// STUB: SADX 0x0056f5b0
unsigned char GetGGClearNum(long s32Emblem, long s32Mission)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0056f630
long isCheckGGApper_Emblem()
{
	return (long)0;
}

// STUB: SADX 0x0056f770
long InitGGMessage()
{
	return (long)0;
}

// FUNCTION: SADX 0x0056f800
void GGMessageDest(struct task *tp)
{
	if (DAT_05ccdebc != 0)
	{
		syFree(DAT_05ccdebc);
		DAT_05ccdebc = 0;
	}
	FUN_004c3310(&DAT_05ccdec0);
	FUN_004c1c20();
	MSG_Disp(0);
	DAT_05ccdf08 = 0;
}

// FUNCTION: SADX 0x0056f850
unsigned char isGGMessageEnable()
{
	return DAT_05ccdf08;
}
