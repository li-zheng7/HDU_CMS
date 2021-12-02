#pragma once
#include<vector>
using namespace std;
class Job
{
public:
	int dq;
	vector<int> v;
	vector<int> predecessor;
	Job(void);
	~Job(void);
};
