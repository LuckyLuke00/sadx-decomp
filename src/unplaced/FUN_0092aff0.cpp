#include "decls.h"
#include "../advertise.h"

// STUB: SADX 0x0092b030
void __fastcall FUN_0092b030(int *param_1, int *param_2, int *param_3)
{
}

// STUB: SADX 0x0092b080
void __stdcall FUN_0092b080(void *param_1, int param_2)
{
}

// STUB: SADX 0x0092b110
int __fastcall FUN_0092b110(int *param_1, int *param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x0092b130
Magic::Base::IniFile::IniFile()
{
	blChanged = false;
}

// STL string and map helper code generation remains unmatched.
// FUNCTION: SADX 0x0092b1b0
int Magic::Base::IniFile::FUN_0092b1b0(const std::string& param_1, const std::string& param_2, const std::string& param_3)
{
	if (!blOpenSuccess)
	{
		return 2;
	}
	if (param_1.empty() || param_2.empty())
	{
		return 4;
	}
	FileMap[param_1 + "&" + param_2] = param_3;
	blChanged = true;
	return 5;
}

// STUB: SADX 0x0092b2b0
int Magic::Base::IniFile::FUN_0092b2b0(const std::string& param_1)
{
	return 0;
}

Magic::Base::IniFile::~IniFile()
{
}

// STUB: SADX 0x0092c090
int __fastcall FUN_0092c090(int param_1, int param_2)
{
	return (int)0;
}
