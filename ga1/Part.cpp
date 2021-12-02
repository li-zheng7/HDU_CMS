#include "Part.h"
#include<vector>
#include "Common.h"
#include<algorithm>
#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;
Part::Part(int m,int k)
:m(m),k(k)
{
	pa = new Job[k+1];
	
	srand(time(0));
	//vector<Job>::iterator ir;
	//ir=pa.begin()
	for(int i=0;i<=k;i++)
	{
		vector<int> p,q;
		INSERT_ELEMENTS(p,(rand()%(m/2))+1,rand()%(m/2+1)+m/2);
		random_shuffle(p.begin(),p.end());
		pa[i].dq=rand()%101;//
	
		q=p;
		q.insert (q.begin(),0);
		q.erase(q.end()-1);
		pa[i].v=p;
		pa[i].predecessor=q;
		vector<int>::iterator it;
		cout<<"该工件加工工序：";
		for(it=pa[i].v.begin();it!=pa[i].v.end();it++)	
			cout<<setw(3)<<*it;
		cout<<"---此款生产件数"<<pa[i].dq;
		cout<<endl;
	}
	cout<<"---------------"<<endl;
	
}
/*
float Part::f(int a,int b)
{
	float t=0;
	//vector<Job>::iterator it;
	
	for(int i=0;i<=dq;i++)
	{
		if(pa[i].v[FindPosition(pa[i].predecessor,a)]==b)
			t++;

		if(pa[i].v[FindPosition(pa[i].predecessor,b)]==a)
			t++;

	}
		return t;
}
*/

Part::~Part(void)
{
	cout<<"---------------"<<endl;
	delete []pa;
	/*vector<Job*>::iterator it;
	for(it=part.begin();it!=part.end();it++)
		delete *it;*/
}
