#include "decls.h"
#include <windows.h>
#include <string.h>

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
