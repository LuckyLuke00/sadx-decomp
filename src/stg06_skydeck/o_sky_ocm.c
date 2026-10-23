#include "decls.h"
void ObjectSkydeck_OCM(struct task *tp);
extern struct task *DAT_060d12a8;

// FUNCTION: SADX 0x0084c050
void ObjectSkydeck_OCM(struct task *tp)
{
	if (DAT_060d12a8 == tp)
	{
		DAT_060d12a8 = NULL;
	}
}

// STUB: SADX 0x0084c070
void OCMref(struct task *tp)
{
}
