#include "decls.h"
extern unsigned char DAT_05bafb86;
extern unsigned char DAT_05bafbc2;
extern unsigned char DAT_05bafc02;
extern unsigned char DAT_05bafc41;
extern unsigned char DAT_05bafcc1;
extern unsigned char DAT_05bafb81;
extern unsigned char DAT_05bafbc1;
extern unsigned char DAT_05bafc01;
extern unsigned char DAT_05bafc40;
extern unsigned char DAT_05bafc80;
extern unsigned char DAT_05bafcc0;
extern int DAT_060b56a0;

// FUNCTION: SADX 0x00681150
int getSsHotelPoolDoorMode()
{
	return DAT_060b56a0;
}

// FUNCTION: SADX 0x00681160
long SeqCheckFront()
{
	long var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafb81;
		case 2:
			return DAT_05bafbc1;
		case 3:
			return DAT_05bafc01;
		case 5:
			return DAT_05bafc40;
		case 6:
			return DAT_05bafc80;
		case 7:
			return DAT_05bafcc0;
		default:
			return 0;
	}
}

// FUNCTION: SADX 0x006811d0
long SeqCheckBack()
{
	long var1;

	var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafb86;
		case 2:
			return DAT_05bafbc2;
		case 3:
			return DAT_05bafc02;
		case 5:
			return DAT_05bafc41;
		case 7:
			return DAT_05bafcc1;
		default:
			return 0;
	}
}

// STUB: SADX 0x00681240
long SeqCheckPool()
{
	return (long)0;
}

// STUB: SADX 0x006814b0
void ObjectColliSet2(struct taskwk *twp)
{
}

// STUB: SADX 0x006817d0
void ObjectWaitKeyblock(struct task *tp)
{
}
