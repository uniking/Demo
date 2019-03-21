#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

#ifdef WIN32
#define DLL_EXPORT_API __declspec(dllexport)
#else
#define DLL_EXPORT_API
#endif

/*
��Ҷ˹ģ�ͣ���������һ������
*/
class DLL_EXPORT_API CModel
{
public:
	string m_level;//��ȫ����
	string m_modulename;//ģ�͵�����
	string m_uid;
	map<string, float> m_wordPro;//���ʵ��������
	float m_thresholdRange[2];//������ֵ��Χ
	float m_threshold;//ʹ����ֵ
	int m_filenumber;//����ģ����ʹ�õ��ļ���Ŀ
   bool m_positive;

public:
	CModel();
	virtual ~CModel();
	virtual int loadmodule();
	virtual int loadmodule(string& path);
	virtual int savemodule();

	map<string, float> *getwordpro();
	string getmodulename();
	string getuid();
	string getlevel();
	int getthresholdrange(float* buffer);
	float getthreshold();
	int getfilenumber();

	int setwordpro(map<string, float>& wordpro);
	int setmodulename (string& modulename);
	int setthresholdrange(float* buffer);
	int setthreshold(float threshold);
	int setfilenumber(int filenumber);

    bool is_positive();
    void set_positive(bool positive);
};
