#include "decls.h"
extern unsigned char DAT_05bafb96;
extern unsigned char DAT_05bafbd5;
extern unsigned char DAT_05bafc11;
extern unsigned char DAT_05bafc92;
extern unsigned char DAT_05bafccc;

// FUNCTION: SADX 0x006aded0
int GetBreakRockState()
{
	int var1 = GetPlayerCharacterName(0);

	switch (var1)
	{
	case 0:
		return DAT_05bafb96;
	case 2:
		return DAT_05bafbd5;
	case 3:
		return DAT_05bafc11;
	case 6:
		return DAT_05bafc92;
	case 7:
		return DAT_05bafccc;
	}
	return 0;
}
