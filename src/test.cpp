#include "test.h"

test::test(QWidget *parent):QWidget(parent)
{

    s=new QFrame(this);
    l=new QLabel(this);
    l->setGeometry(30,30,240,240);
    l->setFont(QFont("Courier",12));
    resize(300,300);
}
void test::set(vector<vector<char>> c)
{
    text=new QString;
    for(int i=0;i<6;i++){
        *text+=QString::number(i);
        *text+=" :|";
        for(int j=0;j<7;j++){
            if(c[i][j]=='\0'){
                *text+=".|";
            }
            else{
                *text+=c[i][j];
                *text+='|';
            }
        }
        *text+='\n';
    }
    l->setText(*text);
    free(text);
}
