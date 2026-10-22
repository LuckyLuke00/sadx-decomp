#include "decls.h"
extern char DAT_01c6ee20[];
extern char DAT_01c6ee60[];
extern char DAT_05ad9ba8[];
extern char DAT_05ad9cb0[];

// FUNCTION: SADX 0x00430dc0
void stQueryInit(char **param_1)
{
	char *var1;
	char *var2;

	var1 = *param_1;
	var2 = DAT_01c6ee20;
	while (1)
	{
		char var3;

		var3 = *var1;
		*var2 = var3;
		var1++;
		var2++;
		if (var3 == 0)
		{
			break;
		}
	}
	var1 = param_1[1];
	var2 = DAT_01c6ee60;
	while (1)
	{
		char var4;

		var4 = *var1;
		*var2 = var4;
		var1++;
		var2++;
		if (var4 == 0)
		{
			break;
		}
	}
	var1 = param_1[2];
	var2 = DAT_05ad9ba8;
	while (1)
	{
		char var5;

		var5 = *var1;
		*var2 = var5;
		var1++;
		var2++;
		if (var5 == 0)
		{
			break;
		}
	}
	var1 = param_1[3];
	var2 = DAT_05ad9cb0;
	while (1)
	{
		char var6;

		var6 = *var1;
		*var2 = var6;
		var1++;
		var2++;
		if (var6 == 0)
		{
			break;
		}
	}
}

// FUNCTION: SADX 0x00430e20
char * stGetQueryMediaDir(void)
{
	return (char *)&DAT_05ad9ba8;
}
