#include "decls.h"
#include <windows.h>
#include <string.h>
void FUN_006411b0(int param_1, int param_2);
extern int DAT_05b3e930;
extern int DAT_05b3e39c;
extern unsigned char DAT_05b3ea08;
extern int DAT_05b3e988[20];
int FUN_004aee80(int param_1, int param_2);
int FUN_004ae8c0(struct MDHANDLE *, char *);
extern int DAT_05b3e398;
extern int DAT_05b3e464;
extern int DAT_05b3ea00;
extern int DAT_05b3ea04;
extern unsigned short DAT_05b9d724;
extern unsigned short DAT_05b9d744;
void FUN_004afe30(void);

extern int DAT_05b3e46c[20][14];
extern int DAT_05b3e938[20];
extern int DAT_05a92330;
extern struct MDHANDLE *DAT_05b3e3a0[51];
extern char DAT_06276b20[260];

// FUNCTION: SADX 0x004ae460
void StopBankSound(int bank)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][3] != -1 && DAT_05b3e46c[local_8][12] == bank)
		{
			StopPCM(local_8);
			DAT_05b3e46c[local_8][0] = 0;
			DAT_05b3e46c[local_8][1] = 0;
			DAT_05b3e46c[local_8][2] = 0;
			DAT_05b3e46c[local_8][3] = -1;
			DAT_05b3e938[local_8] = 0;
		}
	}
}

// FUNCTION: SADX 0x004ae500
int SetBankDir(int num)
{
	int local_8g;
	struct MDHANDLE *local_118g;
	char local_114[264];

	if (num >= 0x7b)
	{
		return 0;
	}
	if (IsSoundSystem() && DAT_05a92330)
	{
		for (local_8g = 0; local_8g < allsedata[num].datasize; local_8g++)
		{
			if (DAT_05b3e3a0[((struct bankdata *)allsedata[num].data)[local_8g].banknum])
			{
				wsprintfA(local_114, "%sSoundData\\SE\\%s.dat", "SYSTEM\\", allsedata[num].data[local_8g].bankfilename);
				if (!_stricmp(local_114, *(char **)((char *)DAT_05b3e3a0[allsedata[num].data[local_8g].banknum] + 0x10)))
				{
					continue;
				}
				wsprintfA(local_114, "%sSoundData\\SE\\%s.dat", DAT_06276b20, allsedata[num].data[local_8g].bankfilename);
				if (!_stricmp(local_114, *(char **)((char *)DAT_05b3e3a0[allsedata[num].data[local_8g].banknum] + 0x10)))
				{
					continue;
				}
			}
			if (DAT_05b3e3a0[allsedata[num].data[local_8g].banknum])
			{
				StopBankSound(allsedata[num].data[local_8g].banknum);
				MDHeaderClose(DAT_05b3e3a0[allsedata[num].data[local_8g].banknum]);
				DAT_05b3e3a0[allsedata[num].data[local_8g].banknum] = 0;
			}
			if (*allsedata[num].data[local_8g].bankfilename)
			{
				wsprintfA(local_114, "%sSoundData\\SE\\%s.dat", DAT_06276b20, allsedata[num].data[local_8g].bankfilename);
				local_118g = MDHeaderOpen(local_114, 1);
				DAT_05b3e3a0[allsedata[num].data[local_8g].banknum] = local_118g;
				if (!local_118g)
				{
					wsprintfA(local_114, "%sSoundData\\SE\\%s.dat", "SYSTEM\\", allsedata[num].data[local_8g].bankfilename);
					DAT_05b3e3a0[allsedata[num].data[local_8g].banknum] = MDHeaderOpen(local_114, 1);
				}
			}
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004ae7b0
void IsndPlay(long bank_num, long list_num, long priority, long handleno)
{
	makesndfilename((int)bank_num, (int)list_num);
	PlayPCM((int)handleno, (void *)DAT_05b3e398, DAT_05b3e464, 2, 0);
}

// FUNCTION: SADX 0x004ae7f0
void makesndfilename(int bk, int li)
{
	char local_114[264];
	int local_8g;

	wsprintfA(local_114, "B%02d_00_%02d.wav", bk, li);
	if (DAT_05b3e3a0[bk])
	{
		local_8g = FUN_004ae8c0(DAT_05b3e3a0[bk], local_114);
		DAT_05b3e398 = *(int *)((char *)DAT_05b3e3a0[bk] + 0x20 + local_8g * 0xc);
		if (DAT_05b3e398)
		{
			DAT_05b3e464 = *(int *)((char *)DAT_05b3e3a0[bk] + 0x24 + local_8g * 0xc);
		}
		else
		{
			DAT_05b3e464 = 0;
		}
	}
	else
	{
		DAT_05b3e398 = 0;
		DAT_05b3e464 = 0;
	}
}

// FUNCTION: SADX 0x004ae8c0
int FUN_004ae8c0(struct MDHANDLE *param_1, char *param_2)
{
	int local_8;

	if (!param_1)
	{
		return -1;
	}
	for (local_8 = 0; local_8 < *(int *)((char *)param_1 + 0x18); local_8++)
	{
		if (!_stricmp(*(char **)((char *)param_1 + 0x1c + local_8 * 0xc) + 3, param_2 + 3))
		{
			return local_8;
		}
	}
	return -1;
}

// FUNCTION: SADX 0x004ae920
void IsndStop(long handleno)
{
	StopPCM(handleno);
}

// FUNCTION: SADX 0x004ae940
void IsndVolume(int vol, int handleno)
{
	if (vol <= -100 && (DAT_05b3e46c[handleno][2] & 0x4000) != 0)
	{
		Set3DPositionPCM(handleno, 0.0f, 5000.0f, 0.0f);
	}
	SetVolumePCM(handleno, vol);
}

// FUNCTION: SADX 0x004ae9a0
void IsndPitch(int pitch, int handleno)
{
	SetPanPCM(handleno, pitch);
}

// FUNCTION: SADX 0x004aee80
int FUN_004aee80(int param_1, int param_2)
{
	int local_cg;
	int local_8g;

	local_8g = -1;
	for (local_cg = 0; local_cg < 0x13; local_cg++)
	{
		if (DAT_05b3e46c[local_cg][1] == param_2 && DAT_05b3e46c[local_cg][3] == param_1)
		{
			local_8g = local_cg;
		}
	}
	return local_8g;
}

// FUNCTION: SADX 0x004af360
int dsStop_num(int tone)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][3] == tone)
		{
			DAT_05b3e46c[local_8][0] = 0;
			DAT_05b3e46c[local_8][2] |= 0x10;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af3c0
int dsStop_id(int id)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][1] == id)
		{
			DAT_05b3e46c[local_8][0] = 0;
			DAT_05b3e46c[local_8][2] |= 0x10;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af420
int dsVolume_id(int id, int vol)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][1] == id)
		{
			DAT_05b3e46c[local_8][5] = vol;
			DAT_05b3e46c[local_8][2] &= 0xfffffeff;
			DAT_05b3e46c[local_8][2] |= 0x200;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af4a0
int dsPan_id(int id, int pan)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][1] == id)
		{
			DAT_05b3e46c[local_8][4] = pan;
			DAT_05b3e46c[local_8][2] &= 0xfffffbff;
			DAT_05b3e46c[local_8][2] |= 0x800;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af520
int dsPitch_id(int id, int pitch)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][1] == id)
		{
			DAT_05b3e46c[local_8][7] = pitch;
			DAT_05b3e46c[local_8][2] = DAT_05b3e46c[local_8][2] | 0x2000;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af590
int dsPause_all()
{
	int local_8;

	DAT_05b3ea00 = -1;
	DAT_05b3ea04 = -1;
	for (local_8 = 0; local_8 < 20; local_8++)
	{
		IsndVolume(-127, local_8);
	}
	FUN_005b5aa0();
	wmapause();
	return 0;
}

// FUNCTION: SADX 0x004af5e0
int dsRelease_all()
{
	int local_8;

	DAT_05b3ea00 = 0;
	DAT_05b3ea04 = 0;
	for (local_8 = 0; local_8 < 20; local_8++)
	{
		IsndVolume(DAT_05b3e988[local_8], local_8);
	}
	FUN_005b5aa0();
	wmaresume();
	return 0;
}

// FUNCTION: SADX 0x004af640
int dsPauseSndOnly()
{
	int local_8;

	DAT_05b3ea00 = -1;
	DAT_05b3ea04 = -1;
	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e46c[local_8][3] != 3 && DAT_05b3e46c[local_8][3] != 1 && DAT_05b3e46c[local_8][3] != 2)
		{
			IsndVolume(-127, local_8);
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004af6c0
int dsStop_all()
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		DAT_05b3e46c[local_8][0] = 0;
		DAT_05b3e46c[local_8][2] = DAT_05b3e46c[local_8][2] | 0x10;
		IsndStop(local_8);
		DAT_05b3e938[local_8] = 0;
	}
	return 0;
}

// FUNCTION: SADX 0x004af730
int FUN_004af730(int param_1, int param_2)
{
	int local_8;

	local_8 = FUN_004aee80(param_1, param_2);
	if (local_8 < 0)
	{
		return 0;
	}
	if (DAT_05b3e46c[local_8][2] & 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x004af780
void InitOverlapSE(unsigned char ini)
{
	if (DAT_05b3ea08++ > 3)
	{
		memset(DAT_05b3e3a0 + 0x25, 0, 0x28);
		DAT_05b3ea08 = 0;
	}
	if (ini == 1)
	{
		memset(DAT_05b3e3a0 + 0x25, 0, 0x28);
	}
}

// FUNCTION: SADX 0x004afe30
void FUN_004afe30(void)
{
	FUN_006411b0(0, 0);
	DAT_05b3e930 = 0xfffffffa;
	DAT_05b3e39c = DAT_05b3e930;
}

// FUNCTION: SADX 0x004afe60
void dsSetFxAny(int depth)
{
	DAT_05b3e39c = depth;
}

// FUNCTION: SADX 0x004b00e0
void dsReloadEVBossSound()
{
	int local_8;

	local_8 = ((short)DAT_05b9d724 << 8 | (short)DAT_05b9d744) >> 8;
	switch (local_8)
	{
		case 0x1d:
		case 0x1e:
		case 0x1f:
		case 0x20:
			SetBankDir(0x11);
			break;
		case 0x21:
		case 0x22:
			SetBankDir(0x14);
			break;
	}
}

// FUNCTION: SADX 0x004b0150
void TempEraseSound()
{
	dsStop_all();
	((void(*)(int))FUN_006411b0)(2);
}

// FUNCTION: SADX 0x004b0170
void EraseDolbyCtrl(struct taskwk *twp)
{
	int local_8;

	for (local_8 = 0; local_8 < 20; local_8++)
	{
		if (DAT_05b3e938[local_8] == (int)twp)
		{
			DAT_05b3e938[local_8] = 0;
			IsndStop(local_8);
		}
	}
}
