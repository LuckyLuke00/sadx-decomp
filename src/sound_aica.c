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
	int i;

	for (i = 0; i < 20; i++)
	{
		if (DAT_05b3e46c[i][3] != -1 && DAT_05b3e46c[i][12] == bank)
		{
			StopPCM(i);
			DAT_05b3e46c[i][0] = 0;
			DAT_05b3e46c[i][1] = 0;
			DAT_05b3e46c[i][2] = 0;
			DAT_05b3e46c[i][3] = -1;
			DAT_05b3e938[i] = 0;
		}
	}
}

// FUNCTION: SADX 0x004ae500
int SetBankDir(int bank)
{
	int i;
	struct MDHANDLE *handle;
	char path[264];

	if (bank >= 0x7b)
	{
		return 0;
	}
	if (IsSoundSystem() && DAT_05a92330)
	{
		for (i = 0; i < allsedata[bank].datasize; i++)
		{
			if (DAT_05b3e3a0[((struct bankdata *)allsedata[bank].data)[i].banknum])
			{
				wsprintfA(path, "%sSoundData\\SE\\%s.dat", "SYSTEM\\", allsedata[bank].data[i].bankfilename);
				if (!_stricmp(path, *(char **)((char *)DAT_05b3e3a0[allsedata[bank].data[i].banknum] + 0x10)))
				{
					continue;
				}
				wsprintfA(path, "%sSoundData\\SE\\%s.dat", DAT_06276b20, allsedata[bank].data[i].bankfilename);
				if (!_stricmp(path, *(char **)((char *)DAT_05b3e3a0[allsedata[bank].data[i].banknum] + 0x10)))
				{
					continue;
				}
			}
			if (DAT_05b3e3a0[allsedata[bank].data[i].banknum])
			{
				StopBankSound(allsedata[bank].data[i].banknum);
				MDHeaderClose(DAT_05b3e3a0[allsedata[bank].data[i].banknum]);
				DAT_05b3e3a0[allsedata[bank].data[i].banknum] = 0;
			}
			if (*allsedata[bank].data[i].bankfilename)
			{
				wsprintfA(path, "%sSoundData\\SE\\%s.dat", DAT_06276b20, allsedata[bank].data[i].bankfilename);
				handle = MDHeaderOpen(path, 1);
				DAT_05b3e3a0[allsedata[bank].data[i].banknum] = handle;
				if (!handle)
				{
					wsprintfA(path, "%sSoundData\\SE\\%s.dat", "SYSTEM\\", allsedata[bank].data[i].bankfilename);
					DAT_05b3e3a0[allsedata[bank].data[i].banknum] = MDHeaderOpen(path, 1);
				}
			}
		}
	}
	return 0;
}
