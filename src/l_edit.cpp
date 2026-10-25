#include "decls.h"
extern char *DAT_025ddba8[1];
extern char *DAT_025ddbbc[1];
extern char *DAT_025ddb80[1];
extern char *DAT_025ddb94[1];
extern char DAT_025ddbd0[4];
extern char DAT_025ddbe4[4];
void DialogJimakuInit();
void DialogJimakuPut(char *str);
extern int DAT_05b3ebbc;
int FUN_00502cd0();
extern int DAT_05b9d84c;
extern int DAT_05b9d848;
extern void *DAT_05b42528;
extern void *DAT_05cc3564;
extern unsigned char DAT_05cc3560;
extern unsigned char DAT_05cc3568;
extern int DAT_05cc356c;
extern unsigned char DAT_05cc3570;
void FUN_00503160();

// FUNCTION: SADX 0x00502ac0
void DialogJimakuProcSR(struct DDlgType *ddltype)
{
	DialogJimakuInit();
	switch (ddltype->Csr)
	{
	case 0:
		DialogJimakuPut(DAT_025ddb80[DAT_05b3ebbc]);
		break;
	case 1:
		DialogJimakuPut(DAT_025ddb94[DAT_05b3ebbc]);
		break;
	}
}

// FUNCTION: SADX 0x00502b20
void DialogJimakuProcSRC(struct DDlgType *ddltype)
{
	DialogJimakuInit();
	switch (ddltype->Csr)
	{
	case 0:
		DialogJimakuPut(DAT_025ddb80[DAT_05b3ebbc]);
		break;
	case 1:
		DialogJimakuPut(DAT_025ddb94[DAT_05b3ebbc]);
		break;
	case 2:
		DialogJimakuPut(DAT_025ddba8[DAT_05b3ebbc]);
		break;
	}
}

// FUNCTION: SADX 0x00502b90
void DialogJimakuProcSRF(struct DDlgType *ddltype)
{
	DialogJimakuInit();
	switch (ddltype->Csr)
	{
	case 0:
		DialogJimakuPut(DAT_025ddb80[DAT_05b3ebbc]);
		break;
	case 1:
		DialogJimakuPut(DAT_025ddb94[DAT_05b3ebbc]);
		break;
	case 2:
		DialogJimakuPut(DAT_025ddbbc[DAT_05b3ebbc]);
		break;
	}
}

// STUB: SADX 0x00502c00
void DialogJimakuProcYN(struct DDlgType *ddltype)
{
	DialogJimakuInit();
	switch (ddltype->Csr)
	{
	case 0:
		DialogJimakuPut((*(char *(*)[1])&DAT_025ddbd0)[DAT_05b3ebbc]);
		break;
	case 1:
		DialogJimakuPut((*(char *(*)[1])&DAT_025ddbe4)[DAT_05b3ebbc]);
		break;
	}
}

// STUB: SADX 0x00502c60
void DialogJimakuProcYNS(struct DDlgType *ddltype)
{
	DialogJimakuInit();
	switch (ddltype->Csr)
	{
	case 0:
		DialogJimakuPut((*(char *(*)[1])&DAT_025ddbd0)[DAT_05b3ebbc]);
		break;
	case 1:
		DialogJimakuPut((*(char *(*)[1])&DAT_025ddbe4)[DAT_05b3ebbc]);
		break;
	case 2:
		DialogJimakuPut(DAT_025ddb94[DAT_05b3ebbc]);
		break;
	}
}

// FUNCTION: SADX 0x00502f00
int dsVMSLoadGame()
{
	int local_8;
	local_8 = FUN_00502cd0();
	return local_8;
}

// FUNCTION: SADX 0x005030d0
int FUN_005030d0()
{
	return 0xf;
}

// FUNCTION: SADX 0x005030e0
int FUN_005030e0()
{
	return 1;
}

// FUNCTION: SADX 0x005030f0
void InitGCMemocaState()
{
	DAT_05cc3560 = 1;
	DAT_05cc3568 = 0;
	DAT_05cc356c = 0;
	DAT_05cc3570 = 0;
	DAT_05cc3564 = NULL;
}

// FUNCTION: SADX 0x00503120
void l_edit_Init()
{
	DAT_05b9d84c = 0;
	DAT_05b9d848 = 0;
	if (DAT_05b42528 != 0)
	{
		ReleaseLineList();
	}
}

// FUNCTION: SADX 0x00503150
void SaveMissionData()
{
	FUN_00503160();
}
