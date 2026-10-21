#include "decls.h"
extern int DAT_060d0ad0;
extern int DAT_060d0acc;

// FUNCTION: SADX 0x00838810
void InitIntSkyDeck()
{
	DAT_060d0ad0 = 0;
	DAT_060d0acc = 0;
}

// FUNCTION: SADX 0x0083d930
void ObjectSkydeck_tcolli(struct task *tp)
{
	tp->exec = ObjectSkydeck_tcolli_Exec;
	tp->disp = ObjectSkydeck_tcolli_Display;
	tp->dest = ObjectSkydeck_tcolli_Exit;
}
