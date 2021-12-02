#include<iostream>
using namespace std;
#include "Chromosome.h"
#include "Project.h"
#include<ctime>
#include "Part.h"
void main()
{
	srand(time(0)); 

	int m=10;
	int c=3;
	int k=10;
	Project cc(m,c,k);
	cc.Generic1();
}