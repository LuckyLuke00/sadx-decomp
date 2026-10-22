#include "decls.h"
extern void gc_ClearScreen();

// FUNCTION: SADX 0x00598b80
void InitSystemTV()
{
	late_init();
	input_init();
}

// STUB: SADX 0x00598bd0
void Draw_Reset()
{
}

// STUB: SADX 0x00598d20
void gc_ClearScreen()
{
}
