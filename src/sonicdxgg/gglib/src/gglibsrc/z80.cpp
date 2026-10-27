#include "decls.h"
extern unsigned char FUN_0090ccb0(int);
extern void FUN_0090ccf0(int, int);
extern unsigned char FUN_0090cc60(int param_1);
unsigned char FUN_0090cc60(int param_1);
void Z80_Write2(unsigned short addr, unsigned short data);
unsigned char FUN_0090ccb0(int param_1);
extern char DAT_060ee5c0[];
extern char DAT_060ee5c0[0x100];
extern char DAT_060ee5c0[256];
int FUN_0090ccd0(int param_1);
extern unsigned char DAT_060ee6c8[256];
void FUN_0090ccf0(int param_1, int param_2);
extern char *DAT_060ee5b8;
int FUN_0090cd50();

#pragma optimize("", off)
// STUB: SADX 0x0090cd50
int FUN_0090cd50()
{
	return (int)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0090cd70
void di()
{
	char *var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x40) = 0;
	*(int *)(var1 + 0x3c) = 0;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cd90
void im_0()
{
	char *var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x44) = 0;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x0090cdb0
void im_1()
{
	int *var1 = (int *)DAT_060ee5b8;
	var1[0x11] = 1;
	var1[0x14] = 8;
}

// FUNCTION: SADX 0x0090cdd0
void im_2()
{
	char *var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x44) = 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x0090cdf0
void ld_b_c()
{
	char *var1 = (char *)DAT_060ee5b8;
	var1[5] = var1[4];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090ce10
void ld_b_d()
{
	char *pcVar1;

	pcVar1 = (char *)DAT_060ee5b8;
	*(char *)(pcVar1 + 5) = *(char *)(pcVar1 + 9);
	*(int *)(pcVar1 + 0x50) = 4;
	return;
}

// FUNCTION: SADX 0x0090ce30
void ld_b_e()
{
	char *pcVar1;

	pcVar1 = (char *)DAT_060ee5b8;
	*(char *)(pcVar1 + 5) = *(char *)(pcVar1 + 8);
	*(int *)(pcVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090ce50
void ld_b_h()
{
	char *pcVar1;

	pcVar1 = (char *)DAT_060ee5b8;
	pcVar1[5] = pcVar1[0xd];
	*(int *)(pcVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090ce70
void ld_b_l()
{
	char *pcVar1;

	pcVar1 = (char *)DAT_060ee5b8;
	pcVar1[5] = pcVar1[0xc];
	*(int *)(pcVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090ce90
void ld_b_xhl()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) = uVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090cec0
void ld_b_a()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[1];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cee0
void ld_c_b()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[5];
	*(int *)(cVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cf00
void ld_c_d()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[9];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cf20
void ld_c_e()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[8];
	*(int *)(cVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cf40
void ld_c_h()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[0xd];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cf60
void ld_c_l()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[0xc];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cf80
void ld_c_xhl()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 4) = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090cfb0
void ld_c_a()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[1];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cfd0
void ld_d_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) = *(char *)(var1 + 5);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090cff0
void ld_d_c()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[4];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d010
void ld_d_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) = *(char *)(var1 + 8);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d030
void ld_d_h()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[0xd];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d050
void ld_d_l()
{
	int iVar1;

	iVar1 = (int)DAT_060ee5b8;
	*(char *)(iVar1 + 9) = *(char *)(iVar1 + 0xc);
	*(int *)(iVar1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d070
void ld_d_xhl()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 9) = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d0a0
void ld_d_a()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[1];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d0c0
void ld_e_b()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[5];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d0e0
void ld_e_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) = *(char *)(var1 + 4);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d100
void ld_e_d()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[9];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d240
void ld_h_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) = *(char *)(var1 + 0xc);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d260
void ld_h_xhl()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) = (char)uVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d290
void ld_h_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[1];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d2b0
void ld_l_b()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[5];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d2d0
void ld_l_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) = *(char *)(var1 + 4);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d2f0
void ld_l_d()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[9];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d310
void ld_l_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) = *(char *)(var1 + 8);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d330
void ld_l_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[0xd];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d350
void ld_l_xhl()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 0xc) = uVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d380
void ld_l_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) = *(char *)(var1 + 1);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d3a0
void ld_xhl_b()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 5));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d3d0
void ld_xhl_c()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 4));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d400
void ld_xhl_d()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 9));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d430
void ld_xhl_e()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 8));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d460
void ld_xhl_h()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 0xd));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d490
void ld_xhl_l()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), *(unsigned char *)((char *)DAT_060ee5b8 + 0xc));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d4c0
int FUN_0090d4c0()
{
	return FUN_0090cd50();
}

// FUNCTION: SADX 0x0090d4d0
void ld_xhl_a()
{
	FUN_0090ccf0((int)*(unsigned short *)(DAT_060ee5b8 + 0xc), (int)*(unsigned char *)(DAT_060ee5b8 + 1));
	*(int *)(DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d500
void ld_a_b()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[5];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d520
void ld_a_c()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[4];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d540
void ld_a_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) = *(char *)(var1 + 9);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d560
void ld_a_e()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[8];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d580
void ld_a_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) = *(char *)(var1 + 0xd);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d5a0
void ld_a_l()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[0xc];
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090d5c0
void ld_a_xhl()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 1) = uVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d5f0
void ld_b_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[5] = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d620
void ld_c_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[4] = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d650
void ld_d_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[9] = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d680
void ld_e_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[8] = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d6b0
void ld_h_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(unsigned char *)(var1 + 0xd) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d6e0
void ld_l_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(unsigned char *)(var1 + 0xc) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d710
void ld_xhl_n()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090d750
void ld_a_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090d780
void ld_b_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 5) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d7c0
void ld_c_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 4) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d800
void ld_d_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 9) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d840
void ld_e_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 8) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d880
void ld_h_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 0xd) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d8c0
void ld_l_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 0xc) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d900
void ld_a_xix()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x28))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 1) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d940
void ld_b_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 5) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d980
void ld_c_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 4) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090d9c0
void ld_d_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 9) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090da00
void ld_e_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 8) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090da40
void ld_h_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 0xd) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090da80
void ld_l_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 0xc) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// FUNCTION: SADX 0x0090dac0
void ld_a_xiy()
{
	char *var1;
	char var2;
	char var3;
	char var4;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)(DAT_060ee5b8 + 0x20)));
	var3 = (char)(char)(short)var2;
	var4 = (char)(FUN_0090ccb0((unsigned short)((short)var3 + *(short *)(DAT_060ee5b8 + 0x2c))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	*(char *)(var1 + 1) = var4;
	*(int *)(var1 + 0x50) = 0x13;
}

// STUB: SADX 0x0090db00
void ld_xix_b()
{
}

// STUB: SADX 0x0090db80
void ld_xix_d()
{
}

// STUB: SADX 0x0090dbc0
void ld_xix_e()
{
}

// STUB: SADX 0x0090dc00
void ld_xix_h()
{
}

// STUB: SADX 0x0090dc40
void ld_xix_l()
{
}

// STUB: SADX 0x0090dcc0
void ld_xiy_b()
{
}

// STUB: SADX 0x0090dd80
void ld_xiy_e()
{
}

// STUB: SADX 0x0090ddc0
void ld_xiy_h()
{
}

// STUB: SADX 0x0090de00
void ld_xiy_l()
{
}

// STUB: SADX 0x0090de40
void ld_xiy_a()
{
}

// STUB: SADX 0x0090de80
void ld_xix_n()
{
}

// STUB: SADX 0x0090dee0
void ld_xiy_n()
{
}

// FUNCTION: SADX 0x0090df40
void ld_a_xbc()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 1) = uVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090df70
void ld_a_xde()
{
	char *var1;
	unsigned char cVar1;

	cVar1 = FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 8));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 1) = cVar1;
	*(int *)(var1 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090dfa0
void ld_a_xn()
{
	char *var1;
	int iVar1;
	unsigned char uVar2;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	uVar2 = FUN_0090ccb0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	var1[1] = (char)uVar2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0090dfe0
void ld_xbc_a()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 4), *(unsigned char *)((char *)DAT_060ee5b8 + 1));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// FUNCTION: SADX 0x0090e010
void ld_xde_a()
{
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 8), *(unsigned char *)((char *)DAT_060ee5b8 + 1));
	*(int *)((char *)DAT_060ee5b8 + 0x50) = 7;
}

// STUB: SADX 0x0090e040
void ld_xn_a()
{
}

// FUNCTION: SADX 0x0090e080
void ld_a_i()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[0x30];
	var1[0] = (var1[0] & 1) | (DAT_060ee6c8[(unsigned char)var1[0x30]] | ((*(int *)(var1 + 0x40)) != 0 ? 4 : 0));
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x0090e0b0
void ld_a_r()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[0x34];
	var1[0] = (var1[0] & 1) | (DAT_060ee6c8[(unsigned char)var1[0x34]] | ((*(int *)(var1 + 0x40)) != 0 ? 4 : 0));
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x0090e0e0
void ld_i_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0x30] = var1[1];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x0090e100
void ld_r_a()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x34) = (unsigned char)var1[1];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x0090e120
void ld_bc_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 4) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e150
void ld_de_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 8) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e180
void ld_hl_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e1b0
void ld_sp_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x24) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e1e0
void ld_ix_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xe;
}

// FUNCTION: SADX 0x0090e210
void ld_iy_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xe;
}

// FUNCTION: SADX 0x0090e240
void ld_bc_xn()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar1 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 4) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0x14;
}

// FUNCTION: SADX 0x0090e280
void ld_de_xn()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar1 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 8) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0x14;
}

// FUNCTION: SADX 0x0090e2c0
void ld_hl_xn()
{
	char *var1;
	int iVar1;
	int iVar2;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar2 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)iVar2;
	*(int *)(var1 + 0x50) = 0x10;
}

// FUNCTION: SADX 0x0090e300
void ld_sp_xn()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar1 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x24) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0x14;
}

// FUNCTION: SADX 0x0090e340
void ld_ix_xn()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar1 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0x14;
}

// FUNCTION: SADX 0x0090e380
void ld_iy_xn()
{
	char *var1;
	int iVar1;
	int iVar2;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	iVar2 = FUN_0090ccd0((unsigned short)iVar1);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)iVar2;
	*(int *)(var1 + 0x50) = 0x14;
}

// STUB: SADX 0x0090e3c0
void FUN_0090e3c0()
{
}

// STUB: SADX 0x0090e400
void FUN_0090e400()
{
}

// STUB: SADX 0x0090e440
void FUN_0090e440()
{
}

// STUB: SADX 0x0090e480
void FUN_0090e480()
{
}

// STUB: SADX 0x0090e4c0
void FUN_0090e4c0()
{
}

// STUB: SADX 0x0090e500
void FUN_0090e500()
{
}

// FUNCTION: SADX 0x0090e540
void ld_sp_hl()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x24) = *(short *)(var1 + 0xc);
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x0090e560
void ld_sp_ix()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x24) = *(short *)(var1 + 0x28);
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e580
void ld_sp_iy()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x24) = *(short *)(var1 + 0x2c);
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e5a0
void FUN_0090e5a0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)var1;
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x0090e5d0
void FUN_0090e5d0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 4);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x0090e600
void FUN_0090e600()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 8);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x0090e630
void FUN_0090e630()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0xc);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x0090e660
void FUN_0090e660()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x28);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xf;
}

// FUNCTION: SADX 0x0090e690
void FUN_0090e690()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x2c);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x50) = 0xf;
}

// FUNCTION: SADX 0x0090e6c0
void pop_af()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)var1 = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e6f0
void pop_bc()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 4) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e720
void pop_de()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 8) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e750
void pop_hl()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x0090e780
void pop_ix()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xe;
}

// FUNCTION: SADX 0x0090e7b0
void pop_iy()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xe;
}

// STUB: SADX 0x0090e7e0
void add_a_b()
{
}

// STUB: SADX 0x0090e850
void add_a_c()
{
}

// STUB: SADX 0x0090e8c0
void add_a_d()
{
}

// STUB: SADX 0x0090e930
void add_a_e()
{
}

// STUB: SADX 0x0090e9a0
void add_a_h()
{
}

// STUB: SADX 0x0090ea10
void add_a_l()
{
}

// STUB: SADX 0x0090ea80
void add_a_xhl()
{
}

// STUB: SADX 0x0090eb30
void add_a_a()
{
}

// STUB: SADX 0x0090eb90
void add_a_n()
{
}

// FUNCTION: SADX 0x0090ee60
void adc_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 5);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 5) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 5) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 5) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090eed0
void adc_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 4);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 4) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 4) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 4) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090ef40
void adc_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 9);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 9) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 9) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 9) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090efb0
void adc_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 8);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 8) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 8) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 8) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f020
void adc_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 0xd);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 0xd) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 0xd) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xd) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f090
void adc_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 0xc);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 0xc) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 0xc) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xc) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x0090f100
void adc_a_xhl()
{
}

// STUB: SADX 0x0090f1c0
void adc_a_a()
{
}

// STUB: SADX 0x0090f220
void adc_a_n()
{
}

// FUNCTION: SADX 0x0090f500
void sub_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 5);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 5)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 5)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f560
void sub_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 4);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 4)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 4) ^ (unsigned char)var2) & 0x10);
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f5c0
void sub_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 9);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 9)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 9)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f620
void sub_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 8);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 8)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 8)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f680
void sub_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0xd);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xd)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xd)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x0090f6e0
void sub_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0xc);
	var3 = (((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xc)) >> 5)) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xc) ^ (unsigned char)var2) & 0x10);
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x0090f740
void sub_a_xhl()
{
}

// FUNCTION: SADX 0x0090f7e0
void sub_a_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0] = (char)(DAT_060ee6c8[0] | 2);
	var1[1] = 0;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x0090f800
void sub_a_n()
{
}

// STUB: SADX 0x0090f8b0
void sub_a_xix()
{
}

// STUB: SADX 0x0090f9a0
void sub_a_xiy()
{
}

// STUB: SADX 0x0090fa90
void sbc_a_b()
{
}

// STUB: SADX 0x0090fb00
void sbc_a_c()
{
}

// STUB: SADX 0x0090fb70
void sbc_a_d()
{
}

// STUB: SADX 0x0090fbe0
void sbc_a_e()
{
}

// STUB: SADX 0x0090fc50
void sbc_a_h()
{
}

// STUB: SADX 0x0090fcc0
void sbc_a_l()
{
}

// STUB: SADX 0x0090fd30
void sbc_a_xhl()
{
}

// FUNCTION: SADX 0x0090fde0
void sbc_a_a()
{
	char *var1;
	int var2;

	var1 = DAT_060ee5b8;
	var2 = -(*(unsigned char *)var1 & 1);
	*(unsigned char *)var1 = (char)((var2 >> 8) & 1) | (char)DAT_060ee6c8[var2 & 0xff] | (char)(var2 & 0x10) | 2;
	*(unsigned char *)(var1 + 1) = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x0090fe20
void sbc_a_n()
{
}

// STUB: SADX 0x0090fed0
void sbc_a_xix()
{
}

// STUB: SADX 0x0090ffc0
void sbc_a_xiy()
{
}

// FUNCTION: SADX 0x009100b0
void and_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & var1[5]) & 0xff;
	var1[0] = DAT_060ee5c0[var2] | 0x10;
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009100e0
void and_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[4];
	*(unsigned char *)var1 = (unsigned char)DAT_060ee5c0[var2] | 0x10;
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910110
void and_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[9];
	*(unsigned char *)var1 = (unsigned char)DAT_060ee5c0[var2] | 0x10;
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910140
void and_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[8];
	*(unsigned char *)var1 = (unsigned char)(DAT_060ee5c0[var2] | 0x10);
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910170
void and_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[0xd];
	var1[0] = (char)(DAT_060ee5c0[var2] | 0x10);
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009101a0
void and_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[0xc];
	var1[0] = (char)(DAT_060ee5c0[var2] | 0x10);
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x009101d0
void and_a_xhl()
{
}

// STUB: SADX 0x00910210
void and_a_a()
{
}

// STUB: SADX 0x00910230
void and_a_n()
{
}

// STUB: SADX 0x00910270
void and_a_xix()
{
}

// STUB: SADX 0x009102d0
void and_a_xiy()
{
}

// FUNCTION: SADX 0x00910330
void or_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[5];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910360
void or_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[4];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910390
void or_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[9];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009103c0
void or_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[8];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009103f0
void or_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[0xd];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910420
void or_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[0xc];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x00910450
void or_a_xhl()
{
}

// STUB: SADX 0x00910490
void or_a_a()
{
}

// STUB: SADX 0x009104b0
void or_a_n()
{
}

// STUB: SADX 0x009104f0
void or_a_xix()
{
}

// STUB: SADX 0x00910550
void or_a_xiy()
{
}

// FUNCTION: SADX 0x009105b0
void xor_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[5];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009105e0
void xor_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[4];
	var1[0] = (char)((char *)DAT_060ee5c0)[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910610
void xor_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[9];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910640
void xor_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[8];
	*(unsigned char *)var1 = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910670
void xor_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[0xd];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009106a0
void xor_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[0xc];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x009106d0
void xor_a_xhl()
{
}

// STUB: SADX 0x00910710
void xor_a_a()
{
}

// STUB: SADX 0x00910730
void xor_a_n()
{
}

// STUB: SADX 0x00910770
void xor_a_xix()
{
}

// STUB: SADX 0x009107d0
void xor_a_xiy()
{
}

// FUNCTION: SADX 0x00910830
void cp_a_b()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 5);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 5)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 5)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910890
void cp_a_c()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 4);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 4)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 4)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009108f0
void cp_a_d()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 9);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 9)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 9)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910950
void cp_a_e()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 8);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 8)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 8)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009109b0
void cp_a_h()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0xd);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xd)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xd)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00910a10
void cp_a_l()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0xc);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xc)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0xc)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x00910a70
void cp_a_xhl()
{
}

// FUNCTION: SADX 0x00910b10
void cp_a_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0] = (char)(DAT_060ee6c8[0] | 2);
	*(int *)(var1 + 0x50) = 4;
}

// STUB: SADX 0x00910b30
void cp_a_n()
{
}

// STUB: SADX 0x00910bd0
void cp_a_xix()
{
}

// STUB: SADX 0x00910cb0
void cp_a_xiy()
{
}

// STUB: SADX 0x00910d90
void inc_b()
{
}

// STUB: SADX 0x00910de0
void inc_c()
{
}

// STUB: SADX 0x00910e30
void inc_d()
{
}

// STUB: SADX 0x00910e80
void inc_e()
{
}

// STUB: SADX 0x00910ed0
void inc_h()
{
}

// STUB: SADX 0x00910f20
void inc_l()
{
}

// STUB: SADX 0x00910f70
void inc_a()
{
}

// STUB: SADX 0x00910fc0
void inc_xhl()
{
}

// STUB: SADX 0x00911030
void inc_xix()
{
}

// STUB: SADX 0x009110c0
void inc_xiy()
{
}

// STUB: SADX 0x00911150
void dec_b()
{
}

// STUB: SADX 0x009111b0
void dec_c()
{
}

// STUB: SADX 0x00911210
void dec_d()
{
}

// STUB: SADX 0x00911270
void dec_e()
{
}

// STUB: SADX 0x009112d0
void dec_h()
{
}

// STUB: SADX 0x00911330
void dec_l()
{
}

// STUB: SADX 0x00911390
void dec_a()
{
}

// STUB: SADX 0x009113f0
void dec_xhl()
{
}

// STUB: SADX 0x00911470
void dec_xix()
{
}

// STUB: SADX 0x00911500
void dec_xiy()
{
}

// FUNCTION: SADX 0x00911590
void add_hl_bc()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 4) + *(unsigned short *)(var1 + 0xc);
	var3 = ((*(unsigned short *)(var1 + 4) >> 8) ^ (*(unsigned short *)(var1 + 0xc) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009115e0
void add_hl_de()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 8) + *(unsigned short *)(var1 + 0xc);
	var3 = ((*(unsigned short *)(var1 + 8) >> 8) ^ (*(unsigned short *)(var1 + 0xc) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xb;
}

// STUB: SADX 0x00911630
void add_hl_hl()
{
}

// FUNCTION: SADX 0x00911670
void add_hl_sp()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 0xc) + *(unsigned short *)(var1 + 0x24);
	var3 = ((*(unsigned short *)(var1 + 0xc) >> 8) ^ (*(unsigned short *)(var1 + 0x24) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0xc) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009116c0
void add_ix_bc()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 4) + *(unsigned short *)(var1 + 0x28);
	var3 = ((*(unsigned short *)(var1 + 4) >> 8) ^ (*(unsigned short *)(var1 + 0x28) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// FUNCTION: SADX 0x00911710
void add_ix_de()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 8) + *(unsigned short *)(var1 + 0x28);
	var3 = ((*(unsigned short *)(var1 + 8) >> 8) ^ (*(unsigned short *)(var1 + 0x28) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// STUB: SADX 0x00911760
void add_ix_ix()
{
}

// FUNCTION: SADX 0x009117a0
void add_ix_sp()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 0x24) + *(unsigned short *)(var1 + 0x28);
	var3 = ((*(unsigned short *)(var1 + 0x24) >> 8) ^ (*(unsigned short *)(var1 + 0x28) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x28) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// FUNCTION: SADX 0x009117f0
void add_iy_bc()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 4) + *(unsigned short *)(var1 + 0x2c);
	var3 = ((*(unsigned short *)(var1 + 4) >> 8) ^ (*(unsigned short *)(var1 + 0x2c) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// FUNCTION: SADX 0x00911840
void add_iy_de()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 8) + *(unsigned short *)(var1 + 0x2c);
	var3 = ((*(unsigned short *)(var1 + 8) >> 8) ^ (*(unsigned short *)(var1 + 0x2c) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// STUB: SADX 0x00911890
void add_iy_iy()
{
}

// FUNCTION: SADX 0x009118d0
void add_iy_sp()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned short *)(var1 + 0x24) + *(unsigned short *)(var1 + 0x2c);
	var3 = ((*(unsigned short *)(var1 + 0x24) >> 8) ^ (*(unsigned short *)(var1 + 0x2c) >> 8) ^ (unsigned char)(var2 >> 8)) & 0x10;
	var3 |= (unsigned char)(var2 >> 0x10) & 1;
	var4 = *(unsigned char *)var1 & 0xc4;
	var3 |= var4;
	*(unsigned short *)(var1 + 0x2c) = (unsigned short)var2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 0xf;
}

// STUB: SADX 0x00911920
void adc_hl_bc()
{
}

// STUB: SADX 0x009119b0
void adc_hl_de()
{
}

// STUB: SADX 0x00911a40
void adc_hl_hl()
{
}

// STUB: SADX 0x00911aa0
void adc_hl_sp()
{
}

// STUB: SADX 0x00911b30
void sbc_hl_bc()
{
}

// STUB: SADX 0x00911bc0
void sbc_hl_de()
{
}

// STUB: SADX 0x00911c50
void sbc_hl_hl()
{
}

// STUB: SADX 0x00911ca0
void sbc_hl_sp()
{
}

// FUNCTION: SADX 0x00911d30
void inc_bc()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 4) = *(short *)(var1 + 4) + 1;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911d50
void inc_de()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 8) = *(short *)(var1 + 8) + 1;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911d70
void inc_hl()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0xc) += 1;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911d90
void inc_ix()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x28) = *(short *)(var1 + 0x28) + 1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00911db0
void inc_iy()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x2c) = *(short *)(var1 + 0x2c) + 1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00911dd0
void inc_sp()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x24) += 1;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911df0
void dec_bc()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 4) += 0xffff;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911e10
void dec_de()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 8) += 0xffff;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911e30
void dec_hl()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0xc) += 0xffff;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911e50
void dec_ix()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x28) += 0xffff;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00911e70
void dec_iy()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x2c) = *(unsigned short *)(var1 + 0x2c) + 0xffff;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00911e90
void dec_sp()
{
	char *var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) = *(unsigned short *)(var1 + 0x24) + 0xffff;
	*(int *)(var1 + 0x50) = 6;
}

// FUNCTION: SADX 0x00911eb0
void jp_n()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00911ee0
void jp_xhl()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x20) = *(short *)(var1 + 0xc);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00911f00
void jp_xix()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x20) = *(short *)(var1 + 0x28);
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00911f20
void jp_xiy()
{
	char *var1 = DAT_060ee5b8;
	*(short *)(var1 + 0x20) = *(short *)(var1 + 0x2c);
	*(int *)(var1 + 0x50) = 8;
}

// STUB: SADX 0x00911f40
void jp_c_n()
{
}

// STUB: SADX 0x00911f80
void jp_z_n()
{
}

// STUB: SADX 0x00911fc0
void jp_p_n()
{
}

// STUB: SADX 0x00912000
void jp_s_n()
{
}

// STUB: SADX 0x00912040
void jp_nc_n()
{
}

// STUB: SADX 0x00912080
void jp_nz_n()
{
}

// STUB: SADX 0x009120c0
void jp_np_n()
{
}

// STUB: SADX 0x00912100
void jp_ns_n()
{
}

// STUB: SADX 0x00912140
void jr_e()
{
}

// STUB: SADX 0x00912170
void jr_c_e()
{
}

// STUB: SADX 0x009121b0
void jr_z_e()
{
}

// STUB: SADX 0x009121f0
void jr_nc_e()
{
}

// STUB: SADX 0x00912230
void jr_nz_e()
{
}

// STUB: SADX 0x00912270
void djnz()
{
}

// FUNCTION: SADX 0x009122b0
void FUN_009122b0()
{
	char *var1;
	unsigned short var2;

	var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 2;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = var2;
	*(int *)(var1 + 0x50) = 0x11;
}

// FUNCTION: SADX 0x00912300
void FUN_00912300()
{
	char *var1;

	var1 = DAT_060ee5b8;
	if (*(unsigned char *)var1 & 1)
	{
		unsigned short var2;

		var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x00912360
void FUN_00912360()
{
	char *var1;

	var1 = DAT_060ee5b8;
	if (*(unsigned char *)var1 & 0x40)
	{
		unsigned short var2;

		var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x009123c0
void FUN_009123c0()
{
	char *var1;

	var1 = DAT_060ee5b8;
	if (*(unsigned char *)var1 & 4)
	{
		unsigned short var2;

		var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x00912420
void FUN_00912420()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var2;

	if (*(unsigned char *)var1 & 0x80)
	{
		var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x00912480
void FUN_00912480()
{
	char *var1;

	var1 = DAT_060ee5b8;
	if ((*var1 & 1) == 0)
	{
		unsigned short var2;

		var2 = (unsigned short)FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x009124e0
void FUN_009124e0()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var3;

	if ((*var1 & 0x40) == 0)
	{
		var3 = FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var3;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x00912540
void FUN_00912540()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var3;

	if ((*var1 & 4) == 0)
	{
		var3 = FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var3;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x009125a0
void FUN_009125a0()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var3;

	if ((*var1 & 0x80) == 0)
	{
		var3 = FUN_0090ccd0(*(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) += 2;
		*(unsigned short *)(var1 + 0x24) += 0xfffe;
		Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x20) = var3;
		*(int *)(var1 + 0x50) = 0x11;
	}
	else
	{
		*(unsigned short *)(var1 + 0x20) += 2;
		*(int *)(var1 + 0x50) = 0xa;
	}
}

// FUNCTION: SADX 0x00912600
void ret()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xa;
}

// FUNCTION: SADX 0x00912630
void ret_c()
{
	char *var1;
	int iVar1;

	if ((*(char *)DAT_060ee5b8 & 1) != 0)
	{
		iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x00912670
void ret_z()
{
	if (*(unsigned char *)DAT_060ee5b8 & 0x40)
	{
		int var2 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		char *var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = var2;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x009126b0
void ret_p()
{
	if (*(unsigned char *)DAT_060ee5b8 & 4)
	{
		int var2 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		char *var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)var2;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x009126f0
void ret_s()
{
	char *var1;
	int iVar1;

	if ((*(char *)DAT_060ee5b8 & 0x80) != 0)
	{
		iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x00912730
void ret_nc()
{
	if ((*DAT_060ee5b8 & 1) == 0)
	{
		int var2 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		char *var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) = *(unsigned short *)(var1 + 0x24) + 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)var2;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x00912770
void ret_nz()
{
	char *var1 = DAT_060ee5b8;
	int iVar1;

	if ((*(unsigned char *)var1 & 0x40) == 0)
	{
		iVar1 = FUN_0090ccd0(*(unsigned short *)(var1 + 0x24));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)(var1 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x009127b0
void ret_np()
{
	char *var1;
	int iVar1;

	if ((*(char *)DAT_060ee5b8 & 4) == 0)
	{
		iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x009127f0
void ret_ns()
{
	char *var1;
	int iVar1;

	if ((*(char *)DAT_060ee5b8 & 0x80) == 0)
	{
		iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
		var1 = DAT_060ee5b8;
		*(unsigned short *)(var1 + 0x24) += 2;
		*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
		*(int *)(var1 + 0x50) = 0xb;
	}
	else
	{
		*(int *)((char *)DAT_060ee5b8 + 0x50) = 5;
	}
}

// FUNCTION: SADX 0x00912830
void reti()
{
	char *var1;
	int iVar1;

	iVar1 = FUN_0090ccd0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x24));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 2;
	*(unsigned short *)(var1 + 0x20) = (unsigned short)iVar1;
	*(int *)(var1 + 0x50) = 0xe;
}

// FUNCTION: SADX 0x00912860
void FUN_00912860()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009128a0
void FUN_009128a0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 8;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009128e0
void FUN_009128e0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x10;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00912920
void FUN_00912920()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x18;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00912960
void FUN_00912960()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x20;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009129a0
void FUN_009129a0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x28;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009129e0
void FUN_009129e0()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x30;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00912a20
void FUN_00912a20()
{
	char *var1;
	unsigned short var2;

	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	var2 = *(unsigned short *)(var1 + 0x20);
	Z80_Write2(*(unsigned short *)(var1 + 0x24), var2);
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) = 0x38;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00912a60
void ex_de_hl()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var2 = *(unsigned short *)(var1 + 8);
	*(unsigned short *)(var1 + 8) = *(unsigned short *)(var1 + 0xc);
	*(unsigned short *)(var1 + 0xc) = var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00912a80
void ex_af_af()
{
	char *var1 = DAT_060ee5b8;
	unsigned short var2 = *(unsigned short *)var1;
	*(unsigned short *)var1 = *(unsigned short *)(var1 + 0x10);
	*(unsigned short *)(var1 + 0x10) = var2;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00912aa0
void ex_x()
{
	unsigned short *var1 = (unsigned short *)DAT_060ee5b8;
	unsigned short var2;

	var2 = var1[2];
	var1[2] = var1[10];
	var1[10] = var2;
	var2 = var1[4];
	var1[4] = var1[12];
	var1[12] = var2;
	var2 = var1[6];
	var1[6] = var1[14];
	var1[14] = var2;
	*(int *)(var1 + 0x28) = 4;
}

// STUB: SADX 0x00912ae0
void FUN_00912ae0()
{
}

// STUB: SADX 0x00912b20
void FUN_00912b20()
{
}

// STUB: SADX 0x00912b60
void FUN_00912b60()
{
}

// STUB: SADX 0x00912ba0
void ldi()
{
}

// STUB: SADX 0x00912c00
void ldir()
{
}

// STUB: SADX 0x00912c80
void ldd()
{
}

// STUB: SADX 0x00912ce0
void lddr()
{
}

// STUB: SADX 0x00912d60
void cpi()
{
}

// STUB: SADX 0x00912dd0
void cpir()
{
}

// STUB: SADX 0x00912e60
void cpd()
{
}

// STUB: SADX 0x00912ed0
void cpdr()
{
}

// STUB: SADX 0x00912f60
void daa()
{
}

// FUNCTION: SADX 0x00912fe0
void cpl()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0) |= 0x12;
	var1[1] = (char)(~var1[1]);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00913000
void neg()
{
	char *var1;
	int var2;
	int var3;

	var1 = DAT_060ee5b8;
	var3 = *(unsigned char *)(var1 + 1);
	var2 = -var3;
	*(unsigned char *)(var1 + 1) = 0;
	*(unsigned char *)var1 = (char)((var2 >> 5) & (var3 >> 5) & 4) | (char)DAT_060ee6c8[var2 & 0xff] | (char)((var3 ^ (char)var2) & 0x10) | (char)((var2 >> 8) & 1) | 2;
	*(unsigned char *)(var1 + 1) = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00913060
void ccf()
{
	char *var1 = DAT_060ee5b8;
	*var1 = (char)((((*var1 & 1) << 4) | (*var1 & 0xc5)) ^ 1);
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x00913090
void scf()
{
	char *var1 = DAT_060ee5b8;
	var1[0] = (var1[0] & 0xc5) | 1;
	*(int *)(var1 + 0x50) = 4;
}

// FUNCTION: SADX 0x009130b0
void in_a_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090cc60((int)(unsigned char)FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20))));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009130e0
void in_a_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 1) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00913120
void in_b_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) = uVar1;
	*(unsigned char *)var1 = (*(unsigned char *)var1 & 1) | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00913160
void in_c_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 4) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009131a0
void in_d_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 9) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009131e0
void in_e_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 8) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00913220
void in_h_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 0xd) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x00913260
void in_l_c()
{
	char *var1;
	unsigned char uVar1;

	uVar1 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 0xc) = uVar1;
	*(unsigned char *)var1 = *(unsigned char *)var1 & 1 | DAT_060ee5c0[uVar1];
	*(int *)(var1 + 0x50) = 0xb;
}

// FUNCTION: SADX 0x009132a0
void ini()
{
	unsigned char uVar2;
	char *var1;

	uVar2 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), uVar2);
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) = *(unsigned char *)(var1 + 5) - 1;
	*(unsigned short *)(var1 + 0xc) = *(unsigned short *)(var1 + 0xc) + 1;
	*(unsigned char *)var1 = (unsigned char)((*(unsigned char *)(var1 + 5) != 0) - 1 & 0x40 | *(unsigned char *)var1 & 0x97 | 2);
	*(int *)(var1 + 0x50) = 0x10;
}

// FUNCTION: SADX 0x00913300
void inir()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), var2);
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) -= 1;
	*(unsigned short *)(var1 + 0xc) += 1;
	*var1 = ((*(unsigned char *)(var1 + 5) != 0) - 1) & 0x40 | *var1 & 0x97 | 2;
	if (*(unsigned short *)(var1 + 4) != 0 && (*var1 & 0x40) == 0)
	{
		*(unsigned short *)(var1 + 0x20) += 0xfffe;
		*(int *)(var1 + 0x50) = 0x15;
		return;
	}
	*(int *)(var1 + 0x50) = 0x10;
}

// FUNCTION: SADX 0x00913370
void ind()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090cc60(*(unsigned char *)((char *)DAT_060ee5b8 + 4));
	FUN_0090ccf0(*(unsigned short *)((char *)DAT_060ee5b8 + 0xc), var2);
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) -= 1;
	*(unsigned short *)(var1 + 0xc) += 0xffff;
	*var1 = ((*(unsigned char *)(var1 + 5) != 0) - 1) & 0x40 | *var1 & 0x97 | 2;
}

// FUNCTION: SADX 0x009133c0
void indr()
{
	char *var1;
	unsigned char var2;

	var2 = FUN_0090cc60(*(unsigned char *)(DAT_060ee5b8 + 4));
	FUN_0090ccf0(*(unsigned short *)(DAT_060ee5b8 + 0xc), var2);
	var1 = DAT_060ee5b8;
	*(unsigned char *)(var1 + 5) -= 1;
	*(unsigned short *)(var1 + 0xc) -= 1;
	*(unsigned char *)var1 = ((*(unsigned char *)(var1 + 5) != 0) - 1) & 0x40 | (*(unsigned char *)var1 & 0x97) | 2;
	if (*(unsigned short *)(var1 + 4) == 0 || (*((unsigned char *)var1) & 0x40) != 0)
	{
		*(int *)(var1 + 0x50) = 0x10;
		return;
	}
	*(unsigned short *)(var1 + 0x20) -= 2;
	*(int *)(var1 + 0x50) = 0x15;
}

// STUB: SADX 0x00913440
void out_n_a()
{
}

// STUB: SADX 0x00913480
void out_c_a()
{
}

// STUB: SADX 0x009134b0
void out_c_b()
{
}

// STUB: SADX 0x009134e0
void out_c_c()
{
}

// STUB: SADX 0x00913510
void out_c_d()
{
}

// STUB: SADX 0x00913540
void out_c_e()
{
}

// STUB: SADX 0x00913570
void out_c_h()
{
}

// STUB: SADX 0x009135a0
void out_c_l()
{
}

// STUB: SADX 0x009135d0
void outi()
{
}

// STUB: SADX 0x00913620
void otir()
{
}

// STUB: SADX 0x00913690
void outd()
{
}

// STUB: SADX 0x009136e0
void otdr()
{
}

// STUB: SADX 0x00913760
void rlc_a()
{
}

// STUB: SADX 0x00913790
void rlc_b()
{
}

// STUB: SADX 0x009137c0
void rlc_c()
{
}

// STUB: SADX 0x009137f0
void rlc_d()
{
}

// STUB: SADX 0x00913820
void rlc_e()
{
}

// STUB: SADX 0x00913850
void rlc_h()
{
}

// STUB: SADX 0x00913880
void rlc_l()
{
}

// STUB: SADX 0x009138b0
void rlc_xhl()
{
}

// STUB: SADX 0x00913910
void rlc_xix()
{
}

// STUB: SADX 0x00913980
void rlc_xiy()
{
}

// STUB: SADX 0x009139f0
void rlca()
{
}

// STUB: SADX 0x00913a20
void rl_a()
{
}

// STUB: SADX 0x00913a60
void rl_b()
{
}

// STUB: SADX 0x00913aa0
void rl_c()
{
}

// STUB: SADX 0x00913ae0
void rl_d()
{
}

// STUB: SADX 0x00913b20
void rl_e()
{
}

// STUB: SADX 0x00913b60
void rl_h()
{
}

// STUB: SADX 0x00913ba0
void rl_l()
{
}

// STUB: SADX 0x00913be0
void rl_xhl()
{
}

// STUB: SADX 0x00913c40
void rl_xix()
{
}

// STUB: SADX 0x00913cb0
void rl_xiy()
{
}

// STUB: SADX 0x00913d20
void rla()
{
}

// STUB: SADX 0x00913d60
void rrc_a()
{
}

// STUB: SADX 0x00913da0
void rrc_b()
{
}

// STUB: SADX 0x00913de0
void rrc_c()
{
}

// STUB: SADX 0x00913e20
void rrc_d()
{
}

// STUB: SADX 0x00913e60
void rrc_e()
{
}

// FUNCTION: SADX 0x00913ea0
void rrc_h()
{
	char *var1;
	unsigned char var2;
	int var3;

	var1 = DAT_060ee5b8;
	var2 = *(unsigned char *)(var1 + 0xd);
	var3 = (int)*(unsigned char *)(var1 + 0xd);
	var3 &= 1;
	*(unsigned char *)(var1 + 0xd) = (char)((var3 ? 0x80 : 0) | (var2 >> 1));
	*(unsigned char *)var1 = (char)((var3 ? 1 : 0) | (char)DAT_060ee5c0[*(unsigned char *)(var1 + 0xd)]);
	*(int *)(var1 + 0x50) = 8;
}

// STUB: SADX 0x00913ee0
void rrc_l()
{
}

// STUB: SADX 0x00913f20
void rrc_xhl()
{
}

// STUB: SADX 0x00913f80
void rrc_xix()
{
}

// STUB: SADX 0x00913ff0
void rrc_xiy()
{
}

// STUB: SADX 0x00914060
void rrca()
{
}

// STUB: SADX 0x009140a0
void rr_a()
{
}

// STUB: SADX 0x009140e0
void rr_b()
{
}

// STUB: SADX 0x00914120
void rr_c()
{
}

// STUB: SADX 0x00914160
void rr_d()
{
}

// STUB: SADX 0x009141a0
void rr_e()
{
}

// STUB: SADX 0x009141e0
void rr_h()
{
}

// STUB: SADX 0x00914220
void rr_l()
{
}

// STUB: SADX 0x00914260
void rr_xhl()
{
}

// STUB: SADX 0x009142c0
void rr_xix()
{
}

// STUB: SADX 0x00914330
void rr_xiy()
{
}

// STUB: SADX 0x009143a0
void rra()
{
}

// STUB: SADX 0x009143e0
void sla_a()
{
}

// STUB: SADX 0x00914410
void sla_b()
{
}

// STUB: SADX 0x00914440
void sla_c()
{
}

// STUB: SADX 0x00914470
void sla_d()
{
}

// STUB: SADX 0x009144a0
void sla_e()
{
}

// STUB: SADX 0x009144d0
void sla_h()
{
}

// STUB: SADX 0x00914500
void sla_l()
{
}

// STUB: SADX 0x00914530
void sla_xhl()
{
}

// STUB: SADX 0x00914590
void sla_xix()
{
}

// STUB: SADX 0x00914600
void sla_xiy()
{
}

// STUB: SADX 0x00914670
void sra_a()
{
}

// STUB: SADX 0x009146b0
void sra_b()
{
}

// STUB: SADX 0x009146f0
void sra_c()
{
}

// STUB: SADX 0x00914730
void sra_d()
{
}

// STUB: SADX 0x00914770
void sra_e()
{
}

// STUB: SADX 0x009147b0
void sra_h()
{
}

// STUB: SADX 0x009147f0
void sra_l()
{
}

// STUB: SADX 0x00914830
void sra_xhl()
{
}

// STUB: SADX 0x00914890
void sra_xix()
{
}

// STUB: SADX 0x00914900
void sra_xiy()
{
}

// STUB: SADX 0x00914970
void sll_a()
{
}

// STUB: SADX 0x009149a0
void sll_b()
{
}

// STUB: SADX 0x009149d0
void sll_c()
{
}

// STUB: SADX 0x00914a00
void sll_d()
{
}

// STUB: SADX 0x00914a30
void sll_e()
{
}

// STUB: SADX 0x00914a60
void sll_h()
{
}

// STUB: SADX 0x00914a90
void sll_l()
{
}

// STUB: SADX 0x00914ac0
void sll_xhl()
{
}

// STUB: SADX 0x00914b20
void sll_xix()
{
}

// STUB: SADX 0x00914b90
void sll_xiy()
{
}

// STUB: SADX 0x00914c00
void srl_a()
{
}

// STUB: SADX 0x00914c30
void srl_b()
{
}

// STUB: SADX 0x00914c60
void srl_c()
{
}

// STUB: SADX 0x00914c90
void srl_d()
{
}

// STUB: SADX 0x00914cc0
void srl_e()
{
}

// STUB: SADX 0x00914cf0
void srl_h()
{
}

// STUB: SADX 0x00914d20
void srl_l()
{
}

// STUB: SADX 0x00914d50
void srl_xhl()
{
}

// STUB: SADX 0x00914da0
void srl_xix()
{
}

// STUB: SADX 0x00914e00
void srl_xiy()
{
}

// STUB: SADX 0x00914e60
void rld()
{
}

// STUB: SADX 0x00914ed0
void rrd()
{
}

// FUNCTION: SADX 0x00914f40
void bit_0_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00914f70
void bit_1_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00914fa0
void bit_2_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00914fd0
void bit_3_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915000
void bit_4_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915030
void bit_5_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915060
void bit_6_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915090
void bit_7_a()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & 0x80) != 0;
	*var1 = (var2 ? 0x3c : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009150c0
void bit_0_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009150f0
void bit_1_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915120
void bit_2_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915150
void bit_3_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915180
void bit_4_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009151b0
void bit_5_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009151e0
void bit_6_b()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[5] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915210
void bit_7_b()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[5] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915240
void bit_0_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915270
void bit_1_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009152a0
void bit_2_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009152d0
void bit_3_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915300
void bit_4_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 0x10) ? 0 : 0x44;
	var1[0] = (var2 | 0x10) | (var1[0] & 1);
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915330
void bit_5_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915360
void bit_6_c()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[4] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915390
void bit_7_c()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[4] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009153c0
void bit_0_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009153f0
void bit_1_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915420
void bit_2_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 4) ? 0xbc : 0;
	*var1 = (var2 + 0x44) | (*var1 & 1) | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915450
void bit_3_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915480
void bit_4_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009154b0
void bit_5_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 0x20) != 0;
	var1[0] = (char)((var2 ? 0xbc : 0) + 0x44) | (var1[0] & 1) | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009154e0
void bit_6_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915510
void bit_7_d()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[9] & 0x80) != 0;
	*var1 = (var2 ? 0x3c : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915540
void bit_0_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915570
void bit_1_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009155a0
void bit_2_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009155d0
void bit_3_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915600
void bit_4_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915630
void bit_5_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915660
void bit_6_e()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[8] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915690
void bit_7_e()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[8] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009156c0
void bit_0_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009156f0
void bit_1_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915720
void bit_2_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915750
void bit_3_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915780
void bit_4_h()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (var1[0xd] & 0x10) != 0 ? 0xbc : 0;
	var2 += 0x44;
	var2 |= var1[0] & 1;
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009157b0
void bit_5_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009157e0
void bit_6_h()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xd] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915810
void bit_7_h()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = var1[0xd] & 0x80;
	var2 = (var2 == 0) ? 0 : 0x3c;
	var2 = (var2 + 0x44) | (var1[0] & 1) | 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915840
void bit_0_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915870
void bit_1_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009158a0
void bit_2_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009158d0
void bit_3_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915900
void bit_4_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 0x10) != 0;
	var2 = (var2 ? 0xbc : 0) + 0x44;
	var2 |= var1[0] & 1;
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915930
void bit_5_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915960
void bit_6_l()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0xc] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00915990
void bit_7_l()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[0xc] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 8;
}

// STUB: SADX 0x009159c0
void bit_0_xhl()
{
}

// STUB: SADX 0x00915a00
void bit_1_xhl()
{
}

// STUB: SADX 0x00915a40
void bit_2_xhl()
{
}

// STUB: SADX 0x00915a80
void bit_3_xhl()
{
}

// STUB: SADX 0x00915ac0
void bit_4_xhl()
{
}

// STUB: SADX 0x00915b00
void bit_5_xhl()
{
}

// STUB: SADX 0x00915b40
void bit_6_xhl()
{
}

// STUB: SADX 0x00915b80
void bit_7_xhl()
{
}

// STUB: SADX 0x00915bc0
void bit_0_xix()
{
}

// STUB: SADX 0x00915c10
void bit_1_xix()
{
}

// STUB: SADX 0x00915c60
void bit_2_xix()
{
}

// STUB: SADX 0x00915cb0
void bit_3_xix()
{
}

// STUB: SADX 0x00915d00
void bit_4_xix()
{
}

// STUB: SADX 0x00915d50
void bit_5_xix()
{
}

// STUB: SADX 0x00915da0
void bit_6_xix()
{
}

// STUB: SADX 0x00915df0
void bit_7_xix()
{
}

// STUB: SADX 0x00915e40
void bit_0_xiy()
{
}

// STUB: SADX 0x00915e90
void bit_1_xiy()
{
}

// STUB: SADX 0x00915ee0
void bit_2_xiy()
{
}

// STUB: SADX 0x00915f30
void bit_3_xiy()
{
}

// STUB: SADX 0x00915f80
void bit_4_xiy()
{
}

// STUB: SADX 0x00915fd0
void bit_5_xiy()
{
}

// STUB: SADX 0x00916020
void bit_6_xiy()
{
}

// STUB: SADX 0x00916070
void bit_7_xiy()
{
}

// FUNCTION: SADX 0x009160c0
void set_0_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009160e0
void set_1_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916100
void set_2_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916120
void set_3_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916140
void set_4_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916160
void set_5_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916180
void set_6_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009161a0
void set_7_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[1] | 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009161c0
void set_0_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009161e0
void set_1_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916200
void set_2_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916220
void set_3_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916240
void set_4_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916260
void set_5_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916280
void set_6_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009162a0
void set_7_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] | 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009162c0
void set_0_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009162e0
void set_1_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916300
void set_2_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] |= 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916320
void set_3_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] | 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916340
void set_4_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] |= 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916360
void set_5_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] |= 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916380
void set_6_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] |= 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009163a0
void set_7_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] | 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009163c0
void set_0_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009163e0
void set_1_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916400
void set_2_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916420
void set_3_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916440
void set_4_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916460
void set_5_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916480
void set_6_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009164a0
void set_7_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] | 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009164c0
void set_0_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[8] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009164e0
void set_1_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[8] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916500
void set_2_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] |= 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916520
void set_3_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] |= 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916540
void set_4_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] |= 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916560
void set_5_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[8] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916580
void set_6_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] |= 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009165a0
void set_7_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] |= 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009165c0
void set_0_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009165e0
void set_1_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916600
void set_2_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] |= 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916620
void set_3_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] |= 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916640
void set_4_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] |= 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916660
void set_5_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916680
void set_6_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] | 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009166a0
void set_7_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] | 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009166c0
void set_0_l()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[0xc] | 1;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009166e0
void set_1_l()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[0xc] | 2;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916700
void set_2_l()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[0xc] | 4;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916720
void set_3_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) |= 8;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916740
void set_4_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) |= 0x10;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916760
void set_5_l()
{
	char *var1 = DAT_060ee5b8;
	var1[0xc] = var1[0xc] | 0x20;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00916780
void set_6_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) |= 0x40;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009167a0
void set_7_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) |= 0x80;
	*(int *)(var1 + 0x50) = 8;
}

// STUB: SADX 0x009167c0
void set_0_xhl()
{
}

// STUB: SADX 0x00916800
void set_1_xhl()
{
}

// STUB: SADX 0x00916840
void set_2_xhl()
{
}

// STUB: SADX 0x00916880
void set_3_xhl()
{
}

// STUB: SADX 0x009168c0
void set_4_xhl()
{
}

// STUB: SADX 0x00916900
void set_5_xhl()
{
}

// STUB: SADX 0x00916940
void set_6_xhl()
{
}

// STUB: SADX 0x00916980
void set_7_xhl()
{
}

// STUB: SADX 0x009169c0
void set_0_xix()
{
}

// STUB: SADX 0x00916a30
void set_1_xix()
{
}

// STUB: SADX 0x00916aa0
void set_2_xix()
{
}

// STUB: SADX 0x00916b10
void set_3_xix()
{
}

// STUB: SADX 0x00916b80
void set_4_xix()
{
}

// STUB: SADX 0x00916bf0
void set_5_xix()
{
}

// STUB: SADX 0x00916c60
void set_6_xix()
{
}

// STUB: SADX 0x00916cd0
void set_7_xix()
{
}

// STUB: SADX 0x00916d40
void set_0_xiy()
{
}

// STUB: SADX 0x00916db0
void set_1_xiy()
{
}

// STUB: SADX 0x00916e20
void set_2_xiy()
{
}

// STUB: SADX 0x00916e90
void set_3_xiy()
{
}

// STUB: SADX 0x00916f00
void set_4_xiy()
{
}

// STUB: SADX 0x00916f70
void set_5_xiy()
{
}

// STUB: SADX 0x00916fe0
void set_6_xiy()
{
}

// STUB: SADX 0x00917050
void set_7_xiy()
{
}

// FUNCTION: SADX 0x009170c0
void res_0_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] &= 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009170e0
void res_1_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917100
void res_2_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) = *(char *)(var1 + 1) & 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917120
void res_3_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917140
void res_4_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) = *(char *)(var1 + 1) & 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917160
void res_5_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) = *(char *)(var1 + 1) & 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917180
void res_6_a()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = (char)(var1[1] & 0xbf);
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009171a0
void res_7_a()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 1) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009171c0
void res_0_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] & 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009171e0
void res_1_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917200
void res_2_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917220
void res_3_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917240
void res_4_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) = *(char *)(var1 + 5) & 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917260
void res_5_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) &= 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917280
void res_6_b()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[5] & 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009172a0
void res_7_b()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 5) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009172c0
void res_0_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] & 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009172e0
void res_1_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 4) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917300
void res_2_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 4) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917320
void res_3_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 4) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917340
void res_4_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] & 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917360
void res_5_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] & 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917380
void res_6_c()
{
	char *var1 = DAT_060ee5b8;
	var1[4] = var1[4] & 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009173a0
void res_7_c()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 4) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009173c0
void res_0_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009173e0
void res_1_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917400
void res_2_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917420
void res_3_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917440
void res_4_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] & 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917460
void res_5_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917480
void res_6_d()
{
	char *var1 = DAT_060ee5b8;
	var1[9] = var1[9] & 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009174a0
void res_7_d()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 9) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009174c0
void res_0_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[8] & 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009174e0
void res_1_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917500
void res_2_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917520
void res_3_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917540
void res_4_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917560
void res_5_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917580
void res_6_e()
{
	char *var1 = DAT_060ee5b8;
	var1[8] = var1[8] & 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009175a0
void res_7_e()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 8) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009175c0
void res_0_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009175e0
void res_1_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917600
void res_2_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917620
void res_3_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917640
void res_4_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917660
void res_5_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917680
void res_6_h()
{
	char *var1 = DAT_060ee5b8;
	var1[0xd] = var1[0xd] & 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009176a0
void res_7_h()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xd) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009176c0
void res_0_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xfe;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009176e0
void res_1_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xfd;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917700
void res_2_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xfb;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917720
void res_3_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xf7;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917740
void res_4_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xef;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917760
void res_5_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xdf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x00917780
void res_6_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0xbf;
	*(int *)(var1 + 0x50) = 8;
}

// FUNCTION: SADX 0x009177a0
void res_7_l()
{
	char *var1 = DAT_060ee5b8;
	*(char *)(var1 + 0xc) &= 0x7f;
	*(int *)(var1 + 0x50) = 8;
}

// STUB: SADX 0x009177c0
void res_0_xhl()
{
}

// STUB: SADX 0x00917800
void res_1_xhl()
{
}

// STUB: SADX 0x00917840
void res_2_xhl()
{
}

// STUB: SADX 0x00917880
void res_3_xhl()
{
}

// STUB: SADX 0x009178c0
void res_4_xhl()
{
}

// STUB: SADX 0x00917900
void res_5_xhl()
{
}

// STUB: SADX 0x00917940
void res_6_xhl()
{
}

// STUB: SADX 0x00917980
void res_7_xhl()
{
}

// STUB: SADX 0x009179c0
void res_0_xix()
{
}

// STUB: SADX 0x00917a30
void res_1_xix()
{
}

// STUB: SADX 0x00917aa0
void res_2_xix()
{
}

// STUB: SADX 0x00917b10
void res_3_xix()
{
}

// STUB: SADX 0x00917b80
void res_4_xix()
{
}

// STUB: SADX 0x00917bf0
void res_5_xix()
{
}

// STUB: SADX 0x00917c60
void res_6_xix()
{
}

// STUB: SADX 0x00917cd0
void res_7_xix()
{
}

// STUB: SADX 0x00917d40
void res_0_xiy()
{
}

// STUB: SADX 0x00917db0
void res_1_xiy()
{
}

// STUB: SADX 0x00917e20
void res_2_xiy()
{
}

// STUB: SADX 0x00917e90
void res_3_xiy()
{
}

// STUB: SADX 0x00917f00
void res_4_xiy()
{
}

// STUB: SADX 0x00917f70
void res_5_xiy()
{
}

// STUB: SADX 0x00917fe0
void res_6_xiy()
{
}

// STUB: SADX 0x00918050
void res_7_xiy()
{
}

// FUNCTION: SADX 0x009180c0
void ld_ixh_b()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x29] = cVar1[5];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009180e0
void ld_ixh_c()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x29] = cVar1[4];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918100
void ld_ixh_d()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[9];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918120
void ld_ixh_e()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x29] = cVar1[8];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918230
void ld_ixl_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[1];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918250
void ld_iyh_b()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2d] = cVar1[5];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918270
void ld_iyh_c()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2d] = cVar1[4];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918290
void ld_iyh_d()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2d] = cVar1[9];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009182b0
void ld_iyh_e()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2d] = cVar1[8];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009182d0
void ld_iyh_iyl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2d] = cVar1[0x2c];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009182f0
void ld_iyh_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[1];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918310
void ld_iyl_b()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2c] = cVar1[5];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918330
void ld_iyl_c()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2c] = cVar1[4];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918350
void ld_iyl_d()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2c] = cVar1[9];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918370
void ld_iyl_e()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2c] = cVar1[8];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918390
void ld_iyl_iyh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[0x2c] = cVar1[0x2d];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009183b0
void ld_iyl_a()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[1];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009183d0
void ld_b_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[0x29];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009183f0
void ld_c_ixh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[0x29];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918410
void ld_d_ixh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[9] = cVar1[0x29];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918430
void ld_e_ixh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[8] = cVar1[0x29];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918450
void ld_a_ixh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[1] = cVar1[0x29];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918470
void ld_b_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[0x28];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918490
void ld_c_ixl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[0x28];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009184b0
void ld_d_ixl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[9] = cVar1[0x28];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009184d0
void ld_e_ixl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[8] = cVar1[0x28];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009184f0
void ld_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[0x28];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918510
void ld_b_iyh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[5] = cVar1[0x2d];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918530
void ld_c_iyh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[0x2d];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918550
void ld_d_iyh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[9] = cVar1[0x2d];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918570
void ld_e_iyh()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[8] = cVar1[0x2d];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918590
void ld_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[1] = var1[0x2d];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009185b0
void ld_b_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[5] = var1[0x2c];
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009185d0
void ld_c_iyl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[4] = cVar1[0x2c];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009185f0
void ld_d_iyl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[9] = cVar1[0x2c];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918610
void ld_e_iyl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[8] = cVar1[0x2c];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918630
void ld_a_iyl()
{
	char *cVar1;

	cVar1 = DAT_060ee5b8;
	cVar1[1] = cVar1[0x2c];
	*(int *)(cVar1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918650
void ld_ixh_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[0x29] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918680
void ld_ixl_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[0x28] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009186b0
void ld_iyh_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[0x2d] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009186e0
void ld_iyl_n()
{
	char *var1;
	char var2;

	var2 = (char)(FUN_0090ccb0(*(unsigned short *)((char *)DAT_060ee5b8 + 0x20)));
	var1 = DAT_060ee5b8;
	*(unsigned short *)(var1 + 0x20) += 1;
	var1[0x2c] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// STUB: SADX 0x00918710
void inc_ixh()
{
}

// STUB: SADX 0x00918760
void inc_ixl()
{
}

// STUB: SADX 0x009187b0
void inc_iyh()
{
}

// STUB: SADX 0x00918800
void inc_iyl()
{
}

// STUB: SADX 0x00918850
void dec_ixh()
{
}

// STUB: SADX 0x009188b0
void dec_ixl()
{
}

// STUB: SADX 0x00918910
void dec_iyh()
{
}

// STUB: SADX 0x00918970
void dec_iyl()
{
}

// STUB: SADX 0x009189d0
void add_a_ixh()
{
}

// STUB: SADX 0x00918a40
void add_a_ixl()
{
}

// STUB: SADX 0x00918ab0
void add_a_iyh()
{
}

// STUB: SADX 0x00918b20
void add_a_iyl()
{
}

// FUNCTION: SADX 0x00918b90
void adc_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 0x29);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 0x29) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 0x29) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x29) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918c00
void adc_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 0x2d);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 0x2d) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 0x2d) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2d) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918c70
void adc_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = (*(unsigned char *)var1 & 1) + *(unsigned char *)(var1 + 1) + *(unsigned char *)(var1 + 0x2c);
	var3 = ((*(unsigned char *)(var1 + 1) >> 5) ^ ~(*(unsigned char *)(var1 + 0x2c) >> 5)) & ((var2 >> 5) ^ (*(unsigned char *)(var1 + 0x2c) >> 5)) & 4;
	var4 = (*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2c) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918ce0
void sub_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x29);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x29)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x29)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918d40
void sub_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x28);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x28)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x28)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918da0
void sub_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x2d);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2d)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2d)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00918e00
void sub_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x2c);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2c)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2c)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(unsigned char *)(var1 + 1) = (unsigned char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// STUB: SADX 0x00918e60
void sbc_a_ixh()
{
}

// STUB: SADX 0x00918ed0
void sbc_a_ixl()
{
}

// STUB: SADX 0x00918f40
void sbc_a_iyh()
{
}

// STUB: SADX 0x00918fb0
void sbc_a_iyl()
{
}

// FUNCTION: SADX 0x00919020
void and_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[0x29];
	*(unsigned char *)var1 = (unsigned char)DAT_060ee5c0[var2] | 0x10;
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919050
void and_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[0x28];
	*(unsigned char *)var1 = (unsigned char)DAT_060ee5c0[var2] | 0x10;
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919080
void and_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] & (unsigned char)var1[0x2d];
	*(unsigned char *)var1 = (unsigned char)DAT_060ee5c0[var2] | 0x10;
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009190b0
void and_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[1] & var1[0x2c]) & 0xff;
	var1[0] = DAT_060ee5c0[var2] | 0x10;
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009190e0
void xor_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[0x29];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919110
void xor_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = *(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x28);
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919140
void xor_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[0x2d];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919170
void xor_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] ^ (unsigned char)var1[0x2c];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009191a0
void or_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[1] | (unsigned char)var1[0x29];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009191d0
void or_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (unsigned char)var1[0x28] | (unsigned char)var1[1];
	var1[0] = *(char *)(var2 + (int)DAT_060ee5c0);
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919200
void or_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = *(unsigned char *)(var1 + 0x2d) | *(unsigned char *)(var1 + 1);
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919230
void or_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	unsigned int var2 = (unsigned char)var1[0x2c] | (unsigned char)var1[1];
	var1[0] = DAT_060ee5c0[var2];
	var1[1] = (char)var2;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919260
void cp_a_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x29);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x29)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x29)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x009192c0
void cp_a_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x28);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x28)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x28)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919320
void cp_a_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x2d);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2d)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2d)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 9;
}

// FUNCTION: SADX 0x00919380
void cp_a_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2;
	unsigned char var3;
	unsigned char var4;

	var2 = *(unsigned char *)(var1 + 1) - *(unsigned char *)(var1 + 0x2c);
	var3 = ((var2 >> 5) ^ (*(unsigned char *)(var1 + 1) >> 5)) & ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2c)) >> 5) & 4;
	var4 = ((*(unsigned char *)(var1 + 1) ^ *(unsigned char *)(var1 + 0x2c)) ^ (unsigned char)var2) & 0x10;
	var3 |= var4;
	var3 |= DAT_060ee6c8[var2 & 0xff];
	var3 |= (var2 >> 8) & 1;
	var3 |= 2;
	*(unsigned char *)var1 = var3;
	*(int *)(var1 + 0x50) = 9;
}

// STUB: SADX 0x009193e0
void rlc_ixh()
{
}

// STUB: SADX 0x00919410
void rlc_ixl()
{
}

// STUB: SADX 0x00919440
void rlc_iyh()
{
}

// STUB: SADX 0x00919470
void rlc_iyl()
{
}

// STUB: SADX 0x009194a0
void rrc_ixh()
{
}

// STUB: SADX 0x009194e0
void rrc_ixl()
{
}

// STUB: SADX 0x00919520
void rrc_iyh()
{
}

// STUB: SADX 0x00919560
void rrc_iyl()
{
}

// STUB: SADX 0x009195a0
void rl_ixh()
{
}

// STUB: SADX 0x009195e0
void rl_ixl()
{
}

// STUB: SADX 0x00919620
void rl_iyh()
{
}

// STUB: SADX 0x00919660
void rl_iyl()
{
}

// STUB: SADX 0x009196a0
void rr_ixh()
{
}

// STUB: SADX 0x009196e0
void rr_ixl()
{
}

// STUB: SADX 0x00919720
void rr_iyh()
{
}

// STUB: SADX 0x00919760
void rr_iyl()
{
}

// STUB: SADX 0x009197a0
void sla_ixh()
{
}

// STUB: SADX 0x009197d0
void sla_ixl()
{
}

// STUB: SADX 0x00919800
void sla_iyh()
{
}

// STUB: SADX 0x00919830
void sla_iyl()
{
}

// STUB: SADX 0x00919860
void sra_ixh()
{
}

// STUB: SADX 0x009198a0
void sra_ixl()
{
}

// STUB: SADX 0x009198e0
void sra_iyh()
{
}

// STUB: SADX 0x00919920
void sra_iyl()
{
}

// STUB: SADX 0x00919960
void sll_ixh()
{
}

// STUB: SADX 0x00919990
void sll_ixl()
{
}

// STUB: SADX 0x009199c0
void sll_iyh()
{
}

// STUB: SADX 0x009199f0
void sll_iyl()
{
}

// STUB: SADX 0x00919a20
void srl_ixh()
{
}

// STUB: SADX 0x00919a50
void srl_ixl()
{
}

// STUB: SADX 0x00919a80
void srl_iyh()
{
}

// STUB: SADX 0x00919ab0
void srl_iyl()
{
}

// FUNCTION: SADX 0x00919ae0
void bit_0_ixh()
{
	char *var1 = DAT_060ee5b8;
	char var2 = (var1[0x29] & 1) ? -1 : 0;
	char var3 = (char)((var2 & 0xbc) + 0x44 | (var1[0] & 1) | 0x10);
	var1[0] = var3;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919b10
void bit_1_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919b40
void bit_2_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919b70
void bit_3_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919ba0
void bit_4_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919bd0
void bit_5_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919c00
void bit_6_ixh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x29] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919c30
void bit_7_ixh()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[0x29] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919c60
void bit_0_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919c90
void bit_1_ixl()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = *(unsigned char *)(var1 + 0x28);
	unsigned char var3 = *(unsigned char *)var1;
	var2 = (var2 & 2) ? 0xbc : 0;
	var2 = var2 + 0x44;
	var2 = var2 | (var3 & 1);
	var2 = var2 | 0x10;
	*(unsigned char *)var1 = var2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919cc0
void bit_2_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919cf0
void bit_3_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919d20
void bit_4_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919d50
void bit_5_ixl()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (var1[0x28] & 0x20) != 0 ? 0xbc : 0;
	unsigned char var3 = var1[0] & 1;
	unsigned char var4 = (var2 + 0x44) | var3 | 0x10;
	var1[0] = var4;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919d80
void bit_6_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919db0
void bit_7_ixl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x28] & 0x80) != 0;
	*var1 = (var2 ? 0x3c : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919de0
void bit_0_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919e10
void bit_1_iyh()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (var1[0x2d] & 2) != 0 ? 0xbc : 0;
	unsigned char var3 = var1[0] & 1;
	var2 += 0x44;
	var2 |= var3;
	var2 |= 0x10;
	var1[0] = var2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919e40
void bit_2_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919e70
void bit_3_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919ea0
void bit_4_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919ed0
void bit_5_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919f00
void bit_6_iyh()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2d] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919f30
void bit_7_iyh()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[0x2d] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919f60
void bit_0_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 1) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919f90
void bit_1_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 2) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919fc0
void bit_2_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 4) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x00919ff0
void bit_3_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 8) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a020
void bit_4_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 0x10) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a050
void bit_5_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 0x20) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a080
void bit_6_iyl()
{
	char *var1 = DAT_060ee5b8;
	int var2 = (var1[0x2c] & 0x40) != 0;
	*var1 = (var2 ? 0xbc : 0) + 0x44 | *var1 & 1 | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a0b0
void bit_7_iyl()
{
	char *var1 = DAT_060ee5b8;
	unsigned char var2 = (unsigned char)((var1[0x2c] & 0x80) ? 0x3c : 0) + 0x44;
	var2 |= (unsigned char)(var1[0] & 1);
	var2 |= 0x10;
	var1[0] = (char)var2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a0e0
void res_0_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xfe;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a100
void res_1_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xfd;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a120
void res_2_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xfb;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a140
void res_3_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xf7;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a160
void res_4_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xef;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a180
void res_5_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xdf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a1a0
void res_6_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0xbf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a1c0
void res_7_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] &= 0x7f;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a1e0
void res_0_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xfe;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a200
void res_1_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xfd;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a220
void res_2_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xfb;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a240
void res_3_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xf7;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a260
void res_4_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xef;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a280
void res_5_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xdf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a2a0
void res_6_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0xbf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a2c0
void res_7_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] &= 0x7f;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a2e0
void res_0_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xfe;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a300
void res_1_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xfd;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a320
void res_2_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xfb;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a340
void res_3_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xf7;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a360
void res_4_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xef;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a380
void res_5_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xdf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a3a0
void res_6_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0xbf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a3c0
void res_7_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] &= 0x7f;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a3e0
void res_0_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xfe;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a400
void res_1_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xfd;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a420
void res_2_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xfb;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a440
void res_3_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xf7;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a460
void res_4_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xef;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a480
void res_5_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xdf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a4a0
void res_6_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0xbf;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a4c0
void res_7_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] &= 0x7f;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a4e0
void set_0_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 1;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a500
void set_1_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a520
void set_2_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 4;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a540
void set_3_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 8;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a560
void set_4_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a580
void set_5_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 0x20;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a5a0
void set_6_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 0x40;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a5c0
void set_7_ixh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x29] = var1[0x29] | 0x80;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a5e0
void set_0_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 1;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a600
void set_1_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a620
void set_2_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 4;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a640
void set_3_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 8;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a660
void set_4_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a680
void set_5_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 0x20;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a6a0
void set_6_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 0x40;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a6c0
void set_7_ixl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x28] = var1[0x28] | 0x80;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a6e0
void set_0_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 1;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a700
void set_1_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a720
void set_2_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 4;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a740
void set_3_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 8;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a760
void set_4_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a780
void set_5_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 0x20;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a7a0
void set_6_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 0x40;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a7c0
void set_7_iyh()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2d] = var1[0x2d] | 0x80;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a7e0
void set_0_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 1;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a800
void set_1_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 2;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a820
void set_2_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 4;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a840
void set_3_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 8;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a860
void set_4_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 0x10;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a880
void set_5_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 0x20;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a8a0
void set_6_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 0x40;
	*(int *)(var1 + 0x50) = 0xd;
}

// FUNCTION: SADX 0x0091a8c0
void set_7_iyl()
{
	char *var1 = DAT_060ee5b8;
	var1[0x2c] = var1[0x2c] | 0x80;
	*(int *)(var1 + 0x50) = 0xd;
}

// STUB: SADX 0x0091a950
void op_fd_cb()
{
}

// STUB: SADX 0x0091a980
void dd_nop()
{
}

// STUB: SADX 0x0091a990
void op_fd()
{
}

// STUB: SADX 0x0091a9c0
void op_ed()
{
}

// STUB: SADX 0x0091aa20
void Z80_Reset(unsigned char *ram)
{
}

// FUNCTION: SADX 0x0091aa90
void SetWorkPointer(unsigned char *ram)
{
	DAT_060ee5b8 = (char *)ram;
}

// STUB: SADX 0x0091aaa0
int Z80(int cycle, int modCycle, int flag)
{
	return (int)0;
}

// STUB: SADX 0x0091ab50
void EXEC_ONE_OP()
{
}

// STUB: SADX 0x0091ab90
void Z80_Interrupt(int irq)
{
}

// FUNCTION: SADX 0x0091ac70
void Z80_NMI()
{
	char *var1;

	var1 = DAT_060ee5b8;
	if (*(int *)(var1 + 0x38) != 0)
	{
		*(unsigned short *)(var1 + 0x20) += 1;
		*(int *)(var1 + 0x38) = 0;
	}
	*(int *)(var1 + 0x3c) = 0;
	*(unsigned short *)(var1 + 0x24) += 0xfffe;
	Z80_Write2(*(unsigned short *)(var1 + 0x24), *(unsigned short *)(var1 + 0x20));
	var1 = DAT_060ee5b8;
	*(int *)(var1 + 0x4c) -= 0xb;
	*(unsigned short *)(var1 + 0x20) = 0x66;
	*(int *)(var1 + 0x5c) += 0xb;
	*(int *)(var1 + 0x54) += 0xb;
}

// FUNCTION: SADX 0x0091acc0
unsigned long GetCyclePoint()
{
	char *var1 = DAT_060ee5b8;
	return *(int *)(var1 + 0x60) + *(int *)(var1 + 0x5c);
}

// STUB: SADX 0x0091acd0
void ei()
{
}

// STUB: SADX 0x0091ad30
void retn()
{
}

// STUB: SADX 0x0091ad80
void BuildZ80(void *memp, unsigned char *ram)
{
}
