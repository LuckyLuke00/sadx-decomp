#include "decls.h"
struct DialogPrmType;
enum DiaTypeEnum;
void OpenDialog(struct DialogPrmType *, int);
extern struct DialogPrmType DAT_009919e0;

// FUNCTION: SADX 0x005a3fc0
void AdvaOpenDialog(enum DiaTypeEnum dialog_type)
{
	OpenDialog((struct DialogPrmType *)((int)&DAT_009919e0 + dialog_type * 0x3c), 0);
	return;
}

// FUNCTION: SADX 0x005a3fe0
void AdvaOpenDialogCsrLet(enum DiaTypeEnum dialog_type, signed char csr, signed char *csrp)
{
	OpenDialogCsrLet((struct DialogPrmType *)((char *)&DAT_009919e0 + dialog_type * 0x3c), csr, csrp);
}

// FUNCTION: SADX 0x005a4010
void AdvaOpenDialogQuick(enum DiaTypeEnum dialog_type, signed char csr, signed char *csrp)
{
	OpenDialogQuick((struct DialogPrmType *)((char *)&DAT_009919e0 + dialog_type * 0x3c), csr, csrp);
	return;
}
