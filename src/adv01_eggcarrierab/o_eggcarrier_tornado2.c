#include "decls.h"

// FUNCTION: SADX 0x0069b210
int chk_lost()
{
	switch (GetPlayerNumber())
	{
	case 0:
		return SeqCheckFlag(0x92);
	case 2:
		return SeqCheckFlag(0xd1);
	case 3:
		return SeqCheckFlag(0x10e);
	case 5:
		return SeqCheckFlag(0x14c);
	case 6:
		return SeqCheckFlag(0x18b);
	case 7:
		return SeqCheckFlag(0x1ca);
	}
	return 0;
}
