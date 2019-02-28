//
//  AI.h
//  HW11_E64056122
//
//  Created by 郭家良 on 2019/1/6.
//  Copyright © 2019 郭家良. All rights reserved.
//

#ifndef e64056122_h
#define e64056122_h
#include <vector>
#include <cmath>
#include <QtGlobal>
using namespace std;

#define MAXCOL 7
#define MAXROW 6
#define MAXRE 3

int E64056122(const vector < vector<char> > &, char, char);


class E64056122_helper{
public:
    int Re(int);
    int Case(vector < vector<char> >,char,char);
    int Total(vector < vector<char> >);
    bool JustMid(vector < vector<char> >);
    void NextMove(vector < vector<char> >,int,int,char,char,bool,const int);//decide next move by recursive call
    bool NextWin(vector < vector<char> >,char);//opponent will win after this move
    vector < vector<char> > Move(vector < vector<char> >, int, char);//next state
    bool IsSymmetry(vector < vector<char> >);
    vector < vector<char> > MakeSymmetry(vector < vector<char> >);
    bool IsEmpty(const vector < vector<char> >);//map has nothing
    bool IsFull(vector < vector<char> > map);//map was full
    bool LegalMove(vector < vector<char> >, int);//move was legal
    bool IsWin(vector < vector<char> >, char);//check whether the dishes connect four
    bool JustOne(vector < vector<char> >, char,char);//there is only one opponent's disk on the map
    int JustOneMove(vector < vector<char> >,int,char);//if(justone(map,op)) decide what col is next step

    double mywin=0,yourwin=0;
};
void Output(vector < vector<char> > b4) ;

int E64056122(const vector < vector<char> > &b, char mydisc, char yourdisc)
{
    E64056122_helper N;
    char me = mydisc;
    char opponent = yourdisc;
    int column=0,oddoreven,case_;
    double temp,max_temp=-30001;
    qsrand(1);

    case_=N.Case(b,me,opponent);
    //getchar();

    if(N.IsEmpty(b))//me to begin new game
        return 3;//middle
    else if(case_>=0){
        return case_;
    }
    else
    {
        oddoreven=N.Total(b);
        if(oddoreven<=5&&(N.JustMid(b)||oddoreven<3))
            return 3;
        else
            if(!N.LegalMove(b,3)&&oddoreven==7){
                if(b[5][2]!='\0'){
                    return 1;
                }
                else if(b[5][4]!='\0')
                    return 5;
            }
            else
                if(!N.LegalMove(b,3)&&oddoreven==6){
                    return 2+2*(qrand()%2);
                }
                else
                    for(int i=0;i<MAXCOL;++i)
                    {
                        ////////////////////
                        N.NextMove(b,i,N.Re(oddoreven),me,opponent,true,oddoreven);
                        ////////////////////
                        temp=N.mywin-N.yourwin;//count the probability to win of every col
                        if(N.mywin==0&&N.yourwin==0)// draw
                            temp=-2;
                        if(temp==1&&oddoreven<10) //default front
                            temp=0;
                        else if(temp==1&&oddoreven<20){
                            //N.yourwin=5;
                            temp=N.mywin-N.yourwin;
                        }

                        if(oddoreven<=8&&!N.NextWin(b,opponent)&&(i==0||i==6)) //define begin
                            temp=-5000;
                        //if(oddoreven<=7&&i==3)
                        // temp+=1000;
                        if(temp>max_temp)
                        {
                            max_temp=temp;
                            column=i;//let the biggest probability to win of col be decided
                        }
                    }
        return column;
    }

}

int E64056122_helper::Re(int n)
{
    if(n<20)
        return 3;
    if(n<28)
        return 4;
    return 7;
}

bool E64056122_helper::IsEmpty(const vector < vector<char> > map)
{
    for(int i=0;i<MAXROW;++i)
        for(int j=0;j<MAXCOL;++j)
            if(map[i][j]!='\0')
                return false;
    return true;
}

bool E64056122_helper::IsFull(vector < vector<char> > map)
{
    for (int j = 0; j < 7; j++) {
        if (map[0][j] == '\0') {
            return 0;
        }
    }
    return 1;
}

bool E64056122_helper::IsSymmetry(vector < vector<char> > map)
{
    for(int i=0;i<MAXROW;++i)
        for(int j=0;j<3;++j)
            if(map[i][j]!=map[i][MAXCOL-1-j])
                return false;
    return true;
}

bool E64056122_helper::JustMid(vector < vector<char> > map)
{
    for(int i=0;i<MAXCOL;++i)
        if(i!=3&&map[5][i]!='\0')
            return false;
    return true;
}

bool E64056122_helper::LegalMove(vector < vector<char> > map, int c1) {
    if (map[0][c1] == '\0')
        return true;
    else
        return false;
}

bool E64056122_helper::JustOne(vector < vector<char> > map, char my,char your)
{
    int count_c2=0;
    for(int j=0;j<MAXROW;++j)
    {
        for(int k=0;k<MAXCOL;++k)
        {
            if(map[j][k]==your)
                ++count_c2;
            else if(map[j][k]==my){
                return false;
            }

            if(count_c2>1){
                return false;
            }
        }
    }
    if(count_c2==1)
        return true;
    return false;
}

int E64056122_helper::JustOneMove(vector < vector<char> > map,int i,char your)
{
    for(int k=0;k<MAXCOL;++k){
        if(map[MAXROW-1][k]==your){
            if((i-k<-2)||(i-k>2)||(k<2&&i<k)||(k>(MAXCOL-2)&&i>k))
                return -1;
            return i;
        }
    }
    return -1;//move=-1
}

void E64056122_helper::NextMove(vector < vector<char> > map,int i,int n,char my,char your,bool first,const int oddoreven)
{
    vector < vector<char> > temp1,temp2;
    int tempmy=0,tempyour=0;
    if(first)
    {
        first=false;
        mywin=0;//my
        yourwin=0;//your

        if(LegalMove(map,i))
            map=Move(map,i,my);
        else{
            mywin=-30000;
            yourwin=0;
            return ;
        }

        if(NextWin(map,my)){
            mywin=-10;
            yourwin=0;
        }
        if(IsSymmetry(map)){
            mywin=2000;
            yourwin=0;
            return ;
        }
        else
            if(IsWin(map,my)){
                mywin=10000;
                yourwin=0;
                return;
            }
            else
                if(NextWin(map,your)){
                    mywin=-20000;
                    yourwin=0;
                    return;
                }
    }
    temp1=map;
    temp2=map;
    //not first
    if(n==1)
    {


        for(int k=0;k<MAXCOL;++k)
        {

            if(LegalMove(map,k))
            {
                temp1=map;
                temp1=Move(temp1,k,your);
                if(!oddoreven%2&&IsFull(temp1)) return;//我先手
                if(NextWin(temp1,my)){
                    //mywin=mywin+pow(C,n);
                    ++tempyour;
                    continue;
                }
                else if(oddoreven%2){
                    for(int j=0;j<MAXCOL;++j){
                        if(LegalMove(map,j)){
                            temp2=temp1;
                            temp2=Move(temp2,j,my);
                            if(IsFull(temp2)) return;//他先手
                            if(NextWin(temp2,your)){
                                ++tempmy;
                                continue;
                            }
                        }
                        else
                            ++tempmy;
                    }
                    if(tempmy==7){
                        yourwin=yourwin+n;//我無子可下
                        if(yourwin>1800)
                            return;
                        return;
                    }
                    tempmy=0;
                }
            }
            else
                ++tempyour;
        }
        if(tempyour==7){
            mywin=mywin+n+1;//他無子無子可下
            if(mywin>1800)
                return;
            return;
        }

    }
    else
    {
        if(NextWin(temp1,your)){
            yourwin=yourwin+n+1;
            return;
        }
        else{
            for(int k=0;k<MAXCOL;++k)
            {

                if(LegalMove(map,k))
                {
                    temp1=map;
                    temp1=Move(temp1,k,your);
                    if(!oddoreven%2&&IsFull(temp1)) return;//我先手
                    if(NextWin(temp1,my)){
                        //mywin=mywin+pow(C,n);
                        ++tempyour;
                        continue;
                    }
                    else{
                        for(int j=0;j<MAXCOL;++j){
                            if(LegalMove(map,j)){
                                temp2=temp1;
                                temp2=Move(temp2,j,my);
                                if(oddoreven%2&&IsFull(temp2)) return;//他先手
                                //if(IsWin(temp2,my))
                                // mywin=mywin+pow(C,n);
                                if(NextWin(temp2,your)){
                                    ++tempmy;
                                    continue;
                                }
                                else{
                                    NextMove(temp2,i,n-1,my,your,first,oddoreven);
                                }
                            }
                            else
                                ++tempmy;
                        }
                        if(tempmy==7){
                            yourwin=yourwin+n;//我無子可下
                            if(yourwin>1800)
                                return;
                            return;
                        }
                        tempmy=0;
                    }
                }
                else
                    ++tempyour;
            }

            if(tempyour==7){
                mywin=mywin+n+1;//他無子無子可下
                if(mywin>1800)
                    return;
                return;
            }
        }
    }
}

vector < vector<char> > E64056122_helper::Move(vector < vector<char> > map, int col, char c)
{
    bool flag = 0;
    for (int i = 0; i < 5; i++) {
        if (map[i][col] == '\0'&&map[i + 1][col] != '\0') {
            map[i][col] = c;
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        map[5][col] = c;
    }
    return map;
}

bool E64056122_helper::IsWin(vector < vector<char> > map, char c) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (j + 3 < 7) {
                if (map[i][j] == c && map[i][j+1] == c && map[i][j + 2] == c && map[i][j + 3] == c) {
                    return 1;
                }
            }
            if (i + 3 < 6) {
                if (map[i][j] == c && map[i + 1][j] == c && map[i + 2][j] == c && map[i + 3][j] == c) {
                    return 1;
                }
            }
            if ((j + 3 < 7) && (i + 3 < 6)) {
                if (map[i][j] == c && map[i + 1][j + 1] == c && map[i + 2][j + 2] == c && map[i + 3][j + 3] == c) {
                    return 1;
                }
            }
            if ((j - 3 >= 0) && (i + 3 < 6)) {
                if (map[i][j] == c && map[i + 1][j - 1] == c && map[i + 2][j - 2] == c && map[i + 3][j - 3] == c) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool E64056122_helper::NextWin(vector < vector<char> > map,char c)
{
    vector < vector<char> > temp;
    for(int i=0;i<MAXCOL;++i){
        temp=map;
        if(LegalMove(temp,i)){
            temp=Move(temp,i,c);
            if(IsWin(temp,c))
                return true;
        }
    }
    return false;

}

int E64056122_helper::Case(vector < vector<char> > map,char my,char your)
{
    vector < vector<char> > case1(6, vector<char>(7, 0)),case1_s(6, vector<char>(7, 0));
    vector < vector<char> > case2(6, vector<char>(7, 0)),case2_s(6, vector<char>(7, 0));
    vector < vector<char> > case3(6, vector<char>(7, 0)),case3_s(6, vector<char>(7, 0));
    vector < vector<char> > case4(6, vector<char>(7, 0)),case4_s(6, vector<char>(7, 0));
    vector < vector<char> > case5(6, vector<char>(7, 0)),case5_s(6, vector<char>(7, 0));
    vector < vector<char> > case6(6, vector<char>(7, 0)),case6_s(6, vector<char>(7, 0));
    vector < vector<char> > case7(6, vector<char>(7, 0)),case7_s(6, vector<char>(7, 0));
    vector < vector<char> > case8(6, vector<char>(7, 0)),case8_s(6, vector<char>(7, 0));
    vector < vector<char> > case9(6, vector<char>(7, 0)),case9_s(6, vector<char>(7, 0));

    //case1
    case1[0][3]=your;
    case1[1][3]=my;
    case1[2][2]=case1[2][3]=case1[2][4]=your;
    case1[3][2]=case1[3][3]=my;case1[3][0]=case1[3][4]=your;
    case1[4][0]=case1[4][2]=case1[4][4]=case1[4][5]=my;case1[4][3]=your;
    case1[5][0]=case1[5][3]=case1[5][4]=my;case1[5][1]=case1[5][2]=case1[5][5]=your;
    case1_s=MakeSymmetry(case1);
    if(map==case1) return 0;
    if(map==case1_s) return 6;

    //case2
    case2[0][3]=your;
    case2[1][3]=case2[1][4]=my;
    case2[2][3]=your;case2[2][4]=my;
    case2[3][3]=my;case2[3][4]=your;
    case2[4][2]=case2[4][3]=your;case2[4][4]=my;
    case2[5][2]=case2[5][3]=my;case2[5][4]=case2[5][5]=your;
    case2_s=MakeSymmetry(case2);
    if(map==case2) return 5;
    if(map==case2_s) return 1;

    //case3
    case3[0][3]=my;
    case3[1][3]=your;
    case3[2][3]=my;
    case3[3][3]=your;
    case3[4][3]=my;case3[4][5]=your;
    case3[5][1]=case3[5][4]=my;case3[5][2]=case3[5][3]=case3[5][5]=your;
    case3_s=MakeSymmetry(case3);
    if(map==case3) return 5;
    if(map==case3_s) return 1;

    //case4
    case4[0][2]=my;case4[0][3]=case4[0][4]=case4[0][5]=your;
    case4[1][3]=case4[1][4]=my;case4[1][2]=case4[1][5]=your;
    case4[2][3]=your;case4[2][2]=case4[2][4]=case4[2][5]=my;
    case4[3][2]=case4[3][3]=my;case4[3][4]=case4[3][5]=your;
    case4[4][2]=case4[4][3]=your;case4[4][4]=case4[4][5]=my;
    case4[5][2]=case4[5][3]=case4[5][6]=my;case4[5][1]=case4[5][4]=case4[5][5]=your;
    case4_s=MakeSymmetry(case4);
    if(map==case4) return 6;
    if(map==case4_s) return 0;

    //case5
    case5[0][2]=my;case5[0][3]=case5[0][4]=case5[0][5]=your;
    case5[1][3]=case5[1][4]=my;case5[1][2]=case5[1][5]=your;
    case5[2][3]=your;case5[2][2]=case5[2][4]=case5[2][5]=my;
    case5[3][2]=case5[3][3]=my;case5[3][4]=case5[3][5]=case5[3][6]=your;
    case5[4][2]=case5[4][3]=your;case5[4][4]=case5[4][5]=case5[4][6]=my;
    case5[5][2]=case5[5][3]=case5[5][6]=my;case5[5][1]=case5[5][4]=case5[5][5]=your;
    case5_s=MakeSymmetry(case5);
    if(map==case5) return 6;
    if(map==case5_s) return 0;

    //case6
    case6[0][3]=my;
    case6[1][3]=your;
    case6[2][3]=my;
    case6[3][3]=your;case6[3][5]=my;
    case6[4][3]=my;case6[4][4]=case6[4][5]=your;
    case6[5][1]=case6[5][4]=my;case6[5][2]=case6[5][3]=case6[5][5]=your;
    case6_s=MakeSymmetry(case6);
    if(map==case6) return 1;
    if(map==case6_s) return 5;

    //case7
    case7[0][3]=my;
    case7[1][3]=case7[1][5]=your;
    case7[2][3]=case7[2][5]=my;
    case7[3][3]=your;case7[3][5]=my;
    case7[4][3]=my;case7[4][4]=case7[4][5]=your;
    case7[5][1]=case7[5][4]=my;case7[5][2]=case7[5][3]=case7[5][5]=your;
    case7_s=MakeSymmetry(case7);
    if(map==case7) return 2;
    if(map==case7_s) return 4;

    //case8
    case8[0][3]=my;
    case8[1][3]=your;
    case8[2][3]=my;
    case8[3][3]=your;case8[3][5]=my;
    case8[4][1]=case8[4][3]=my;case8[4][2]=case8[4][4]=case8[4][5]=your;
    case8[5][1]=case8[5][4]=my;case8[5][2]=case8[5][3]=case8[5][5]=your;
    case8_s=MakeSymmetry(case8);
    if(map==case8) return 1;
    if(map==case8_s) return 5;

    //case9
    case9[0][3]=my;
    case9[1][3]=your;
    case9[2][3]=my;case9[2][1]=your;
    case9[3][3]=your;case9[3][1]=case9[3][5]=my;
    case9[4][1]=case9[4][3]=my;case9[4][2]=case9[4][4]=case9[4][5]=your;
    case9[5][1]=case9[5][4]=my;case9[5][2]=case9[5][3]=case9[5][5]=your;
    case9_s=MakeSymmetry(case9);
    if(map==case9) return 5;
    if(map==case9_s) return 1;

    return -1;
}

vector < vector<char> > E64056122_helper::MakeSymmetry(vector < vector<char> > map)
{
    vector < vector<char> > s(6, vector<char>(7, 0));
    for(int i=0;i<MAXROW;++i)
        for(int j=0;j<MAXCOL;++j){
            if(map[i][MAXCOL-1-j]!='\0')
                s[i][j]=map[i][MAXCOL-1-j];
        }
    //Output(s);
    return s;
}
int E64056122_helper::Total(vector < vector<char> > map)
{
    int c=0;
    for(int i=0;i<MAXROW;++i)
        for(int j=0;j<MAXROW;++j)
            if(map[i][j]!='\0')
                ++c;
    return c;
}
/*
void Output(vector < vector<char> > b4) {
    cout << "      0 1 2 3 4 5 6" << endl;
    cout << "     ===============" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "  " << i << "  |";
        for (int j = 0; j < 7; j++) {
            if(b4[i][j])
                cout << b4[i][j] << "|";
            else
                cout << " |";
        }
        cout << endl;
    }
    cout << "     ===============" << endl;
}
*/
#endif /* e64056122_h */
