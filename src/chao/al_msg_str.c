#include "decls.h"

extern int DAT_05b3ebbc;

// STUB: SADX 0x0044c420
const unsigned long *AlMsgStrLoadLang(const char *name, int lang)
{
	return (const unsigned long *)0;
}

// FUNCTION: SADX 0x0044c4c0
int AlMsgStrEmbed(char *dst, const char *format, const char * *suite)
{
	char *var1 = dst;
	char var2;
	while ((var2 = *format) != '\0')
	{
		format++;
		if (var2 == 5)
		{
			int var3 = ((format[0] - 0x33) << 4) + format[1];
			format += 2;
			var1 += AlMsgStrEmbed(var1, suite[var3], suite);
		}
		else
		{
			*var1 = var2;
			var1++;
		}
	}
	*var1 = '\0';
	return var1 - dst;
}

// FUNCTION: SADX 0x0044c520
const unsigned long *AlMsgStrLoad(const char *name)
{
	return AlMsgStrLoadLang(name, DAT_05b3ebbc);
}
