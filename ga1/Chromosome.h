#pragma once
#include<vector>
using namespace std;
#include "Job.h"
#include "Part.h"
#include "Globals.h"
class Chromosome
{
public:
	int m;
	int c;
	int k;
	float fitness;
	void pini(int k);
	
	void display();
	Part *pp;
	vector <int> chrom;
	vector <int> *sub_chrom;
	Chromosome(int c);
	Chromosome(int m,int c);
	~Chromosome(void);
};
