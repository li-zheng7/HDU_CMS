#include "Chromosome.h"
#include "Common.h"
#include<iostream>
#include<algorithm>
#include<iomanip>
#include "Part.h"
/*Chromosome::Chromosome(int c)
:c(c)
{
	sub_chrom = new vector<int> [c+1];
}
*/

Chromosome::Chromosome(int c)
:c(c)
{
	//pp=new Part(m,k);
	sub_chrom = new vector <int> [c+1];
	
}
Chromosome::Chromosome(int m,int c)
:m(m),
c(c)
{
	//pp=new Part(m,k);
	
	sub_chrom = new vector <int> [c+1];
	INSERT_ELEMENTS(chrom,1,m);
	random_shuffle(chrom.begin(),chrom.end());
	//dispatch();


}
/*
void Chromosome::pini(int k)
{
		vector<int> p,q;
	INSERT_ELEMENTS(p,1,m);
	for(int i=0;i<=k;i++)
	{
		random_shuffle(p.begin(),p.end());
		q=p;
		q.insert (q.begin(),0);
		q.erase(q.end()-1);
		pp->pa[i].v=p;
		pp->pa[i].predecessor=q;	
	}
	cout<<"-------------------------"<<endl;
}
*/
Chromosome::~Chromosome(void)
{
	
	//delete pp;
	delete []sub_chrom;
	
}
/*
void Chromosome::dispatch()
{
	vector<int>::iterator itx;
	int i=1;
	for(itx=chrom.begin();itx!=chrom.end();itx++,i++)
	{
		if(i<=c)
			sub_chrom[i].push_back (*itx);
		else
		{
			vector<float>comp;
			for(int j=1;j<=c;j++)
			{
				comp.push_back (AS(*itx,sub_chrom[j]));
			}

			vector<float>::iterator maxPosition = max_element(comp.begin(), comp.end());
			if((maxPosition-comp.begin())==0)
				sub_chrom[1].push_back (*itx);
			else
			sub_chrom[(maxPosition-comp.begin())].push_back (*itx);

		}
	}
	
}
float Chromosome::AS(int n,vector<int> a)
{
	vector<int>::iterator it;
	float ts=0,t=0;

	for(it=a.begin();it!=a.end();it++)
		t+=ff(n,*it);
	for(it=chrom.begin();it!=chrom.end();it++)
		ts+=ff(n,*it);
	return t*1.0/(ts+1);

}

float Chromosome::ff(int a,int b)
{
	/*
	//float d=(pp->dq)*(pp->f(a,b));
	//return d;
	
	float t=0;
	//vector<Job>::iterator it;
	
	for(int i=0;i<=k;i++)
	{
		if(pp->pa[i].v[FindPosition(pp->pa[i].predecessor,a)]==b)
			t++;

		if(pp->pa[i].v[FindPosition(pp->pa[i].predecessor,b)]==a)
			t++;

	}
		return t;
}
*/
void Chromosome::display()
{
	//Part p(m);
	vector<int>::iterator it,it1;
	for(it=chrom.begin();it!=chrom.end();it++)	
		cout<<setw(2)<<*it;
	cout<<endl;
	for(int i=1;i<=c;i++)
	{
		cout<<"cell"<<i;
		for(it1=sub_chrom[i].begin();it1!=sub_chrom[i].end();it1++)
			cout<<setw(2)<<*it1;
		cout<<endl;
	}
	/*for(int i=0;i<m;i++)
	{
		cout<<setw(3)<<pp->pa[i].v;
			
	}
	cout<<endl;
	for(int i=0;i<m;i++)
	{
		cout<<setw(3)<<pp->pa[i].predecessor;
			
	}

	cout<<endl;*/

}
/*
float Chromosome::compute_tt()
{
	vector<int>::iterator it1,it2;
	float z=0;
	for(int i=1;i<=c;i++)
	{
		for(int j=c;j>i;j--)
		{

			for(it1=sub_chrom[i].begin();it1!=sub_chrom[i].end();it1++)
				for(it2=sub_chrom[j].begin();it2!=sub_chrom[j].end();it2++)
					 z+=ff(*it1,*it2);

			
		}
	}
	return z;
}
*/