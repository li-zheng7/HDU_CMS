#pragma once
#include "Chromosome.h"
class Population
{
public:
	int generation;//当前世代数
	float ave_fitness;
	float sum_fitness,min_fitness,max_fitness;
	vector<Chromosome*> vec_chrom;//染色体集合
	void output();
	void compute_sum_ave_min_fitness();
	Population(void);
	~Population(void);
};
