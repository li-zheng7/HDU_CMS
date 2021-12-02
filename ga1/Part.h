#pragma once
#include<vector>
#include "Job.h"

class Part
{
public:
	int m;
	Job *pa;
	int k;
	float f(int a,int b);
	Part(int m,int k);
	~Part(void);
};
