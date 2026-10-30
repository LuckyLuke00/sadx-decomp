#include "decls.h"
#include "../advertise.h"
extern std::vector<struct FUN_00420960_0, std::allocator<struct FUN_00420960_0> > DAT_05ab42dc;

// FUNCTION: SADX 0x0041c2d0
void FUN_0041c2d0(void *param_1)
{
	std::vector<FUN_00420960_0>::iterator var1;
	var1 = DAT_05ab42dc.begin();
	if (DAT_05ab42dc.begin() != DAT_05ab42dc.end())
	{
		do
		{
			if (var1->local_14 == param_1)
			{
				var1->local_14 = 0;
			}
			++var1;
		} while (var1 != DAT_05ab42dc.end());
	}
}
