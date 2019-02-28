#ifndef EASY_H
#define EASY_H
#include <iostream>

#include<vector>

#include<iomanip>

#include <QDebug>

#include <unistd.h>

#define ai_row  6

#define ai_col  7

#define disc_tot 42

using namespace std;



class easy
{
public:
    easy();
    int easy_ai(const vector < vector<char> > &, char, char);

private:
    int depth=1;
    void display(vector<vector<int> > board);
    bool drawj(vector<vector<int> > board);
    int deptrans(int dep);
    float value(vector<vector<int> > board);
    float value1(vector<vector<int> > board);
    void findposmove(vector<vector<int> > board, int* simboard1);
    void setorback(vector<vector<int> > &board, int dep, int *simboard, int choice);
    float dfsuntil(vector<vector<int> > board, int dep);
    int ai(vector<vector<char> > board, char mydisc, char oppdisc);

};

#endif // EASY_H
