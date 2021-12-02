#include "Project.h"
#include "Population.h"
#include "Globals.h"
#include "Chromosome.h"
#include "Common.h"
#include <math.h>
#include<algorithm>
Project::Project(int m,int c,int k)
:m(m),
c(c),k(k)
{
	part=new Part(m,k);
}

Project::~Project(void)
{
	delete part;
}

void Project::Initialpop(Population *pop)
{
	pop->generation = 1;

	for(int k=1;k<=popsize;k++)
	{
		Chromosome * chr = new Chromosome(m,c);
		chr->fitness = compute_tt(chr);
		pop->vec_chrom.push_back(chr);
	}
	pop->compute_sum_ave_min_fitness();
	
}
void Project::dispatch(Chromosome * chr)
{
	vector<int>::iterator itx;
	int i=1;
	for(itx=chr->chrom.begin();itx!=chr->chrom.end();itx++,i++)
	{
		if(i<=chr->c)
			chr->sub_chrom[i].push_back (*itx);
		else
		{
			vector<float>comp;
			for(int j=1;j<=chr->c;j++)
			{
				comp.push_back (AS(*itx,chr->sub_chrom[j],chr));
			}

			vector<float>::iterator maxPosition = max_element(comp.begin(), comp.end());
			int a=(std::distance(comp.begin(),maxPosition)+1);
			chr->sub_chrom[a].push_back (*itx);

		}
	}
	
}
float Project::AS(int n,vector<int> a,Chromosome * chr)
{
	vector<int>::iterator it;
	float ts=0,t=0;

	for(it=a.begin();it!=a.end();it++)
		t+=ff(n,*it);
	for(it=chr->chrom.begin();it!=chr->chrom.end();it++)
		ts+=ff(n,*it);
	return (t*1.0/ts);

}

float Project::ff(int a,int b)
{
	
	//float d=(pp->dq)*(pp->f(a,b));
	//return d;
	
	
	//vector<Job>::iterator it;
	float sum=0;
	for(int i=0;i<=part->k;i++)
	{
		float t=0;
		if(eleInclude(part->pa[i].predecessor,a)&&part->pa[i].v[FindPosition(part->pa[i].predecessor,a)]==b)
			t+=(part->pa[i].dq);

		if(eleInclude(part->pa[i].predecessor,b)&&part->pa[i].v[FindPosition(part->pa[i].predecessor,b)]==a)
			t+=(part->pa[i].dq);
		sum+=t;

	}
		return sum;
}


float Project::compute_tt(Chromosome * chr)
{
	dispatch(chr);
	vector<int>::iterator it1,it2;
	float z=0;
	for(int i=1;i<=c;i++)
	{
		for(int j=c;j>i;j--)
		{

			for(it1=chr->sub_chrom[i].begin();it1!=chr->sub_chrom[i].end();it1++)
				for(it2=chr->sub_chrom[j].begin();it2!=chr->sub_chrom[j].end();it2++)
					 z+=ff(*it1,*it2);

			
		}
	}
	return z;
}
///////////////////////////////////////////////////////
vector<Chromosome*> Project::crossover(Population *pop)
{
	Chromosome * new_chromosome;
	vector<Chromosome*> vec_new_chrom;
	vector<Chromosome*> vec_chrom = pop->vec_chrom;
	vector<Chromosome*>::iterator iti,itj,tem;
	tem=vec_chrom.end();
	tem--;
	for(iti=vec_chrom.begin();iti!=tem;iti++)
	{
		for(itj=++iti,iti--;itj!=vec_chrom.end();itj++)
		{
			new_chromosome = chrom_cross(*iti,*itj);
			if(new_chromosome->fitness <= pop->ave_fitness)
				vec_new_chrom.push_back(new_chromosome);
			else
				delete new_chromosome;
		}
	}

	return vec_new_chrom;
}

Chromosome * Project::chrom_cross(Chromosome *c1,Chromosome *c2)
{
	Chromosome *chr1,*chr2;
		chr1 = c1;
		chr2 = c2;

	Chromosome * new_chromosome1 = new Chromosome(c);
	Chromosome * new_chromosome2 = new Chromosome(c);

	vector<int> selected1,selected2;
	int p1=3;   //[0,1]随机数
	int p2=7;

	selected2.assign(chr1->chrom.begin()+p1,chr1->chrom.begin()+p2);
	selected1.assign(chr2->chrom.begin()+p1,chr2->chrom.begin()+p2);

	
	vector<int> temp,temp2,temp3,temp4;
	vector<int>::iterator ita,itb,it1,it2;
	for(it1=chr1->chrom.begin(),it2=chr2->chrom.begin();it1!=chr1->chrom.begin()+p1,it2!=chr2->chrom.begin()+p1;it1++,it2++)
	{
		if(eleInclude(selected1,*it1))
			temp.push_back(find(selected2,selected1,*it1));
		else
			temp.push_back(*it1);
		if(eleInclude(selected2,*it2))

			temp2.push_back(find(selected1,selected2,*it2));
	
		else
			temp2.push_back(*it2);
	}

	selected1.insert(selected1.begin(),temp.begin(),temp.end());
	selected2.insert(selected2.begin(),temp2.begin(),temp2.end());
		
	for(it1=chr1->chrom.begin()+p2,it2=chr2->chrom.begin()+p2;it1!=chr1->chrom.end(),it2!=chr2->chrom.end();it1++,it2++)
	{
		if(eleInclude(selected1,*it1))

			temp3.push_back(find(selected2,selected1,*it1));
	
		else
			temp3.push_back(*it1);
		
		if(eleInclude(selected2,*it2))

			temp4.push_back(find(selected1,selected2,*it2));
	
		else
			temp4.push_back(*it2);
	}
	selected1.insert(selected1.end(),temp3.begin(),temp3.end());
	selected2.insert(selected2.end(),temp4.begin(),temp4.end());

	new_chromosome1->chrom = selected1;
	new_chromosome2->chrom = selected2;

	new_chromosome2->fitness=compute_tt(new_chromosome2);
	new_chromosome1->fitness=compute_tt(new_chromosome1);

	if(new_chromosome1->fitness<=new_chromosome2->fitness)
	{
		return new_chromosome1;delete new_chromosome2;
	}
	else
	{
		return new_chromosome2;delete new_chromosome1;
	}
	
}

vector<Chromosome*> Project::mutation(Population *pop)
{
	vector<Chromosome*> vec_new_chrom;
	vector<Chromosome*>::iterator it;
	for(it=pop->vec_chrom.begin();it!=pop->vec_chrom.end();it++)
	{
		if(pmutation>(double)rand()/RAND_MAX)
		{
			Chromosome * muta_chr = muta(*it);
			if(muta_chr->fitness <= pop->ave_fitness)
				vec_new_chrom.push_back(muta_chr);
			else
				delete muta_chr;
		//	vec_new_chrom.push_back(muta_chr);
		}
	}

	return vec_new_chrom;
}

Chromosome * Project::muta(Chromosome *chr)
{
	Chromosome *new_chr = new Chromosome(c);

	new_chr->chrom = chr->chrom;
	int p1=rand()%m;
	int p2=0;
	do {p2=rand()%m;}
	while(p1==p2);
	swap(new_chr->chrom[p1],new_chr->chrom[p2]);

	new_chr->fitness = compute_tt(new_chr);

	return new_chr;
}


Population * Project::selection(Population *pop)
{
	Population *new_pop = new Population;

	vector<Chromosome*>::iterator it;
	int size = pop->vec_chrom.size();
	double * lunpan = new double[size];

	int max_fitness=0;
	for(it=pop->vec_chrom.begin();it!=pop->vec_chrom.end();it++)
	{
		if((*it)->fitness > max_fitness)
			max_fitness = (*it)->fitness;
	}

	double sum_fitness=0;
	for(it=pop->vec_chrom.begin();it!=pop->vec_chrom.end();it++)
		sum_fitness += (0.1+max_fitness - (*it)->fitness);
	
	int j=0;
	for(it=pop->vec_chrom.begin();it!=pop->vec_chrom.end();it++,j++)
	{
		lunpan[j] = (0.1+max_fitness - (*it)->fitness) / sum_fitness;
		if(j>0)
			lunpan[j] += lunpan[j-1]; //lunpan累加比例
	}

	vector<int> selected_index,unselected_index,index;
	vector<int>::iterator itI;

	INSERT_ELEMENTS(index,0,size-1);
	while(selected_index.size() < popsize)
	{
		double r=(double)rand()/RAND_MAX;
		int j;
		for(j=0;j<size;j++)
		{
			if(r<lunpan[j])  //产生被选中的编号
			{
				if(!eleInclude(selected_index,j))
				{
					selected_index.push_back(j);
					
					new_pop->vec_chrom.push_back( (pop->vec_chrom[j]));
				}
				break;
			}
		}				
	}

	unselected_index = setDifference(index,selected_index);
	for(itI=unselected_index.begin();itI!=unselected_index.end();itI++)
		delete pop->vec_chrom[*itI];

	new_pop->compute_sum_ave_min_fitness();

	delete []lunpan;

	return new_pop;
}




//////////////////////////////////////////////////////////////////
void Project::Generic1()
{
	Population *pop=new Population;

	Initialpop(pop);	
	pop->output();
	//Generic_tt1 = pop->min_fitness;
	for(int gen=2;gen<=MaxGen;gen++)
	{
		vector<Chromosome*> cross_vec_chrom = crossover(pop);//交叉
		vector<Chromosome*> muta_vec_chrom = mutation(pop);//变异
		vector<Chromosome*>::iterator it;
		for(it=cross_vec_chrom.begin();it!=cross_vec_chrom.end();it++)
			pop->vec_chrom.push_back(*it);
		for(it=muta_vec_chrom.begin();it!=muta_vec_chrom.end();it++)
			pop->vec_chrom.push_back(*it);

		if((pop->vec_chrom.size())>popsize)
			pop = selection(pop);
		pop->generation=gen;
		pop->output();
		if(pop->min_fitness < Generic_tt1)
			Generic_tt1 = pop->min_fitness;

		double diff=0;
		for(int k=0;k<popsize;k++)
			diff += pow(pop->vec_chrom[k]->fitness - pop->ave_fitness, 2);
		double deviation = sqrt(diff/popsize);
		if(deviation<=epinong)
			break;
	}
	delete pop;
}