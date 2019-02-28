#ifndef NORMAL_H
#define NORMAL_H
#include <iostream>
#include <vector>
#include <cmath>
#include<ctime>
#include<stdlib.h>
#include <unistd.h>

using namespace std;

class normal
{
public:
    normal();
    int fb(vector<vector<char> > a, int put);
    vector<int> scorec(const vector<vector<char> > a, char player);
    vector<vector<char> >futureb(const vector<vector<char> > a, int put, char player);
    int returnnumber(vector<vector<char> > b, vector<int> a, int size);
    int returnnumber2(vector<int> a, int size);
    int normal_ai(const vector < vector<char> > &, char, char);
};

#endif // NORMAL_H
