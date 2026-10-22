#include "decls.h"
extern unsigned char DAT_05bafb91;
extern unsigned char DAT_05bafbd0;
extern unsigned char DAT_05bafc0c;
extern unsigned char DAT_05bafc4a;
extern unsigned char DAT_05bafc88;
extern unsigned char DAT_05bafcc9;

// FUNCTION: SADX 0x006a2130
int chk_transform()
{
	int var1;

	var1 = GetPlayerNumber();
	switch (var1)
	{
		case 0:
			return DAT_05bafb91;
		case 2:
			return DAT_05bafbd0;
		case 3:
			return DAT_05bafc0c;
		case 5:
			return DAT_05bafc4a;
		case 6:
			return DAT_05bafc88;
		case 7:
			return DAT_05bafcc9;
	}
	return 0;
}
