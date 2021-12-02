#include "Common.h"
#include<algorithm>
vector<int> setDifference(vector<int> E, vector<int> F)
{
	vector<int> X(E.size());
	vector<int>::iterator  outIt;
	
	sort(E.begin(),E.end());
	sort(F.begin(),F.end());

	outIt=set_difference(E.begin(),E.end(),
		                 F.begin(),F.end(),
		                 X.begin());
	X.erase(outIt,X.end());

	return X;
}

vector<int> setSubtract(vector<int> E,int i)
{
	vector<int>::iterator it;
	for(it=E.begin();it!=E.end();)
	{
		if(*it==i)
			it=E.erase(it);
		else
			it++;
	}
	
	return E;
}
	

//集合E和F的并集X
vector<int> setUnion(vector<int> E, vector<int> F)
{
	vector<int> X(E.size()+F.size());
	vector<int>::iterator  outIt;
	
	sort(E.begin(),E.end());
	sort(F.begin(),F.end());

	outIt=set_union(E.begin(),E.end(),
		            F.begin(),F.end(),
		            X.begin());
	X.erase(outIt,X.end());

	return X;
}

//集合E和i的并集X
vector<int> setAdd(vector<int> E, int i)
{
	vector<int> F;
	F.push_back(i);
	return setUnion(E,F);
}
  
//集合E和F的交集X
vector<int> setIntersection(vector<int> E, vector<int> F)
{
	vector<int> X(E.size()+F.size());
	vector<int>::iterator  outIt;
	
	sort(E.begin(),E.end());
	sort(F.begin(),F.end());

	outIt=set_intersection(E.begin(),E.end(),
		            F.begin(),F.end(),
		            X.begin());
	X.erase(outIt,X.end());

	return X;
}

//非重复元素集合E是否包含非重复元素集合F
bool include(vector<int> E, vector<int> F)
{
	vector<int> X(E.size());
	X=setDifference(E,F);
	return X.size()==E.size()-F.size();
}

//非重复元素集合E是否包含元素i
bool eleInclude(vector<int> E, int i)
{
	vector<int> F;
	F.push_back(i);
	return include(E,F);
}

//集合F放在集合E后面
vector<int> setPushBack(vector<int>E, vector<int> F)
{
	vector<int>::iterator it;

	if(F.empty())
		return E;
	else
	{
		for(it=F.begin();it!=F.end();it++)
			E.push_back(*it);
		return E;
	}
}


int Max(int a, int b)
{
	return (a>b)? a:b;
}

int Min(int a, int b)
{
	return (a<b)? a:b;
}

//在V中插入s~e的整数
void INSERT_ELEMENTS(vector<int> &V,int s,int e)
{
	for(int i=s;i<=e;i++)
		V.push_back(i);
}

int FindPosition(vector<int> vec,int val)
{
	int position;
	vector<int>::iterator it;
	for(it=vec.begin(),position=0;it!=vec.end();it++,position++)
	{
		if(*it==val)
			return position;
	}
}

int find(vector<int> X,vector<int> Y,int e)
{
	vector<int>::iterator it;
	int temp=e;
	while(eleInclude(Y,temp))
	{
		temp=X[FindPosition(Y,temp)];

	}
	return temp;

}