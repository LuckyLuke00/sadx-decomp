#include "decls.h"
extern void ReleaseMiMessage();
void ReleaseMiMessage();
void FUN_004c3310(int *param_1);
void FUN_004c1c20();
void MSG_Close(struct MSGC *msgc);
void MSG_Disp(struct MSGC *msgc);
extern struct MiMsg *DAT_05b3730c;

// FUNCTION: SADX 0x00498b00
unsigned short GetMiMsgMode()
{
	if (DAT_05b3730c == 0)
	{
		return 5;
	}
	return *(unsigned short *)((char *)DAT_05b3730c + 0x50);
}

// STUB: SADX 0x00498b20
void ChangeMiMessageNo(unsigned short u16MsgNo)
{
}

// FUNCTION: SADX 0x00498b80
void ReleaseMiMessage()
{
	if (DAT_05b3730c)
	{
		if (*(int *)((char *)DAT_05b3730c + 0) != 0)
		{
			FUN_004c3310((int *)((char *)DAT_05b3730c + 8));
			FUN_004c1c20();
			syFree(*(void **)((char *)DAT_05b3730c + 0));
		}
		else
		{
			MSG_Close((struct MSGC *)((char *)DAT_05b3730c + 8));
			FUN_004c1c20();
		}
		MSG_Disp(0);
		syFree(DAT_05b3730c);
		DAT_05b3730c = 0;
	}
}

// STUB: SADX 0x00498be0
void SetMiMessage_Main(unsigned short u16MsgNo, unsigned short u16MsgFrame)
{
}
