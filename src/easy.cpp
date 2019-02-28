#include "easy.h"

easy::easy()
{

}



void easy::display(vector<vector<int> > board) {

    for (int i = 0; i < ai_col; i++) {

        //cout << setw(2) << i + 1;

    }

    //cout << endl;

    for (int i = 0; i < ai_row; i++) {

        for (int j = 0; j < ai_col; j++) {

            //cout << setw(2) << board[i][j];

        }

        //cout << endl;

    }

}

bool easy::drawj(vector<vector<int> > board) {

    int disc_left = 0;

    for (int i = 0; i < ai_col; i++) {

        if (board[0][i] == 0) {//∫‚¨Oß_∫°

            disc_left++;

        }

    }

    if (disc_left)return false;

    return true;

}

int easy::deptrans(int dep) {

    int disc=1;

    if (dep != depth) {

        if (depth % 2) {

            if (dep % 2 == 0 ) {

                disc = -1;

            }

        }

        else {

            if (dep % 2 !=0) {

                disc = -1;

            }

        }



    }

    //cout << "deptrans dep=" << dep << " deptrans disc= " << disc;

    return disc;

}

float easy::value(vector<vector<int> > board) {

    int disc = 1;

    for (int x = 0; x < 2; x++) {

        for (int i = 0; i < 6; i++) {

            for (int j = 0; j < 7; j++) {

                if (j + 3 < 7) {

                    if (board[i][j] == disc && board[i][j + 1] == disc && board[i][j + 2] == disc && board[i][j + 3] == disc) {

                        return 1*disc;

                    }

                }

                if (i + 3 < 6) {

                    if (board[i][j] == disc && board[i + 1][j] == disc && board[i + 2][j] == disc && board[i + 3][j] == disc) {

                        return 1 * disc;

                    }

                }

                if ((j + 3 < 7) && (i + 3 < 6)) {

                    if (board[i][j] == disc && board[i + 1][j + 1] == disc && board[i + 2][j + 2] == disc && board[i + 3][j + 3] == disc) {

                        return 1 * disc;

                    }

                }

                if ((j - 3 >= 0) && (i + 3 < 6)) {

                    if (board[i][j] == disc && board[i + 1][j - 1] == disc && board[i + 2][j - 2] == disc && board[i + 3][j - 3] == disc) {

                        return 1 * disc;

                    }

                }

            }

        }

        disc = -1;

    }

    return 0;

}

float easy::value1(vector<vector<int> > board) {

    int total = 0; int mydisc = 1, oppdisc = -1,winj= value(board);

    //cout << "\n!!!!!!!!!!!" << endl;

    //display(board);

    //cout << endl;

    if (drawj(board))return 0.5;//•≠§‚

    if ( winj< 0) {

        total -=1000;

        return total;

    }

    else if (winj > 0) {

        total += 2000;

        return total;

    }

    int count = 0, Decount = 0;

    for (int i = 0; i < ai_row; i++) {//º˙¿y©Ò§§Ωu

        if (board[i][3] == mydisc) {

            total += 10;

        }

    }

    for (int i = 0; i < ai_row; i++) {//attack ßP¬_≥sΩu§@¶∏®˙•|§l

        for (int j = 0; j < ai_col; j++) {

            if (j + 3 < ai_col) {//æÓ¶VßP¬_

                count = 0; Decount = 0;

                for (int x = 0; x < 4; x++) {

                    if (board[i][j + x] == mydisc) {

                        count++;

                    }

                    if (board[i][j + x] == oppdisc) {

                        count = 0;

                        x = 4;

                    }

                }

                for (int x = 0; x < 4; x++) {

                    if (board[i][j + x] == oppdisc) {

                        Decount++;

                    }

                    if (board[i][j + x] == mydisc) {

                        Decount = 0;

                        x = 4;

                    }

                }

                if (count == 2) {//¶≥®‚§l

                    total += 2;

                }

                else if (count == 3) {//¶≥§T§l

                    total += 5;

                }

                if (Decount == 2) {

                    total -= 3;

                }

                else if (Decount == 3) {

                    total -= 100;

                }

            }

            if (i + 3 < ai_row) {//™Ω¶VßP¬_

                count = 0; Decount=0;

                for (int x = 0; x < 4; x++) {

                    if (board[i+x][j] == mydisc) {

                        count++;

                    }

                    if (board[i+x][j] == oppdisc) {

                        count = 0;

                        x = 4;

                    }

                }

                for (int x = 0; x < 4; x++) {

                    if (board[i+x][j] == oppdisc) {

                        Decount++;

                    }

                    if (board[i+x][j] == mydisc) {

                        Decount = 0;

                        x = 4;

                    }

                }

                if (count == 2) {//¶≥®‚§l

                    total += 2;

                }

                else if (count == 3) {//¶≥§T§l

                    total += 5;

                }

                if (Decount == 2) {

                    total -= 3;

                }

                else if (Decount == 3) {

                    total -= 100;

                }

            }

            if ((j + 3 < ai_col) && (i + 3 < ai_row)) {//•™§U•k§WßP¬_

                count = 0; Decount = 0;

                for (int x = 0; x < 4; x++) {

                    if (board[i + x][j + x] == mydisc) {

                        count++;

                    }

                    if (board[i + x][j + x] == oppdisc) {

                        count = 0;

                        x = 4;

                    }

                }

                for (int x = 0; x < 4; x++) {

                    if (board[i+x][j + x] == oppdisc) {

                        Decount++;

                    }

                    if (board[i+x][j + x] == mydisc) {

                        Decount = 0;

                        x = 4;

                    }

                }

                if (count == 2) {//¶≥®‚§l

                    total += 2;

                }

                else if (count == 3) {//¶≥§T§l

                    total += 5;

                }

                if (Decount == 2) {

                    total -= 3;

                }

                else if (Decount == 3) {

                    total -= 100;

                }

            }

            if ((j - 3 >= 0) && (i + 3 < ai_row)) {//•k§W•™§U

                count = 0; Decount = 0;

                for (int x = 0; x < 4; x++) {

                    if (board[i + x][j - x] == mydisc) {

                        count++;

                    }

                    if (board[i + x][j - x] == oppdisc) {//®æ¶ußP¬_

                        count = 0;

                        x = 4;

                    }

                }

                for (int x = 0; x < 4; x++) {

                    if (board[i+x][j - x] == oppdisc) {

                        Decount++;

                    }

                    if (board[i+x][j - x] == mydisc) {

                        Decount = 0;

                        x = 4;

                    }

                }

                if (count == 2) {//¶≥®‚§l

                    total += 2;

                }

                else if (count == 3) {//¶≥§T§l

                    total += 5;

                }

                if (Decount == 2) {

                    total -= 3;

                }

                else if (Decount == 3) {

                    total -= 100;

                }

            }

        }

    }

    //cout << "\ntotal= " << total<<endl;

    //system("pause");

    return total;



}

void easy::findposmove(vector<vector<int> > board, int* simboard1) {

    for (int i = 0; i < ai_col; i++) {

        simboard1[i] = -1;//•Ù∞»ƒÊ™Ï©l

        for (int j = ai_row - 1; j >= 0; j--) {

            if (board[j][i] == 0) {

                simboard1[i] = j;

                j = -1;

            }

        }

    }

}

void easy::setorback(vector<vector<int> > &board, int dep, int *simboard, int choice) {//-1 set 0 back

    int disc;

    //cout << "set start";

    disc = deptrans(dep);//©Ò∏m™©≠±•Œ

    //cout << "disc put!!!!!" << disc;

    if (choice == -1) {

        for (int i = 0; i < ai_col; i++) {

            if (simboard[i] >= 0) {

                board[simboard[i]][i] = disc;

                simboard[i] = -1;

                i = ai_col;

            }

        }

    }

    else {

        for (int i = 0; i < ai_row; i++) {

            if (board[i][choice] != 0) {

                board[i][choice] = 0;

                i = ai_row;

            }

        }

    }

    //display(board);

    //system("pause");

}

float easy::dfsuntil(vector<vector<int> > board, int dep) {

    //cout << "\ndisplay dep=" << dep << endl;

    float val = value1(board); int move = 0; float bestS = 0;

    //display(board);

    //cout << val << endl;

    //system("pause");

    if (dep < 0 || val>150 ||val<(-950)||val==0.5) {

        return val;

    }

    if ((depth-(dep+1)) % 2) {

        bestS = -10000;

    }

    else {

        bestS = 10000;

    }

    float buf=0; int simboard1[ai_col];

    findposmove(board, simboard1);

    //cout << "posmove !!!!!!!!" << simboard1[0];

    for (int i = 0; i < ai_col; i++) {

        if (simboard1[i] >= 0) {

            //cout << "!!sim/i" << simboard1[i] << " " << i << endl;;

            setorback(board, dep, simboard1, -1);

            buf = dfsuntil(board, dep-1);

            if (depth==dep) {

                //cout<<" " << i<< ":" << buf;

            }

            if ((depth-(dep+1)) % 2) {

                if (bestS < buf) {

                    bestS = buf;

                    if(dep==depth){

                        move = i;

                    }

                }

            }

            else {

                if (bestS > buf) {

                    bestS = buf;

                }

            }

            setorback(board, dep, simboard1, i);

        }

    }

    if (dep == depth) {

        //cout << "re move";

        //system("pause");

        return move;

    }

    else{

        //cout << "return bestS "<<bestS<<endl;

        return bestS;

    }



}

/*int fmpreboard(vector<vector<int> > board) {//•˝§‚µPÆw



 }

 int smpreboard(vector<vector<int> > board) {//´·§‚µPÆw



 }*/

int easy::ai(vector<vector<char> > board, char mydisc, char oppdisc) {

    int move = 0, count = 0;

    vector < vector<int> > aiboard(ai_row, vector<int>(ai_col, 0));

    for (int i = 0; i < ai_col; i++) {

        for (int j = 0; j < ai_row; j++) {//º∆¶r§∆

            if (board[j][i] == mydisc) {

                aiboard[j][i] = 1;

                count++;

            }

            if (board[j][i] == oppdisc) {

                aiboard[j][i] = -1;

                count++;

            }

        }

    }

    /*display(aiboard);

     cout << endl;

     for (int i = 0; i < ai_col; i++) {

     for (int j = ai_row-1; j >=0; j--) {

     if (aiboard[j][i] == 0) {

     simboard1[i] = j;

     j = -1;

     }

     }

     }

     for (int i = 0; i < ai_col; i++) {

     if (simboard1[i] >= 0) {

     aiboard[simboard1[i]][i] = 1;

     }

     if (value(aiboard) > 0) {

     move = i;

     i = ai_col;

     }

     else {

     aiboard[simboard1[i]][i] = 0;

     }

     }

     display(aiboard);*/



    //cout << "•ÿ´e®Bº∆= " << count << " •ÿ´e≤`´◊= " << depth << endl;

    move = dfsuntil(aiboard, depth);

    return move;

}





int easy::easy_ai(const vector < vector<char> > &b, char mydisc, char yourdisc) {

    int column = 0;int choice=0;
    //text=new QString;


    //Write a simple AI for testing

    //movejudge++;

    //cout << "movejudge= " << movejudge << endl;

    //system("pause");

    //cout<<"≠n¨›£v?";

    //cin>>choice;

    //cout<<"HI Mk-II ";

    if(choice){

        cin >> column;

    }


    else{

        column = ai(b, mydisc, yourdisc);

    }
    sleep(1);

    //cout<<endl<<"ß⁄®´§F "<<column << endl;

    //Write a simple AI for testing

    return column;

}


