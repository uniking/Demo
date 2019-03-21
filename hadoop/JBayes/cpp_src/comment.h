#pragma once
#ifdef WIN32
#include <Windows.h>
#endif

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;



#define  ContentMatrix vector<vector<float> >
#define  TFIDFMatrix vector<map<float,float> > //(id,����)
typedef vector<string> StrVec; //�ַ�������
typedef vector<int> IntVec; //��������
typedef vector<vector<int> > Int2DVec;//������ά����
typedef vector<vector<double> > Double2DVec;//��������ά����
typedef vector<double> DoubleVec;//����������

void ictclas30(string& input, StrVec& retWords);

void TFIDF(ContentMatrix& content, TFIDFMatrix& tfidf);
void TFIDFKMeans(TFIDFMatrix& tfidf, int k, vector<int>& vclass, TFIDFMatrix& centAttri);
void MapToMultimap(map<float, float>& fMap, multimap<float, float>& mMap);

void ReverseSelectAttrFromMultimap(multimap<float, float>& mMap, vector<float>& Attr , int n);
void ReverseSelectAttrFromMultimap2(multimap<float, float>& mMap, vector<float>& Attr);
/*
content ���ݾ���
tfidf TFIDF�����������������������дʵ�TFIDFֵ
vclass ָ��tfidf�еķ������
classatrribute ���س�ȡ��������
*/
int BYSelectAttributeFromClassFile(TFIDFMatrix tfidf, 
								   vector< vector<int> > vclass, 
								   vector< vector<float> >& classattribute);

/*
ClassNumber Ҫ���õ���id
classatrribute �����б�����б�����������ģ��
*/
int BYSetClassAttribute(int ClassId, vector<float> classatrribute);


/*
�ж������������
Content Ҫ�жϵ��ı�����
ProbabilityList �����ڸ������еĸ���
*/
int BYPredict(string Content, vector<float>& ProbabilityList);

/*
Ϊ�ж��Ƿ�Ϊ�����ļ�������ֵ
threshold ��ֵ��������ĸ��ʳ�������ֵ����Ϊ�����ļ�
*/
int SetThreshold(float threshold);

/*
�ж��Ƿ���������Ϣ����ҪԤ��������ֵ
Content Ҫ�жϵ��ı�����
ClassName ��������������
�������false����˵���������κ���
*/
bool IsAttractiveContent(string Content, string& ClassName, float& oSimilarity, vector<string>& KeyWords);

int GetModelNameById(int ClassId, string& ClassName);

int GetWordById(float id, string& word);
int GetIdByWord(string& word, float& id);
int InsertWordAndId(string word, float id);
bool TFWordIdOk();
