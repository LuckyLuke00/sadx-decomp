#include "decls.h"
#include <windows.h>
#include <string.h>
void FUN_006411b0(int param_1, int param_2);
extern int DAT_05b3e930;
extern int DAT_05b3e39c;
extern unsigned char DAT_05b3ea08;
extern int DAT_05b3e988[20];
extern struct taskwk *DAT_05b42a7c;
int FUN_004aee80(int param_1, int param_2);
extern int DAT_05b3e924;
extern int DAT_025adbd0;
int FUN_004ae8c0(struct MDHANDLE *, char *);
extern int DAT_05b3e398;
extern int DAT_05b3e464;
extern int DAT_05b3ea00;
extern int DAT_05b3ea04;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern unsigned char DAT_05bb00a9;
extern int DAT_05b3ea18;
void FUN_004afe30(void);

extern int DAT_05b3e46c[20][14];
extern int DAT_05b3e938[20];
extern int DAT_05a92330;
extern struct MDHANDLE *DAT_05b3e3a0[51];
extern char DAT_06276b20[260];

// FUNCTION: SADX 0x004adea0
void dsLoadStageSound()
{
	short local_14;
	int local_ci;
	int local_10;
	int local_8g;

	DAT_05b3ea00 = 0;
	DAT_05b3ea04 = 0;
	local_14 = (short)(((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744);
	local_10 = (unsigned short)local_14;
	if (local_10 > 0x2a)
	{
		SetBankDir(0x21);
	}
	else
	{
		switch (local_10)
		{
		case 0:
			SetBankDir(0x24);
			break;
		case 1:
			SetBankDir(0);
			break;
		case 2:
			SetBankDir(0x38);
			break;
		case 3:
			SetBankDir(0x37);
			break;
		case 4:
			SetBankDir(0x26);
			break;
		case 5:
			SetBankDir(0x21);
			break;
		case 6:
			SetBankDir(0x34);
			break;
		case 7:
			SetBankDir(0x29);
			break;
		case 8:
			SetBankDir(0x28);
			break;
		case 9:
			SetBankDir(0x18);
			local_ci = GetPlayerNumber();
			if (local_ci <= 7)
			{
				switch (local_ci)
				{
				case 0:
					SetBankDir(1);
					if (DAT_05bb00a9)
					{
						SetBankDir(0x3e);
					}
					else
					{
						if (!DAT_05b3ea18)
						{
							SetBankDir(0x3b);
						}
						else
						{
							SetBankDir(0x3c);
						}
					}
					break;
				case 2:
					if (DAT_05bb00a9)
					{
						SetBankDir(0x3e);
					}
					else
					{
						SetBankDir(1);
					}
					if (!DAT_05b3ea18)
					{
						SetBankDir(0x3b);
					}
					else
					{
						SetBankDir(0x3c);
					}
					break;
				case 3:
					SetBankDir(0x31);
					if (!DAT_05b3ea18)
					{
						SetBankDir(0x45);
						SetBankDir(0x39);
					}
					else
					{
						SetBankDir(0x46);
						SetBankDir(0x3a);
					}
					break;
				default:
					break;
				}
			}
			else
			{
				SetBankDir(0x1a);
				if (DAT_05bb00a9)
				{
					SetBankDir(0x3e);
				}
				else
				{
					if (!DAT_05b3ea18)
					{
						SetBankDir(0x3b);
					}
					else
					{
						SetBankDir(0x3c);
					}
				}
			}
			break;
		case 0xa:
			SetBankDir(0x25);
			break;
		case 0xc:
			SetBankDir(0x27);
			break;
		case 0xf:
			SetBankDir(0x1b);
			break;
		case 0x10:
			SetBankDir(0x1c);
			break;
		case 0x11:
			SetBankDir(0x1d);
			break;
		case 0x12:
			SetBankDir(0x1e);
			break;
		case 0x13:
			SetBankDir(0x20);
			break;
		case 0x14:
			SetBankDir(0x2a);
			break;
		case 0x15:
			SetBankDir(0x2b);
			break;
		case 0x16:
			SetBankDir(0x2c);
			break;
		case 0x18:
			SetBankDir(0x22);
			break;
		case 0x19:
			SetBankDir(0x23);
			break;
		case 0x1a:
		case 0x1b:
		case 0x1c:
			SetBankDir(0x36);
			break;
		case 0x1d:
		case 0x1e:
		case 0x1f:
		case 0x20:
			SetBankDir(0x24);
			break;
		case 0x21:
		case 0x22:
			SetBankDir(0x2d);
			break;
		case 0x23:
			SetBankDir(0x17);
			break;
		case 0x24:
		case 0x25:
			SetBankDir(0x33);
			break;
		case 0x26:
			SetBankDir(0x32);
			break;
		case 0x27:
		case 0x28:
		case 0x29:
		case 0x2a:
			SetBankDir(0x3d);
			dsLoadCharacterVoice();
			break;
		}
	}
	local_8g = GetPlayerNumber();
	if (local_8g <= 7)
	{
		switch (local_8g)
		{
		case 0:
			if (DAT_05bb00a9)
			{
				SetBankDir(0x3e);
			}
			else
			{
				SetBankDir(1);
			}
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x47);
			}
			else
			{
				SetBankDir(0x48);
			}
			break;
		case 2:
			SetBankDir(1);
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x47);
			}
			else
			{
				SetBankDir(0x48);
			}
			break;
		case 3:
			SetBankDir(0x31);
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x45);
			}
			else
			{
				SetBankDir(0x46);
			}
			break;
		case 5:
			SetBankDir(0x2e);
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x3f);
			}
			else
			{
				SetBankDir(0x40);
			}
			break;
		case 6:
			SetBankDir(0x30);
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x43);
			}
			else
			{
				SetBankDir(0x44);
			}
			break;
		case 7:
			SetBankDir(0x2f);
			if (!DAT_05b3ea18)
			{
				SetBankDir(0x41);
			}
			else
			{
				SetBankDir(0x42);
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (DAT_05bb00a9)
		{
			SetBankDir(0x3e);
		}
		else
		{
			SetBankDir(1);
		}
		if (!DAT_05b3ea18)
		{
			SetBankDir(0x47);
		}
		else
		{
			SetBankDir(0x48);
		}
	}
	FUN_004afe30();
	dsStop_all();
}

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

// FUNCTION: SADX 0x004aea00
int dsPlay_oneshot(int tone, int id, int pri, int volofs)
{
	int local_8;

	local_8 = dsCheckHandle(pri, tone);
	if (local_8 < 0)
	{
		return -1;
	}
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38) = 0x78;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 4) = -1;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 8) = id;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 12) = 0x11;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 16) = tone;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 20) = 0;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 24) = volofs;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 28) = 0;
	*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 32) = 0;
	*(float *)((char *)DAT_05b3e46c + local_8 * 0x38 + 36) = 0.0f;
	*(float *)((char *)DAT_05b3e46c + local_8 * 0x38 + 40) = 0.0f;
	*(float *)((char *)DAT_05b3e46c + local_8 * 0x38 + 44) = 0.0f;
	if (tone == 7)
	{
		*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 12) = 0x801;
		*(int *)((char *)DAT_05b3e46c + local_8 * 0x38 + 20) = DAT_025adbd0;
		DAT_025adbd0 = -DAT_025adbd0;
	}
	return 1;
}

// FUNCTION: SADX 0x004aeb20
int dsCheckHandle(int pri, int tone)
{
	int local_10;
	int local_ci;
	int local_8g;

	local_10 = -1;
	local_ci = 0x13;
	local_8g = DAT_05b3e924;
	while (local_10 < 0 && local_ci > 0)
	{
		if (DAT_05b3e46c[local_8g][0] == 0)
		{
			local_10 = local_8g;
		}
		if (DAT_05b3e46c[local_8g][1] <= pri)
		{
			local_10 = local_8g;
		}
		local_8g++;
		if (local_8g >= 0x13)
		{
			local_8g = 0;
		}
		local_ci--;
	}
	if (local_10 != -1)
	{
		DAT_05b3e924 = local_10 + 1;
		if (DAT_05b3e924 >= 0x14)
		{
			DAT_05b3e924 = 0;
		}
	}
	return local_10;
}

// FUNCTION: SADX 0x004aebd0
int dsPlay_oneshot_v(int tone, int id, int pri, int volofs, float x, float y, float z)
{
	int local_8g;
	int local_20o;
	int local_cj;
	float local_10m;
	float local_1ci;
	float local_18;
	float local_24;
	float local_14;

	local_20o = 0;
	local_cj = 0xc8;
	local_10m = x - *(float *)((char *)DAT_05b42a7c + 0x20);
	local_1ci = y - *(float *)((char *)DAT_05b42a7c + 0x24);
	local_18 = z - *(float *)((char *)DAT_05b42a7c + 0x28);
	local_24 = (float)local_cj;
	local_14 = local_10m * local_10m + local_1ci * local_1ci + local_18 * local_18 + local_24 * local_24;
	if (local_cj >= 0 && DAT_05b42a7c)
	{
		if (local_14 > 1600000000.0f)
		{
			return -1;
		}
		local_20o = local_20o | 0x1000;
	}
	local_8g = FUN_004aee80(tone, id);
	if (local_8g >= 0)
	{
		local_20o = DAT_05b3e46c[local_8g][2] & 1;
	}
	else
	{
		local_8g = dsCheckHandle(pri, tone);
		if (local_8g < 0)
		{
			return -1;
		}
		local_20o = local_20o | 1;
	}
	DAT_05b3e46c[local_8g][0] = 0x78;
	DAT_05b3e46c[local_8g][1] = -1;
	DAT_05b3e46c[local_8g][2] = id;
	DAT_05b3e46c[local_8g][3] = local_20o | 0x10;
	DAT_05b3e46c[local_8g][3] = DAT_05b3e46c[local_8g][3] | 0x100;
	DAT_05b3e46c[local_8g][4] = tone;
	DAT_05b3e46c[local_8g][5] = 0;
	DAT_05b3e46c[local_8g][6] = volofs;
	DAT_05b3e46c[local_8g][7] = volofs;
	DAT_05b3e46c[local_8g][8] = 0;
	*(float *)&DAT_05b3e46c[local_8g][9] = x;
	*(float *)&DAT_05b3e46c[local_8g][10] = y;
	*(float *)&DAT_05b3e46c[local_8g][11] = z;
	return local_8g;
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
