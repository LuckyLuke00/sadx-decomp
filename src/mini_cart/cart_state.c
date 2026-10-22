#include "decls.h"

// FUNCTION: SADX 0x007e5620
long CartStateIntrptToCentiSec(long intrpt)
{
	long local_4 = (intrpt * 1000) / 60;
	long local_8 = local_4 / 10;
	if (local_4 % 10 >= 5)
	{
		local_8++;
	}
	return local_8;
}
