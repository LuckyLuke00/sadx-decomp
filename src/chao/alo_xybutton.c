#include "decls.h"
extern int DAT_05b288a4;

// FUNCTION: SADX 0x00443ab0
void ALO_XYButtonHide(int id)
{
	DAT_05b288a4 |= 1 << id;
}

// FUNCTION: SADX 0x00443ad0
void ALO_XYButtonShow(int id)
{
	DAT_05b288a4 &= ~(1 << id);
}
