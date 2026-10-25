#include "decls.h"
extern struct obj object_loadsfin_gards_gards[];
extern unsigned char DAT_05bafb80;
extern unsigned char DAT_05bafbc0;

// FUNCTION: SADX 0x00688fd0
long SeqCheck()
{
	switch (GetPlayerCharacterName(0))
	{
	case 0:
		if (EV_CheckCansel() != 0)
			return 1;
		return DAT_05bafb80;
	case 2:
		return DAT_05bafbc0;
	case 3:
	case 5:
	case 6:
	case 7:
		return 1;
	}
	return 0;
}
