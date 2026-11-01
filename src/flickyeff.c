#include "decls.h"

// FUNCTION: SADX 0x0061efd0
struct NJS_ARGB getARGB(int colormode, float alpha, float rate_color)
{
	struct NJS_ARGB local_18;

	local_18.a = alpha;
	switch (colormode)
	{
		case 0:
			local_18.r = 1.0f;
			local_18.b = rate_color;
			local_18.g = rate_color;
			break;
		case 1:
			local_18.r = rate_color;
			local_18.b = rate_color;
			local_18.g = 1.0f;
			break;
		case 2:
			local_18.r = rate_color;
			local_18.b = 1.0f;
			local_18.g = rate_color;
			break;
		case 3:
			local_18.r = 1.0f;
			local_18.b = 1.0f;
			local_18.g = 1.0f;
			break;
		case 4:
			local_18.r = 1.0f;
			local_18.b = rate_color;
			local_18.g = 1.0f;
			break;
		case 5:
			local_18.r = 1.0f;
			local_18.b = 1.0f;
			local_18.g = rate_color;
			break;
		case 6:
			local_18.r = rate_color;
			local_18.b = 1.0f;
			local_18.g = 1.0f;
			break;
		default:
			local_18.r = 0.5f;
			local_18.b = 0.7f;
			local_18.g = 1.0f;
			break;
	}
	return local_18;
}
