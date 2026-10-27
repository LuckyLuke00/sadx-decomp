#include "decls.h"
extern struct TEX_PVMTABLE DAT_060cb490[];
static void evmain(int code);
extern int *DAT_02c21248[1];
extern int DAT_05b3ebbc;
extern int *DAT_02c21248[];

// FUNCTION: SADX 0x0071e830
static void evmain(int code)
{
	switch (code)
	{
	case 1:
	{
		FUN_0056bb90();
		FUN_0056a2b0();
		FUN_0056a2c0();
		BGM_Play(0x1f);
		EV_SerifPlay(0x46a);
		FUN_0056d0b0(FUN_0056b1f0(0), "DD");
		EV_MsgW(0x3c, (char *)(*(int *)DAT_02c21248[DAT_05b3ebbc]));
		EV_LookPoint(FUN_0056b1f0(0), -80.0f, -67.0f, 0.0f);
		EV_SerifPlay(0x46b);
		FUN_0056d0b0(FUN_0056b1f0(0), "CCDDEDC");
		EV_MsgW(0x78, (char *)(*(int *)(DAT_02c21248[DAT_05b3ebbc] + 1)));
		EV_MsgCls();
		EV_CameraOff();
		EV_ClrFace(FUN_0056b1f0(0));
		FUN_0056b920(FUN_0056b1f0(0));
		break;
	}
	case 2:
	{
		EV_InitPlayer(0);
		FUN_0056bcd0();
		FUN_0056a2a0();
		break;
	}
	}
}

// GLOBAL: SADX 0x02c21260
struct EVTABLE2 DAT_02c21260 = {evmain, DAT_060cb490};
