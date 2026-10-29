#include "decls.h"

// FUNCTION: SADX 0x0067ec20
void njSetPvmTextureList(int *texlist, int *texname, int filename, int size)
{
	if (size > 0)
	{
		int *piVar1 = texname;
		do
		{
			*piVar1 = filename;
			filename = filename + 0x1c;
			size = size + -1;
			piVar1 = piVar1 + 3;
		}
		while (size != 0);
		*texlist = (int)texname;
		return;
	}
	*texlist = (int)texname;
	return;
}
