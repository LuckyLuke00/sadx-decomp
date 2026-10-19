#include "decls.h"
extern int DAT_060eea5c;
extern int DAT_06274afc;
extern int DAT_06298cac;
extern int DAT_05cc7fe8;
extern int DAT_05cc7ff8;
extern int DAT_05cc62c0;
extern int DAT_05cc62d0;
extern int DAT_05cc3fe0;
extern int DAT_05cc3ff0;
extern int DAT_05cc4000;
extern int DAT_05cc4020;
extern int DAT_05cc4010;

// FUNCTION: SADX 0x0059bcc0
void _advertise_prolog()
{
	DAT_05cc7fe8 = *(int *)((char *)DAT_060eea5c + 0x190);
	DAT_05cc7ff8 = *(int *)((char *)DAT_060eea5c + 0x194);
	DAT_05cc62c0 = *(int *)((char *)DAT_06274afc + 0xa0);
	DAT_05cc62d0 = *(int *)((char *)DAT_06274afc + 0xa4);
	DAT_05cc3fe0 = *(int *)((char *)DAT_06298cac + 0x10);
	DAT_05cc3ff0 = *(int *)((char *)DAT_06298cac + 0x10);
	DAT_05cc4000 = *(int *)((char *)DAT_06298cac + 0x74);
	DAT_05cc4020 = *(int *)((char *)DAT_06298cac + 0x78);
	DAT_05cc4010 = DAT_05cc4020;
}
