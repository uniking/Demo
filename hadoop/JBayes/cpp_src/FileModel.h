#pragma once
#include "Model.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

/*
��Ҷ˹ģ���࣬ ģ�ʹ����json�ļ���
*/
class CFileModel:public CModel
{
public:
	string m_filepath;
	
public:
	CFileModel(string& path);
	CFileModel();
	
	int JsonRead(string& sContent);
	int JsonWrite();
	
	virtual int loadmodule();
	virtual int loadmodule(string& content);
	virtual int savemodule();

};