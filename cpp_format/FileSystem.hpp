#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <sstream> 
#include <iosfwd>
#include <vector>
using namespace std;

/*
����linux��windows��ö��Ŀ¼�Ĺ��ܣ� 
����boost������ƽ̨��Ŀ¼ö�ٹ��ܣ� ����滻Ϊboost��
*/

#ifdef WIN32
#define DLL_EXPORT_API __declspec(dllexport)
#else
#define DLL_EXPORT_API
#endif

namespace discover
{

typedef bool (*EnumerateFunc2) (char* lpFileOrPath, vector<string>& FileList);
class DLL_EXPORT_API File
{
public:
	virtual ~File() {};

	
	virtual int ReadDirFile2(char* cSrcDir, vector<string>& dataMatrix , vector<string>& vsFileList);
	virtual void doFileEnumeration2 (string lpPath, bool bRecursion, bool bEnumFiles, EnumerateFunc2 pFunc, vector<string>& FileList);

protected:
	File() {};
};


#ifdef _WINDOWS
#include <Windows.h>


class DLL_EXPORT_API winFile:public File
{
public:
	winFile(){};
	virtual ~winFile(){};

	int ReadDirFile2(char* cSrcDir, vector<string>& dataMatrix , vector<string>& vsFileList);
	void doFileEnumeration2(string lpPath, bool bRecursion, bool bEnumFiles, EnumerateFunc2 pFunc, vector<string>& FileList);
	BOOL StringToWString(const std::string &str,std::wstring &wstr);
	BOOL WStringToString(const std::wstring &wstr,std::string &str);
	void cutFileName(vector<string> &FilePath, vector<string> &FileName);
};
#else
class linuxFile:public File
{
public:
	linuxFile(){};
	virtual ~linuxFile(){};
	int ReadDirFile2 (char* cSrcDir, vector<string>& dataMatrix , vector<string>& vsFileList);
	//void doFileEnumeration2(string lpPath, bool bRecursion, bool bEnumFiles, char* pFunc, vector<string>& FileList);
	void doFileEnumeration2(string lpPath, bool bRecursion, bool bEnumFiles, EnumerateFunc2 pFunc, vector<string>& FileList);
};

}
#endif
