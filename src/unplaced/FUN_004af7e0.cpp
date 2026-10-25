#include "decls.h"

extern int DAT_05b3ea00;
extern int DAT_05b3ea04;
extern int DAT_05b3e398;
extern int DAT_05b3e464;
extern struct _SEcallbuf DAT_05b3e468[20];
extern int DAT_05b3e938[20];
extern int DAT_05b3e988[20];

void FUN_004ab120(int param_1, int param_2);
void FUN_004ae9c0(int param_1, int param_2);

// FUNCTION: SADX 0x004af7e0
void FUN_004af7e0()
{
	struct _SEcallbuf *local_10l = DAT_05b3e468;
	int local_18x;
	int *local_14u = DAT_05b3e988;
	int local_ci = 0;
	int local_8g;
	int *local_20k;
	int local_1cg;
	int local_24;

	if (DAT_05b3ea00 == 0)
	{
		InitOverlapSE(0);
		for (local_8g = 0; local_8g < 20; local_8g++)
		{
			if (local_10l->mode & 1)
			{
				if (local_10l->tone > 0x568)
				{
					Serif_Play(local_10l->tone + 0x159);
					local_10l->mode &= ~0x10;
					local_10l->timer = 0;
				}
				else
				{
					local_1cg = 0;
					local_18x = 0;
					local_20k = banktbl;
					while (*local_20k >= 0 || local_1cg != 0)
					{
						if (local_10l->tone > *local_20k)
						{
							local_1cg = *local_20k;
							local_20k++;
							local_18x = *local_20k;
							break;
						}
						local_20k += 2;
					}
					if (dsEVboss(local_10l->tone))
					{
						local_18x = (local_18x == 6) + (local_18x == 3) * 4;
					}
					if (local_1cg != 0)
					{
						local_ci = IsPlayOk(local_10l->tone);
						if (local_ci)
						{
							makesndfilename(local_18x, local_10l->tone - local_1cg - 1);
							local_10l->banknum = local_18x;
						}
					}
					else
					{
						local_ci = IsPlayOk(local_10l->tone);
						if (local_ci)
						{
							makesndfilename(0, local_10l->tone);
							local_10l->banknum = 0;
						}
					}
					if (local_ci)
					{
						if (local_10l->mode & 0x4000)
						{
							Load3DPCM(local_8g, (void *)DAT_05b3e398, DAT_05b3e464, 2);
							Set3DMinMaxPCM(local_8g, 10.0f, 500.0f);
						}
						else
						{
							LoadPCM(local_8g, (void *)DAT_05b3e398, DAT_05b3e464, 2);
						}
						if (!(local_10l->mode & 0x4000))
						{
							if (local_10l->mode & 0x100)
							{
								*local_14u = dsGetVolume(local_8g);
							}
							else if (local_10l->mode & 0x200)
							{
								*local_14u = local_10l->vol;
							}
							else
							{
								*local_14u = 0;
							}
							IsndVolume(*local_14u, local_8g);
						}
						if (local_10l->mode & 0x800)
						{
							IsndPitch(local_10l->angle, local_8g);
						}
						if (local_10l->mode & 0x2000)
						{
							FUN_004ae9c0(local_10l->pitch, local_8g);
						}
						FUN_004ab120(local_8g, 0);
					}
				}
				local_10l->mode &= ~1;
			}
			else
			{
				if (local_10l->timer > 0)
				{
					if (!(local_10l->mode & 0x4000))
					{
						if ((local_10l->mode & 2) || (local_10l->mode & 0x20))
						{
							if (local_10l->mode & 0x100)
							{
								local_24 = dsGetVolume(local_8g);
								if (*local_14u != local_24)
								{
									IsndVolume(local_24, local_8g);
									*local_14u = local_24;
								}
							}
							local_10l->mode &= ~2;
						}
						if (local_10l->mode & 0x200)
						{
							local_24 = local_10l->vol;
							if (*local_14u != local_24)
							{
								IsndVolume(local_24, local_8g);
								*local_14u = local_24;
							}
						}
					}
					if (local_10l->mode & 0x800)
					{
						IsndPitch(local_10l->angle, local_8g);
						local_10l->mode &= ~0x800;
					}
					if (local_10l->mode & 0x2000)
					{
						FUN_004ae9c0(local_10l->pitch, local_8g);
						local_10l->mode &= ~0x2000;
					}
					local_10l->timer = local_10l->timer - 1;
				}
				if (local_10l->timer == 0)
				{
					if (local_10l->mode & 0x10)
					{
						IsndStop(local_8g);
					}
					local_10l->timer = 0;
					local_10l->id = 0;
					local_10l->mode = 0;
					local_10l->tone = -1;
					DAT_05b3e938[local_8g] = 0;
				}
			}
			local_10l++;
			local_14u++;
		}
		if (DAT_05b3ea04 == 0)
		{
			dsDolbySound();
		}
	}
}
