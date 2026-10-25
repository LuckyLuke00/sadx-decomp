#include "decls.h"
extern float DAT_060dd39c;
extern int DAT_060dd398;

// FUNCTION: SADX 0x008a2970
void InitAquariumSequence()
{
	DAT_060dd39c = -80.0;
	DAT_060dd398 = 0;
	CreateElementalTask(6, 3, ObjShelterBtsuimen);
	CreateElementalTask(2, 3, ObjShelterAquarium);
	CreateElementalTask(2, 3, ObjShelterSenmanager);
	CreateElementalTask(6, 3, ObjShelterColsuimen);
	CreateUkidoor();
}
