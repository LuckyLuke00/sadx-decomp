#include "decls.h"

// FUNCTION: SADX 0x0083d930
void ObjectSkydeck_tcolli(struct task *tp)
{
	tp->exec = ObjectSkydeck_tcolli_Exec;
	tp->disp = ObjectSkydeck_tcolli_Display;
	tp->dest = ObjectSkydeck_tcolli_Exit;
}
