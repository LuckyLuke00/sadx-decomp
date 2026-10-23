#include "decls.h"

// FUNCTION: SADX 0x006a3480
int chk_service_monorail()
{
	switch (GetPlayerNumber())
	{
	case 0:
		return SeqCheckFlag(0x8f);
	case 2:
		return SeqCheckFlag(0xce);
	case 3:
		return SeqCheckFlag(0x10a);
	case 5:
		return SeqCheckFlag(0x148);
	case 6:
		return SeqCheckFlag(0x186);
	case 7:
		return SeqCheckFlag(0x1c7);
	}
	return 0;
}
