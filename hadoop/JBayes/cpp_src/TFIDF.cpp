// TFIDF.cpp : Defines the entry point for the console application.
//

#include "comment.h"
//#include "File.h"
//#include "convert.h"

#define _debug_kmeans


/*
TF-IDF�㷨����������һ���ʻ����Ҫ�̶ȣ�ԭ����һ���ʻ��������ڳ��ֵĴ���Խ��Ȩ��Խ�ߣ�
�������Ͽ��г��ֵĴ���Խ��Ȩ��Խ�͡� ������ǽ������ļ��Ĵ��鼯����Ϊ���Ͽ⡣
*/
void TFIDF(ContentMatrix& content, TFIDFMatrix& tfidf)
{
	int wordsum = 0;
	unsigned int i = 0;
	TFIDFMatrix InsideFrequency;//�ڲ���Ƶ����
	map<float,float> TotalityFrequency;//�����Ƶ��
	map<float,float> CorpusFrequency;//�ʻ�nƪ������

	//ͳ�ƴʻ��������ļ��ڴʻ�Ƶ��
	ContentMatrix::iterator pC = content.begin();
	while(pC != content.end())
	{
		//ͳ���ļ��ʻ�Ƶ��
		vector<float> record;
		vector<float>::iterator pWord = pC->begin();
		map<float,float> fileinside;

		for (i=0; i< pC->size(); ++i)
		{//����һƪ����
			map<float,float>::iterator pIter;
			pIter = fileinside.find(pWord[i]);
			if (pIter != fileinside.end())
			{
				pIter->second++;
			}
			else
			{
				fileinside.insert(make_pair(pWord[i], 1));
			}

			//�����Ƶ
			pIter = TotalityFrequency.find(pWord[i]);
			if (pIter != TotalityFrequency.end())
			{
				pIter->second++;
			}
			else
			{
				TotalityFrequency.insert(make_pair(pWord[i], 1));
			}

			//Ԥ��Ƶ��
			pIter = CorpusFrequency.find(pWord[i]);
			
			if (pIter != CorpusFrequency.end())
			{
				vector<float>::iterator pRecord = find(record.begin(), record.end(), pWord[i]);
				if (pRecord != record.end())
				{
				}
				else
				{
					pIter->second++;
					record.push_back(pWord[i]);
				}
				
			}
			else
			{
				CorpusFrequency.insert(make_pair(pWord[i], 1));
				record.push_back(pWord[i]);
			}
		}

		InsideFrequency.push_back(fileinside);

		//ͳ���ܴʻ���
		wordsum += pC->size();
		++pC;
	}

	//����TF-IDFֵ
	pC = content.begin();
	TFIDFMatrix::iterator pFrequ = InsideFrequency.begin();
	while(pC != content.end())
	{
		float TF = 0;
		float IDF = 0;
		map<float,float>::iterator oneP = pFrequ->begin();
		while(oneP != pFrequ->end())
		{//����һƪ�������дʻ�
			map<float,float>::iterator pCorpusNum = CorpusFrequency.find(oneP->first);
			TF = oneP->second / pC->size(); //��Ƶ��TF��=ĳ�ؼ��ʳ��ִ���/�����йؼ�������
			IDF = log(content.size()/(pCorpusNum->second +1))   ; //���ĵ�Ƶ�ʣ�IDF��=log�����Ͽ��ĵ�����/�������ôʵ��ĵ���+1����
			
			oneP->second = TF*IDF;
			++oneP;
		}

		++pC;
		++pFrequ;
	}

	tfidf = InsideFrequency;
}

//
//�������¼��TFIDF���ƶ�
//���ڼ�������A����ƪ���¸��ӽ�
//������ԭ����ƪ���£��ʻ��ظ�Խ�����ƶ�Խ�ߣ� �ʻ��TF-IDFԽ�����ƶ�Խ��
//
void TFIDFDistance(TFIDFMatrix& tfidf, vector<vector<float> >& distance)
{
	//������㣺A��B��ȡ��ͬ�ʻ�TFIDF֮��
	int i=0;
	
	TFIDFMatrix::iterator iter = tfidf.begin();
	while(iter != tfidf.end())
	{
		i=0;
		vector<float> essayDistance;

		TFIDFMatrix::iterator iterCmp = tfidf.begin();
		while(iterCmp != tfidf.end())
		{
			essayDistance.push_back(0);
			if (iter == iterCmp)
			{//�Լ����Լ������ƶȼ�Ϊ0
				;
			}
			else
			{//�������������µ����ƶ�
				
				if (iter->size() < iterCmp->size())
				{
					map<float,float>::iterator itermap = iter->begin();
					while(itermap != iter->end())
					{
						map<float,float>::iterator pFind = iterCmp->find(itermap->first);
						if (pFind != iterCmp->end())
						{
							essayDistance[i] += (pFind->second+itermap->second);
						}

						++itermap;
					}
				}
				else
				{
					map<float,float>::iterator itermap = iterCmp->begin();
					while(itermap != iterCmp->end())
					{
						map<float,float>::iterator pFind = iter->find(itermap->first);
						if (pFind != iter->end())
						{
							essayDistance[i] += (pFind->second+itermap->second);
						}

						++itermap;
					}
				}
			}

			++iterCmp;
			++i;
		}

		distance.push_back(essayDistance);
		++iter;
	}
}

void MapToMultimap(map<float, float>& fMap, multimap<float, float>& mMap)
{
	map<float, float>::iterator pIter = fMap.begin();
	while(pIter != fMap.end())
	{
		mMap.insert(make_pair(pIter->second, pIter->first));

		++pIter;
	}

}

void ReverseSelectAttrFromMultimap(multimap<float, float>& mMap, vector<float>& Attr , int n)
{
	if( 0 == mMap.size() )
	{
		return;
	}
	//���ٷֱ�
	multimap<float, float>::iterator mIter = mMap.end();
	mIter--;
	while(n>0)
	{
		Attr.push_back(mIter->second);

		mIter--;
		n--;
	}

	//����Ȩ���ж�
	mIter = mMap.end();
	mIter--;
	while(mIter != mMap.begin())
	{
		if (mIter->first < 0.015)
		{
			break;
		}
		Attr.push_back(mIter->second);

		mIter--;
	}
}

void ReverseSelectAttrFromMultimap2(multimap<float, float>& mMap, vector<float>& Attr)
{
    if( 0 == mMap.size() )
    {
        return;
    }

    float sum = 0;
    multimap<float, float>::iterator tmp_it = mMap.begin();
    while(tmp_it != mMap.end())
    {
        sum += (*tmp_it).first;
        ++tmp_it;
    }
    sum /= mMap.size();

    multimap<float, float>::iterator mIter = mMap.begin();
    while(mIter != mMap.end())
    {
        if(mIter->first > sum)
            Attr.push_back(mIter->second);
        ++mIter;
    }

    //����Ȩ���ж�
    mIter = mMap.begin();
    while(mIter != mMap.end())
    {
        if (mIter->first > 0.015)
            Attr.push_back(mIter->second);
        ++mIter;
    }
}

//����n���ڵ�ľ�ֵ������һ��ƽ��ֵ
void TFIDFMeans(TFIDFMatrix& nodeset, map<float, float>& mean)
{
	//int n= nodeset.size();
	int rep=0;
	multimap<float, float> temp;

	TFIDFMatrix::iterator element = nodeset.begin();

	while(element != nodeset.end())
	{
		if (0 == element->size())
		{
			++element;
			continue;
		}
		//���ٷֱ�ȡ�ؼ���
		//rep = element->size()/3;//ȡ����֮һ
		//if (rep==0)
		//{
		//	rep = 1;//����ȡһ���ؼ���
		//}

		//���� ʹ��1~15���ؼ���
		rep = element->size();//ȡ����֮һ
		if (rep>30)
		{
			rep = 30;//ÿƪ����ֻȡ30���ؼ���
		}

		//��TFIDF���� temp
		MapToMultimap(*element, temp);
		multimap<float, float>::iterator mIter = temp.end();
		mIter--;
		while(--rep)
		{
			map<float, float>::iterator pFind = mean.find(mIter->second);
			if (pFind != mean.end())
			{
				if (pFind->second < mIter->first)
				{
					pFind->second = mIter->first;
				}
			}
			else
			{
				mean.insert(make_pair(mIter->second, mIter->first));
			}
			
			--mIter;
		}

		++element;
	}

}

//�������ĵ㵽�����ڵ�ľ���
void TFIDFMeansDistance(map<float, float>& mean, TFIDFMatrix& nodeset,  vector<float>& distance)
{
	multimap<float, float> temp;
	
	TFIDFMatrix::iterator element = nodeset.begin();
	while(element != nodeset.end())
	{
		float fDistance = 0;
		map<float,float>::iterator mdElement = element->begin();
		while(mdElement != element->end())
		{
			map<float,float>::iterator mdFind = mean.find(mdElement->first);
			if (mdFind != mean.end())
			{
				fDistance += (mdElement->second);
			}

			++mdElement;
		}

		distance.push_back(fDistance);

		++element;
	}

}

void KMeansInitClass(int K, TFIDFMatrix tfidf, vector<int>& rclass)
{
	vector<vector<float> > distance;
	int currentClass = 0;
	int tempClass = 0;
	int i,j,x;
	float mix = 10000;

	TFIDFDistance(tfidf, distance);
	rclass.push_back(0);//��һ��0


	for (i=0; i<K-1; ++i)
	{
		vector<vector<float> >::iterator pDistance = distance.begin();
		j=0;
		while(j<currentClass)
		{
			++pDistance;
			++j;
		}

		vector<float>::iterator pEle = pDistance->begin();
		x=0;
		while(pEle != pDistance->end())
		{
			if (*pEle < mix &&
				x != currentClass &&
				find(rclass.begin(), rclass.end(), x) == rclass.end())
			{
				mix = *pEle;
				tempClass = x;
			}

			++pEle;
			++x;
		}

		mix = 10000;
		currentClass = tempClass;
		rclass.push_back(currentClass);

		
	}
}

void TFIDFKMeans(TFIDFMatrix& tfidf, int k, vector<int>& vclass, TFIDFMatrix& centAttri)
{
	//time_t Time;
	int i=0, j=0;
	vector<TFIDFMatrix> clusters(k);//��¼
	vector<int> clusterAssignments;//������
	vector<int> nearestCluster;//��̬����õ��������
	float nearestDistance;
	TFIDFMatrix coordinates(k);//������
	vector<vector<float> > CtoEdistance(k);//���ĵ�����Ԫ�صľ���
	int nElement = tfidf.size();

	clusterAssignments.resize(nElement);
	nearestCluster.resize(nElement);

	//�����ʼ��k����
	//localtime(&Time);
	//srand(Time);
	//for(i=0; i<k; ++i)
	//{
	//	map<float,float> initNode = tfidf[rand()%nElement];
	//	TFIDFMatrix initMatrix;
	//	initMatrix.push_back(initNode);
	//	clusters[i] = initMatrix;
	//}
	//�̶�����
	vector<int> rclass;
	KMeansInitClass(k, tfidf, rclass);
	for (i=0; i<k; ++i)
	{
		map<float,float> initNode = tfidf[rclass[i]];
		TFIDFMatrix initMatrix;
		initMatrix.push_back(initNode);
		clusters[i] = initMatrix;
	}

	while(true)
	{
		//���´�����
		for (i=0; i<k; ++i)
		{
			TFIDFMeans(clusters[i],coordinates[i]);
		}

		//����ÿ�����ݺ�ÿ���������ĵľ���
		for (i=0; i<k; ++i)
		{
			TFIDFMeansDistance(coordinates[i], tfidf, CtoEdistance[i]);
		}

		//����ÿ���������ĸ����������Ȼ�����ǹ�Ϊһ��
		for(i=0; i<nElement; ++i)
		{
			nearestDistance = 0;
			nearestCluster[i] = 0;
			for(j=0; j<k; ++j)
			{
				vector<float> nearest;
				nearest = CtoEdistance[j];
				if(nearestDistance < nearest[i])
				{
					nearestDistance = nearest[i];
					nearestCluster[i] = j;
				}
			}

			//i����nearestCluster��
		}

		//4���Ƚ�ÿ����������ľ����Ƿ�����������ľ���
		//���ȫ��ȱ�ʾ���еĵ��Ѿ�����Ѿ����ˣ�ֱ�ӷ��أ�
		for(i=0, j=0; i<nElement; ++i)
		{
			if (nearestCluster[i] == clusterAssignments[i])
			{
				++j;
			}
		}

		if (j == nElement)
		{//��ȫƥ��
			vclass = clusterAssignments;
			centAttri = coordinates;
			break;
		}


		//5��������Ҫ���µ������ϵ��Ⱥ����Ĺ�ϵ��������Ϻ������¿�ʼѭ����
		//��Ҫ�޸�ÿ������ĳ�Ա�ͱ�ʾĳ�����������ĸ�����ı���
		coordinates.clear();
		clusters.clear();
		clusters.resize(k);
		coordinates.resize(k);
		for(i=0; i<nElement; ++i)
		{
			vector<TFIDFMatrix>::iterator pClusters = clusters.begin();
			TFIDFMatrix::iterator clustersF;

			for (j=0; j<nearestCluster[i]; ++j)
			{
				++pClusters;
			}

			clusterAssignments[i] = nearestCluster[i];
			pClusters->push_back(tfidf[i]);
		}



	}


}


void ictclas30(string& input, StrVec& retWords)
{//�ִ��㷨��inputΪ���봮,retWordsΪ��������ֿ��ĵ���,����ͼ򵥻������ˣ��Կո��Ϊ�ָ������зִ�
	//Dic->SplitWord(input, retWords);
}

int GetWordById(float id, string& word)
{
	
	return 0; //Dic->GetWord(id, word);
}

int GetIdByWord(string& word, float& id)
{
	return 0;//Dic->GetId(word, id);
}

int InsertWordAndId(string word, float id)
{
	return 0;//Dic->InsertWordId(word, id);
}

bool TFWordIdOk()
{
	return false;//Dic->WordIdOk();
}
