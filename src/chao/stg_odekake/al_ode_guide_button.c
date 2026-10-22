#include "decls.h"

// FUNCTION: SADX 0x0047e910
void CreateCancelButton(float xpos, float ypos, unsigned short WaitTime)
{
	CreateGuideButton(3, xpos, ypos, WaitTime);
	CreateGuideButton(1, xpos + 55.0, ypos, WaitTime);
}
