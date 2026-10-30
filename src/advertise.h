#pragma once

#include <math.h>
#include <stdio.h>
#include <string>
#pragma push_macro("_HAS_TR1")
#pragma push_macro("_HAS_TR1_IMPORTS")
#pragma push_macro("_HAS_CPP0X")
#undef _HAS_TR1
#undef _HAS_TR1_IMPORTS
#undef _HAS_CPP0X
#define _HAS_TR1 0
#define _HAS_TR1_IMPORTS 0
#define _HAS_CPP0X 0
#include <vector>
#include <list>
#include <map>
#pragma pop_macro("_HAS_TR1")
#pragma pop_macro("_HAS_TR1_IMPORTS")
#pragma pop_macro("_HAS_CPP0X")

extern const float DAT_0098fa14;
extern const float DAT_0098fc50;

// VTABLE: SADX 0x00956bb4
class SOCController
{
public:
	enum ControllerButton { AXIS_LX = 11, AXIS_LY = 12 };
	virtual ~SOCController() {}
	virtual void FUN_004321e0();
	virtual bool FUN_00431c60(ControllerButton) const;
	virtual bool FUN_00431d10(ControllerButton) const;
	virtual float FUN_00431e50(ControllerButton) const;
	virtual bool FUN_00432010(int, int);
	virtual bool FUN_00431e90();
	virtual bool FUN_00432100(int, int, double);
	virtual bool FUN_00431ee0();
	virtual void* FUN_00431f00(void*);
	virtual void* FUN_00431fa0(void*);
private:
	char local_4[0x24];
};

// VTABLE: SADX 0x00956be4
class SOCControllerAll : public SOCController
{
public:
	virtual void FUN_004321e0() {}
	virtual bool FUN_00431c60(ControllerButton) const;
	virtual bool FUN_00431d10(ControllerButton) const;
	virtual float FUN_00431e50(ControllerButton) const { return 0.0f; }
	virtual bool FUN_00432010(int, int) { return false; }
	virtual bool FUN_00431e90() { return false; }
	virtual bool FUN_00432100(int, int, double) { return false; }
	virtual bool FUN_00431ee0() { return false; }
};

namespace Magic
{
namespace Base
{
template<class T> class Singleton;
}
}

class SOCInput
{
public:
	SOCController* FUN_00424b40();
private:
	friend class Magic::Base::Singleton<SOCInput>;
	SOCInput();
	int local_0;
	SOCController* local_4[8];
	char local_24[0x28];
};

struct LBOnData
{
	wchar_t strRank[16];
	wchar_t strGameRtag[16];
	wchar_t strData[16];
	wchar_t strScore[16];
};

namespace Magic
{
namespace Base
{
class File
{
public:
	void FUN_00928790();
	void FUN_00928740();
	long FUN_009285c0();
	bool FUN_00928810(const std::string& param_1, int param_2);
	void FUN_00435420();
	bool FUN_00928630(int param_1, int param_2);
	bool FUN_009286c0(void* param_1, size_t param_2, unsigned long* param_3);
private:
	FILE** local_0;
	char local_4[0x1c];
};
class IniFile
{
public:
	IniFile();
	~IniFile();
	int FUN_0092b1b0(const std::string&, const std::string&, const std::string&);
	int FUN_0092b2b0(const std::string&);
private:
	File* Fini;
	std::map<std::string, std::string> FileMap;
	std::string Filename;
	bool blOpenSuccess;
	bool blChanged;
};

template<class T> class Singleton
{
public:
	T* GetSubject()
	{
		if (m_pSubject == 0)
			m_pSubject = new T;
		return m_pSubject;
	}
private:
	T* m_pSubject;
};

class Timer
{
public:
	Timer();
	double FUN_00929760();
private:
	void* local_0;
};
}

namespace MATH
{
class Math
{
public:
	template<class T> static T AngleUniform(T param_1)
	{
		param_1 = (T)fmod(param_1, DAT_0098fc50);
		return param_1 >= 0.0 ? param_1 : param_1 + DAT_0098fc50;
	}
};
}

namespace RenderCore
{
class Texture
{
public:
	Texture();
	virtual ~Texture();
	bool Load(void*, int, int, int, int, int);
private:
	char local_4[0x70];
};
}
}

class SOCFile : public Magic::Base::File
{
public:
	bool FUN_00433c20(const std::string& param_1, int param_2);
};

class SOCIniFile : public Magic::Base::IniFile
{
public:
	SOCIniFile() {}
	~SOCIniFile() {}
	int FUN_0067edf0(const std::string&);
};

class SOCFileStream
{
public:
	SOCFileStream();
	~SOCFileStream();
	bool ReadFile(const std::string&);
	void* FUN_00424960();
	int FUN_0040b8a0();
private:
	void* local_0;
	int local_4;
};

class SOCSystem
{
public:
	SOCSystem();
	void* FUN_004035e0(const std::string&);
	void* GetFuncAddress(void*, char*);
};

class SOCTimer : public Magic::Base::Timer
{
public:
	int FUN_004caf80();
};

class SOCRender
{
public:
	// FUNCTION: SADX 0x00419cf0
	void FUN_00419cf0(int param_1)
	{
		local_2798 = param_1;
	}
private:
	char local_0[0x2798];
	int local_2798;
};

extern void* DAT_0629c344;

// FUNCTION: SADX 0x00405f00
inline class SOCInput* FUN_00405f00()
{
	return ((Magic::Base::Singleton<SOCInput>*)&DAT_0629c344)->GetSubject();
}

extern void* DAT_05ab4304;

// FUNCTION: SADX 0x0041a800
inline class SOCTimer* FUN_0041a800()
{
	return ((Magic::Base::Singleton<SOCTimer>*)&DAT_05ab4304)->GetSubject();
}

static_assert(sizeof(Magic::Base::File) == 0x20, "sizeof File");
