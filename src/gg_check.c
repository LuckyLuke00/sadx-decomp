#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05b3e05c;
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);
void CameraStay(struct _OBJ_CAMERAPARAM *pParam);
void GGMessageMain(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
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

// FUNCTION: SADX 0x0056f770
long InitGGMessage()
{
	struct task *local_cg;
	struct taskwk *local_8g;
	DAT_05ccdf08 = 0;
	local_cg = CreateElementalTask(2, 8, GGMessageMain);
	if (local_cg == 0)
	{
		return 0;
	}
	local_8g = local_cg->twp;
	local_8g->mode = 0;
	DAT_05ccdf08 = 1;
	local_cg->dest = GGMessageDest;
	if ((DAT_05b9d724 << 8 | DAT_05b9d744) != 0x902 && DAT_05b3e05c != 0x16)
	{
		CameraSetEventCameraFunc(CameraStay, 0, 0);
	}
	return 1;
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

// STUB: SADX 0x0056fb80
long GetGGName(char *pString, unsigned char u8No)
{
	return (long)0;
}
