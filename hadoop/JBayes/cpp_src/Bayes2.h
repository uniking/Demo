#pragma once
#ifdef WIN32
#include <Windows.h>
#endif


#include "FileSystem.h"

#include "FileModel.h"

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

#ifdef WIN32
#define DLL_EXPORT_API __declspec(dllexport)
#else
#define DLL_EXPORT_API
#endif


#define  ContentMatrix vector<vector<float> >
#define  TFIDFMatrix vector<map<float,float> > //(id,����)
typedef vector<string> StrVec; //�ַ�������
typedef vector<int> IntVec; //��������
typedef vector<vector<int> > Int2DVec;//������ά����
typedef vector<vector<double> > Double2DVec;//��������ά����
typedef vector<double> DoubleVec;//����������


/*
ԭ��
           P(A|B)*P(B)
P(B|A) = --------------
             P(A)


*/
class DLL_EXPORT_API CBayes
{
public:
	map< int , vector<float> > m_ClassAttrSet;
	map< int, vector<int> > m_ClassList;
	vector<CModel*> m_ModelList;
	vector< map<string, float> > m_Model;
	bool m_isLoadModel;
	discover::File* m_File;
   vector<int> m_current_file_num;
   vector<string> m_className;

   map< string, CModel* > m_classNM;

public:
#ifdef WIN32
	CBayes(){m_File = new discover::winFile();  m_isLoadModel=false; m_current_file_num.resize(100);};
#else
	CBayes(){m_File = new discover::linuxFile(); m_isLoadModel=false; m_current_file_num.resize(100);};
#endif
	~CBayes();

	
	/*
	������
	���ļ��г�ȡһЩ������Ϊһ�������Լ���

	������
	tfidf TFIDF�����������������������дʵ�TFIDFֵ
	vclass ָ��tfidf�еķ������
	classatrribute ���س�ȡ��������

	����ֵ��
	0 ��ʾ�ɹ�
	*/
	int BYSelectAttributeFromClassFile4(TFIDFMatrix tfidf, 
		vector< vector<int> > vclass, 
		vector< vector<float> >& classattribute);

	/*
	������
	����������Լ���

	������
	ClassId Ҫ���õ���id
	classatrribute �����б�����б�����������ģ��

	����ֵ��
	0 �ɹ�
	*/
	int BYSetClassAttribute4(int ClassId, vector<float> classatrribute);

	/*
	Ϊָ������������ģ��
	ClassId ��Id
	*/
	int BYCreateClassModel4(ContentMatrix& content, 
		vector< StrVec >& DatawordMatrix, 
		int ClassId, 
		string ModelFile, float threshold=0);

	/*
	������
	����ָ��Ŀ¼�ڵ�����ģ���ļ���һ����һ��ģ�ͣ�

	������
	ModelDir ģ���ļ���Ŀ¼

	����ֵ��
	0 �ɹ�
	*/
	int BYLoadClassModel4(string ModelDir);
	int BYLoadClassModel4(vector<string>& Models);


	/*
	������
	�����ļ�������ÿ��ģ���еĸ���

	������
	Content Ҫ�жϵ��ı�����
	ProbabilityList �����ڸ������еĸ���
	*/
	int BYPredict4(string Content, vector<float>& ProbabilityList);

	/*
	������
	Ϊ�ж��Ƿ�Ϊ�����ļ�������ֵ

	������
	threshold ��ֵ��������ĸ��ʳ�������ֵ����Ϊ�����ļ�

	����ֵ��
	0 ��ʾ�ɹ�
	*/
	int SetThreshold4(float threshold);

	/*
	�ж��Ƿ���������Ϣ����ҪԤ��������ֵ
	Content Ҫ�жϵ��ı�����
	ClassName ��������������
	�������false����˵���������κ���
	*/
	bool IsAttractiveContent4(vector<string> Words, string &uid, string& level, string& ClassName, float& oSimilarity, vector<string>& KeyWords);
   
   


	/*
	������
	�����ļ���ָ��ģ�͵����ƶȣ� һ���ļ����дʻ���ֵĸ���֮��Ϊ1�� ����ֵΪģ�����ļ�����Ľ�������֤�˽����������֮����0-1��Χ�ڡ�

	������
	Model ģ���ļ�
	ctWordsList �ļ���ÿ���ʻ�ĸ���
	Similarity �����ļ���ָ��ģ�͵����ƶ�

	����ֵ��
	0 ��ʾ�ɹ�
	*/
	int CalculateFileSimilarityInModel4(map<string, float> Model, map<string, float> ctWordsList, float& Similarity);

	/*
	������
	�����ļ���ÿ��������ֵĸ��ʣ� �������ļ����ظ�����Խ�����Խ��

	������
	Words �ļ��е����дʻ㣬�ʻ���ظ�
	ctWordsList �����ļ���ÿ���ʻ���ֵĸ���
	*/
	int CalculateWordProInFile4(StrVec& Words, map<string, float>& ctWordsList);

	/*
	������
	����һ���ļ�Ӧ�������ĸ���

	������
	vclass vclass[n]��ʾ��n�����ļ������

	����ֵ��
	0 �ɹ�
	*/

	int BYSetClassList4(vector< vector<int> > vclass);


	/*
	������
	���������һ���ļ��еĸ���  ������ִ���/һ���ļ��Ĵʻ�����

	������
	content ���ݾ���
	ClassId ָ�����id
	wordPro ���شʻ�ĸ���

	����ֵ��
	0 �ɹ�
	*/
	int BYCreateWordProbabilityInClass4(ContentMatrix& content, int ClassId, map<string, float>& wordPro);

	/*
	������
	������ͬһ���ļ����ɵ�ģ���У� ÿ���ļ������ƶȣ�����һ�����ֵ��һ����Сֵ

	������
	DatawordMatrix ͬһ���ļ��Ĵ������
	ClassId ģ��id
	wordPro ͬһ���ļ�������ָ��ģ���еĴ������
	MinSimilarity ����������ƶ�
	MaxSimilarity ����������ƶ�

	����ֵ��
	0 ��ʾ�ɹ�
	*/
	int CalculateSimilaritryRange4(vector< StrVec > DatawordMatrix, 
		int ClassId, 
		map<string, float>& wordPro,
		float& MinSimilarity,
		float& MaxSimilarity
		);

	/*
	������
	����һ���ļ�����ĳ��ģ�͵ĸ��ʣ��㷨��ȡ�ļ�������ģ�ʹ���Ľ����� ���������Ӧ�ĸ������

	������
	ModelId ģ������id
	Words �ļ����еĴʻ��
	Probability �����ļ�����ָ��ģ�͵ĸ���
	KeyWords �����ļ���ģ�͵Ľ���

	����ֵ��
	0 ��ʾ�ɹ�

	*/
	int CalculateFileProInModel4(int ModelId, StrVec Words, float& Probability, vector<string>& KeyWords);

	/*
	������
	�ж�ģ���Ƿ���سɹ�
	
	������
	��

	����ֵ��
	true ���سɹ�
	false ����ʧ��
	*/
	bool IsModelOk();

   void SetClassName(vector<string>& className);
};
