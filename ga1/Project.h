#pragma once
#include "Population.h"
class Project
{
public:
	int m;
	int c;
	int k;
	Part *part;
	float Generic_tt1;
	Project(int m,int c,int k);
	~Project(void);
	void Generic1();
	void Initialpop(Population *pop);
	float ff(int a,int b);
	float AS(int n,vector<int>a,Chromosome * chr);
	void dispatch(Chromosome * chr);
	
    
	float compute_tt(Chromosome * chr);
	vector<Chromosome*> crossover(Population *pop);
	Chromosome * chrom_cross(Chromosome *c1,Chromosome *c2);//����Chromosome�ľ�������

	vector<Chromosome*> mutation(Population *pop);
	Chromosome * muta(Chromosome *chr);//����Chromosome��mutation

	Population * selection(Population *pop);//����ѡ��
	
};
