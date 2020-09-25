
#include <vector>
#include <iostream>

#ifndef MYUTILS_H
#define MYUTILS_H


using namespace std;

void printEntryLine(vector <string> a);
void genericDisplay(vector <float> &data,time_t start);
string evaluateTendency(float tendency);
//template <class T> T computePercentage(T a,T b);
float computePercentage(float a,float b);

#endif