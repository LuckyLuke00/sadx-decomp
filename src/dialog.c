#include "decls.h"
void ghDrawPvrTextureS(int index, float x, float y, float z, float sx, float sy);
void FUN_00576a10(int param_1);
void FUN_00576c10(struct task *param_1);
void FUN_005779c0(signed char param_1);
void FUN_00576bf0(struct task *param_1);
void SetDialogNoKeyTime(short time);
void ghDrawPvrTextureS(int index, float x, float y, float z, float sx, float sy);
void FUN_00576a60(int param_1);
extern struct task *DAT_05cd2600;

// STUB: SADX 0x00575c00
void SetDlgCsrStat(unsigned char *alphap, long *ani_angp, float *sclp)
{
}

// STUB: SADX 0x00575cb0
unsigned long BetweenCol(unsigned long src, unsigned long dst, float avg)
{
	return (unsigned long)0;
}

// FUNCTION: SADX 0x00575e10
void DrawDlgCsr(unsigned char col_alpha, float x, float y, float z, float magx, float magy)
{
	unsigned long local_cg = (col_alpha << 0x18) | 0xffeb00;
	unsigned long local_8g = (col_alpha << 0x18) | 0xec9800;
	___njSetTexture(&texlist_ava_csr);
	ghSetPvrTexVertexColor(local_cg, local_8g, local_cg, local_8g);
	ghDrawPvrTextureS(0x4000003, x * ScreenRaitoX, y * ScreenRaitoY, z, magx * ScreenRaitoX * 0.25f, magy * ScreenRaitoY * 0.25f);
}

// FUNCTION: SADX 0x00575f60
void DrawPanelC(unsigned long col, float x, float y, float z, float magx, float magy)
{
	___njSetTexture(&texlist_ava_csr);
	ghSetPvrTexMaterial(col);
	ghDrawPvrTextureS(0x4000002, x, y, z + -0.3f, magx, magy);
	ghSetPvrTexMaterial((col & 0xff000000) | 0xffffff);
	ghDrawPvrTextureS(0x4000001, x, y, z + -0.6f, magx, magy);
}

// FUNCTION: SADX 0x00576010
void DrawSquareC(unsigned long col, float x, float y, float z, float magx, float magy)
{
	___njSetTexture(&texlist_ava_square);
	ghSetPvrTexMaterial((col & 0xff000000) | 0xffffff);
	ghDrawPvrTextureS(0x4000001, x * ScreenRaitoX, y * ScreenRaitoY, z, magx * 1.0460431575775146 * ScreenRaitoX, magy * 1.177024483680725 * ScreenRaitoY);
	ghSetPvrTexMaterial(col);
	ghDrawPvrTextureS(0x4000000, x * ScreenRaitoX, y * ScreenRaitoY, z + -0.30000001192092896, magx * ScreenRaitoX, magy * ScreenRaitoY);
}

// STUB: SADX 0x00576130
void DrawShadowWinCenter(float cx, float cy, float z, float w, float h)
{
}

// FUNCTION: SADX 0x005761c0
void DialogExec()
{
	if (DAT_05cd2600 != 0)
	{
		dialog_exec(DAT_05cd2600);
		DAT_05cd2600->disp = 0;
	}
}

// FUNCTION: SADX 0x00576a10
void FUN_00576a10(int param_1)
{
	*(int *)(param_1 + 8) = 0;
	*(float *)(param_1 + 0xc) = 0.0f;
	*(float *)(param_1 + 0x10) = 0.0f;
	*(float *)(param_1 + 0x14) = 1.0f;
	*(short *)(param_1 + 0x24) = 0;
	*(short *)(param_1 + 0x26) = 0;
	FUN_00576a60(0);
	*(int *)(param_1 + 0x3c) = -1;
}

#pragma optimize("", off)
// STUB: SADX 0x00576a60
void FUN_00576a60(int param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00576ae0
long FUN_00576ae0(char *param_1, char param_2)
{
	long local_8;

	local_8 = 0;
	while (param_1[0] >= 0)
	{
		if (param_2 == param_1[0])
		{
			local_8 = 1;
		}
		param_1++;
	}
	if (param_2 == *(int *)((char *)DAT_05cd2600->awp + 0x3c))
	{
		local_8 = 0;
	}
	return local_8;
}

// STUB: SADX 0x00576b40
char FUN_00576b40(char *param_1, char param_2, char param_3)
{
	return (char)0;
}

// STUB: SADX 0x00576ba0
char FUN_00576ba0(char *param_1, char param_2)
{
	return (char)0;
}

// FUNCTION: SADX 0x00576bf0
void FUN_00576bf0(struct task *param_1)
{
	*(int *)((char *)param_1 + 0x20) = 0;
	*(int *)((char *)param_1 + 4) = 2;
}

#pragma optimize("", off)
// STUB: SADX 0x00576c10
void FUN_00576c10(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00576d20
void DrawDialogBg(struct DialogWk *wkp)
{
	struct DialogPrmType *local_8;

	local_8 = wkp->Dp;
	ghDefaultBlendingMode();
	ghSetPvrTexVertexColor(local_8->DlgColU, local_8->DlgColD, local_8->DlgColU, local_8->DlgColD);
	DrawShadowWinCenter(local_8->CntrX, local_8->CntrY, local_8->BaseZ + -4.0f, local_8->SzX * wkp->SclX, local_8->SzY * wkp->SclY);
}

// FUNCTION: SADX 0x00577850
struct task *SetDialogTask()
{
	struct task *local_8g;
	void *local_cg;

	local_8g = CreateElementalTask(0, 5, dialog_exec);
	DAT_05cd2600 = local_8g;
	if (DAT_05cd2600 != 0)
	{
		local_cg = MAlloc(0x44);
		local_8g->awp = (struct anywk *)local_cg;
		SetDialogLocalPrm((struct DialogWk *)local_8g);
		local_8g->exec = dialog_exec;
		local_8g->disp = (void (*)(struct task *))FUN_00576c10;
	}
	return local_8g;
}

#pragma optimize("", off)
// STUB: SADX 0x005778c0
void SetDialogLocalPrm(struct DialogWk *wkp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00577930
void FreeDialogTask()
{
	if (DAT_05cd2600 != 0)
	{
		DestroyTask(DAT_05cd2600);
		DAT_05cd2600 = 0;
	}
}

// FUNCTION: SADX 0x00577960
void OpenDialogQuick(struct DialogPrmType *dp, signed char csr, signed char *dis_csr_ptr)
{
	*(struct DialogPrmType **)((char *)DAT_05cd2600->awp + 0x0) = dp;
	FUN_00576a60((int)dis_csr_ptr);
	*(int *)((char *)DAT_05cd2600->awp + 0x3c) = 0xffffffff;
	FUN_005779c0(csr);
	SetDialogNoKeyTime(0);
	FUN_00576bf0((struct task *)DAT_05cd2600->awp);
}

#pragma optimize("", off)
// STUB: SADX 0x005779c0
void FUN_005779c0(signed char param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00577a40
void OpenDialogCsrLet(struct DialogPrmType *dp, signed char csr, signed char *dis_csr_ptr)
{
	*(struct DialogPrmType **)((char *)DAT_05cd2600->awp + 0x0) = dp;
	*(int *)((char *)DAT_05cd2600->awp + 4) = 1;
	FUN_00576a60((int)dis_csr_ptr);
	*(int *)((char *)DAT_05cd2600->awp + 0x3c) = 0xffffffff;
	FUN_005779c0(csr);
	SetDialogNoKeyTime(0);
	if (dp->DlgSndPrmPtr != 0)
	{
		dsPlay_oneshot(dp->DlgSndPrmPtr->OpenSnd, 0, 0, 0);
	}
}

// FUNCTION: SADX 0x00577ac0
void OpenDialog(struct DialogPrmType *param_1, int param_2)
{
	OpenDialogCsrLet(param_1, (signed char)param_2, 0);
}

// FUNCTION: SADX 0x00577ae0
signed char GetDialogStat()
{
	int local_8;
	if (DAT_05cd2600 == 0)
	{
		return -1;
	}
	if (DAT_05cd2600->awp == 0)
	{
		return -1;
	}
	if ((int)DAT_05cd2600->awp->work.ptr[1] >= 5)
	{
		local_8 = *(signed char *)((char *)DAT_05cd2600->awp + 0x28);
	}
	else
	{
		local_8 = -1;
	}
	return (signed char)local_8;
}

// FUNCTION: SADX 0x00577b30
int CloseDialog()
{
	struct anywk *local_8;
	local_8 = DAT_05cd2600->awp;
	if (*(int *)((char *)local_8 + 4) < 2)
	{
		return 0;
	}
	else
	{
		if (*(int *)((char *)local_8 + 4) == 2)
		{
			*(short *)((char *)local_8 + 0x26) = 4;
			*(int *)((char *)local_8 + 4) = 3;
		}
		return 1;
	}
}

// FUNCTION: SADX 0x00577b80
short GetDialogNoKeyTime()
{
	struct anywk *local_8;
	local_8 = DAT_05cd2600->awp;
	return *(short *)((char *)local_8 + 0x24);
}

// FUNCTION: SADX 0x00577ba0
void SetDialogNoKeyTime(short time)
{
	struct anywk *local_8;
	local_8 = DAT_05cd2600->awp;
	*(short *)((char *)local_8 + 0x24) = time;
}
