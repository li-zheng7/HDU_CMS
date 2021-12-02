#pragma once
#include <vector>
using namespace std;
int FindPosition(vector<int> vec,int val);
void INSERT_ELEMENTS(vector<int> &V,int s,int e);
vector<int> setDifference(vector<int> E, vector<int> F);
bool include(vector<int> E, vector<int> F);
bool eleInclude(vector<int> E, int i);
vector<int> setSubtract(vector<int> E,int i);
int find(vector<int> X,vector<int> Y,int e);