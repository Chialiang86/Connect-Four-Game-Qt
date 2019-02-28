#include "normal.h"

normal::normal()
{

}
int normal::fb(vector<vector<char> > a, int put)//®C™Ω¶C¥—§l∞™´◊
{
    vector<int> s(7, -1);
    for (int i = 0; i <= 6; i++){//±Ω¥y®C¶Ê¶≥¶h§÷0
        for (int j = 0; j <= 5; j++){
            if (a[j][i] == 0)
                s[i]++;
        }
    }
    return s[put];
}
vector<int> normal::scorec(const vector<vector<char> > a, char player)//ßP¬_®C™Ω¶Ê§¿º∆
{
    int row = 0;
    vector<int> score(7, 0);//¶Ï∏møn§¿
    for (int put = 0; put <= 6; put++){
        row = fb(a, put);
        while (row == -1){
            score[put] = -1000000;
            put++;
            if (put > 6)
                break;
            row = fb(a, put);
        }
        if (put > 6)
            break;
        int flag1 = 1;//æÓ¶V
        for (int i = put + 1; i <= put + 4; i++)
        {
            if (i > 6)
                break;
            else if (a[row][i] != player)
                break;
            if (a[row][i] == player)
                flag1++;
        }
        for (int i = put - 1; i >= put - 4; i--)
        {
            if (i < 0)
                break;
            else if (a[row][i] != player)
                break;
            if (a[row][i] == player)
                flag1++;
        }
        score[put] += pow(13, flag1);

        ///////™Ω±∆
        int flag2 = 1;

        for (int i = row + 1; i <= row + 4; i++)
        {
            if (i > 5)
                break;
            else if (a[i][put] != player)
                break;
            if (a[i][put] == player)
                flag2++;
        }
        for (int i = row - 1; i >= put - 4; i--)
        {
            if (i < 0)
                break;
            else if (a[i][put] != player)
                break;
            if (a[i][put] == player)
                flag2++;
        }
        score[put] += pow(10, flag2);
        ///////±◊Ωu1
        int flag3 = 1;
        int x1 = put;
        for (int b = row + 1; b <= row + 4; b++)
        {
            x1--;
            if (b > 5)
                break;
            if (x1 < 0)
                break;
            else if (a[b][x1] != player)
                break;
            if (a[b][x1] == player)
                flag3++;
        }
        x1 = put;
        for (int b = row - 1; b >= row - 4; b--)
        {
            x1++;
            if (b < 0)
                break;
            if (x1 > 6)
                break;
            else if (a[b][x1] != player)
                break;
            if (a[b][x1] == player)
                flag3++;
        }
        score[put] += pow(10, flag3);
        ///////////////±◊Ωu2
        int flag4 = 1;
        x1 = put;
        for (int b = row - 1; b >= row - 4; b--)
        {
            x1--;
            if (b < 0)
                break;
            if (x1 < 0)
                break;
            else if (a[b][x1] != player)
                break;
            if (a[b][x1] == player)
                flag4++;
        }
        x1 = put;
        for (int b = row + 1; b <= row + 4; b++)
        {
            x1++;
            if (b > 5)
                break;
            if (x1 > 6)
                break;
            else if (a[b][x1] != player)
                break;
            if (a[b][x1] == player)
                flag4++;
        }
        score[put] += pow(10, flag4);
    }

    return score;
}
vector<vector<char> > normal::futureb(const vector<vector<char> > a, int put, char player)//±NπwßP™∫¥—§l©Ò§J
{
    vector<vector<char> >fbtest = a;
    if (fb(a, put) == -1)
        return fbtest;

    else
        fbtest[fb(a, put)][put] = player;

    return fbtest;
}
int normal::returnnumber(vector<vector<char> > b, vector<int> a, int size)
{
    vector<int> equal;
    int flag = a[0];//¿x¶s≠»
    int flagnumber = 0;//¿x¶s¶Ï∏m
    for (int i = 0; i <= size; i++){
        if (a[i] >= flag){
            flag = a[i];
            flagnumber = i;
        }
    }
    for (int i = 0; i <= size; i++){
        if (a[i] == flag){
            equal.push_back(i);
            if (i == 3)
                return 3;
        }
    }

    if (equal.size() != 0){
        int n1 = rand() % equal.size();
        flagnumber = equal[n1];
    }

    int flag2 = 0;//≤ƒ§@®B§U3
    for (int put = 0; put <= 6; put++){
        if (fb(b, put) == 5)
            flag2++;
    }
    if (flag2 == 7)
        return 3;


    return flagnumber;
}
int normal::returnnumber2(vector<int> a, int size)
{
    int flag = a[0];//¿x¶s≠»
    for (int i = 0; i < size; i++){
        if (a[i] <= flag){
            flag = a[i];
        }
    }
    return flag;
}



int normal::normal_ai(const vector < vector<char> > &a, char mydisc, char yourdisc) {
    static const char me = mydisc; //Record the disc type main function assigns for this AI. It never changes once assigned
    static const char opponent = yourdisc; //Record the disc type main function assigns for another AI. It never changes once assigned
    int column = -1;
    //Write a simple AI for testing
    srand(time(NULL));
    vector<int> score(7, 0);//¶Ï∏møn§¿
    vector<int> score2(49, 0);//¶Ï∏møn§¿
    vector<vector<char> >fbtest = a;//∑s™∫¥—ΩL

    ///////≤ƒ§@®B/////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i <= 6; i++){
        score[i] = scorec(a, mydisc)[i] + scorec(a, yourdisc)[i];
        if (scorec(a, yourdisc)[i]>1000)
            score[i] += 3000;
    }
    /////////////////§£≠n•u≥s¶®§T±¯Ωu...///////////////////////////////////////////////////////////////////////
    for (int i = 0; i <= 6; i++){//ßP¬_§U§@®B
        fbtest = a;
        while (fbtest == a){
            fbtest = a;
            fbtest = futureb(a, i, mydisc);
            if (fbtest == a)
                i++;
            if (i > 6)
                break;
        }
        if (i > 6)
            break;
        for (int j = 0; j <= 6; j++){
            score2[i * 7 + j] = scorec(a, mydisc)[j];
            if (score2[i * 7 + j] < 10000 && scorec(a, mydisc)[j]>1000){
                score[i] -= 1000;
            }
        }
    }
    /////////∑Q≥s¶®§T±¯Ωu////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i <= 6; i++){//ßP¬_§U§@®B
    fbtest = a;
    while (fbtest == a){
    fbtest = a;
    fbtest = futureb(a, i, mydisc);
    if (fbtest == a)
    i++;
    if (i > 6)
    break;
    }
    if (i > 6)
    break;
    for (int j = 0; j <= 6; j++){
    score2[i * 7 + j] = scorec(fbtest, mydisc)[j];
    if (score2[i * 7 + j] > 1000 ){
    score[i] -= 100;
    }
    }
    }
    //////////§£≠n≈˝ßO§Hæ◊¶Ì////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i <= 6; i++){//ßP¬_§U§@®B
        fbtest = a;
        while (fbtest == a){
            fbtest = a;
            fbtest = futureb(a, i, mydisc);
            if (fbtest == a)
                i++;
            if (i > 6)
                break;
        }
        if (i > 6)
            break;
        for (int j = 0; j <= 6; j++){
            score2[i * 7 + j] = scorec(fbtest, mydisc)[j];
            if (score2[i * 7 + j] > 10000 && j == i){
                score[i] -= 10000;
            }
        }
    }


    ////////////§£≠n§U≈˝ßO§Hƒπ™∫®B/////////////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i <= 6; i++){//ßP¬_§U§@®B
        fbtest = a;
        while (fbtest == a){
            fbtest = a;
            fbtest = futureb(a, i, mydisc);
            if (fbtest == a)
                i++;
            if (i > 6)
                break;
        }
        if (i > 6)
            break;
        int flag = scorec(fbtest, yourdisc)[0];
        for (int j = 0; j <= 6; j++){
            score2[i * 7 + j] = scorec(fbtest, yourdisc)[j];
            if(score2[i * 7 + j]>flag)
                flag = score2[i * 7 + j];
            if (score2[i * 7 + j] > 10000 &&scorec(a, mydisc)[j]<10000){/////§£¶Ê!∑|∞e¿Y!!
                score[i] -= 20000;
            }
            if (score2[i * 7 + j] > 2000  &&scorec(a, mydisc)[j]<10000){/////§£¶Ê!∑|∞e¿Y!!
                score[i] -= 2000;
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    score[3] += 500;
    /*for (int i = 0; i <= 6; i++){
    cout << i << "  " << score[i] << endl;
    }*/

    column = returnnumber(a, score, 6);
    //cout << column << endl;

    //Write a simple AI for testing

    sleep(1);
    return column;
}

