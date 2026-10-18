#include "decls.h"

extern int DAT_05b3ea00;
extern int DAT_05b3ea04;
extern int DAT_05b3e398;
extern int DAT_05b3e464;
extern int DAT_05b3e468[20][14];
extern int DAT_05b3e938[20];
extern int DAT_05b3e988[20];

void FUN_004ab120(int param_1, int param_2);
void FUN_004ae9c0(int param_1, int param_2);

// FUNCTION: SADX 0x004af7e0
void FUN_004af7e0()
{
	int *v = DAT_05b3e468[0];
	int y;
	int *x = DAT_05b3e988;
	int p = 0;
	int vol;
	int *ok;
	int i;
	int bt;

	if (DAT_05b3ea00 == 0)
	{
		InitOverlapSE(0);
		for (vol = 0; vol < 20; vol++)
		{
			if (v[3] & 1)
			{
				if (v[4] > 0x568)
				{
					Serif_Play(v[4] + 0x159);
					v[3] &= ~0x10;
					v[1] = 0;
				}
				else
				{
					i = 0;
					y = 0;
					ok = banktbl;
					while (*ok >= 0 || i != 0)
					{
						if (v[4] > *ok)
						{
							i = *ok;
							ok++;
							y = *ok;
							break;
						}
						ok += 2;
					}
					if (dsEVboss(v[4]))
					{
						y = (y == 6) + (y == 3) * 4;
					}
					if (i != 0)
					{
						p = IsPlayOk(v[4]);
						if (p)
						{
							makesndfilename(y, v[4] - i - 1);
							v[13] = y;
						}
					}
					else
					{
						p = IsPlayOk(v[4]);
						if (p)
						{
							makesndfilename(0, v[4]);
							v[13] = 0;
						}
					}
					if (p)
					{
						if (v[3] & 0x4000)
						{
							Load3DPCM(vol, (void *)DAT_05b3e398, DAT_05b3e464, 2);
							Set3DMinMaxPCM(vol, 10.0f, 500.0f);
						}
						else
						{
							LoadPCM(vol, (void *)DAT_05b3e398, DAT_05b3e464, 2);
						}
						if (!(v[3] & 0x4000))
						{
							if (v[3] & 0x100)
							{
								*x = dsGetVolume(vol);
							}
							else if (v[3] & 0x200)
							{
								*x = v[6];
							}
							else
							{
								*x = 0;
							}
							IsndVolume(*x, vol);
						}
						if (v[3] & 0x800)
						{
							IsndPitch(v[5], vol);
						}
						if (v[3] & 0x2000)
						{
							FUN_004ae9c0(v[8], vol);
						}
						FUN_004ab120(vol, 0);
					}
				}
				v[3] &= ~1;
			}
			else
			{
				if (v[1] > 0)
				{
					if (!(v[3] & 0x4000))
					{
						if ((v[3] & 2) || (v[3] & 0x20))
						{
							if (v[3] & 0x100)
							{
								bt = dsGetVolume(vol);
								if (*x != bt)
								{
									IsndVolume(bt, vol);
									*x = bt;
								}
							}
							v[3] &= ~2;
						}
						if (v[3] & 0x200)
						{
							bt = v[6];
							if (*x != bt)
							{
								IsndVolume(bt, vol);
								*x = bt;
							}
						}
					}
					if (v[3] & 0x800)
					{
						IsndPitch(v[5], vol);
						v[3] &= ~0x800;
					}
					if (v[3] & 0x2000)
					{
						FUN_004ae9c0(v[8], vol);
						v[3] &= ~0x2000;
					}
					v[1] = v[1] - 1;
				}
				if (v[1] == 0)
				{
					if (v[3] & 0x10)
					{
						IsndStop(vol);
					}
					v[1] = 0;
					v[2] = 0;
					v[3] = 0;
					v[4] = -1;
					DAT_05b3e938[vol] = 0;
				}
			}
			v += 14;
			x++;
		}
		if (DAT_05b3ea04 == 0)
		{
			dsDolbySound();
		}
	}
}
