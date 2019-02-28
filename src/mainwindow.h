#ifndef WINDOW_H
#define WINDOW_H

#include <QPainter>
#include <QFrame>
#include <QLabel>
#include <QString>
#include <QBitmap>
#include <QApplication>
#include <ctime>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFrame>
#include <unistd.h>
#include "error.h"
#include "over.h"
#include "connect.h"
#include "pushobject.h"
#include "beginpage.h"
#include "test.h"
#include "easy.h"
#include "normal.h"
#include "hard.h"
#include "resultpage.h"
#define G 0.08
#define TOTAL 42

enum difficult{None,Easy,Normal,Hard};

typedef struct{
int x;
int y;
}posRecord;


class window : public QWidget
{
    Q_OBJECT
public:
    window(QWidget *parent=nullptr);
    pushObject *pc;
    bool isFull(int);
    bool isWin(char [6][7],bool);
    void paint();
    void setboard_();
    QPixmap setImageRound(QPixmap &,int);
    over *oframe;

public slots:
    void start();
    void put();
    void aiPut();
    void undoPut();
    void play();
    void reset();
    void noai();
    void connectEasy();
    void connectNormal();
    void connectHard();
    void col1Clicked();
    void col2Clicked();
    void col3Clicked();
    void col4Clicked();
    void col5Clicked();
    void col6Clicked();
    void col7Clicked();
    void undoClicked();
    //void countTime();
    void toEnd();
    void toCloseApp();
    void backToMenu();


signals :
    void closeBeginPage();
    void toClose();
    void toMenu();
    void set();
    void undoSet();
    void undoAgain();
    void setTime();
    void next();
    void aiThinking();
    void aiFirst();



private:

    QMediaPlaylist *bgmlist;
    QMediaPlayer *down,*floor,*bgm;
    QPixmap d1,d2,cline,bg,p;
    QLabel *player,*d[6][7],*playerImage,*background,*scorel,
           *plate,*countDown,*connectLine,*totalLabel;
    QFrame *scoref;
    QString player_text,time_text,total_text,score_text;
    vector < vector<char> > board_;

    resultpage *re;
    beginPage *beg;
    connect_line *cl;
    test *tframe;
    error *eframe;
    easy E;
    normal N;
    hard H;
    posRecord connect_four[4];
    difficult diff;//enum

    const char disk[3]={'O','X','\0'};
    char board[6][7];
    bool start_clicked,first,conti,disk_color,disk_color_record,pause,full,ai,column_clicked,draw;
    int board_i[7],diskxpos[7],diskypos[6],player_score[2],col_record[TOTAL];
    int n=80,colWidth=70,high=65,undo_num,get,temp_c,total_disk,p1score,p2score,aiscore,yourscore;
    //int hold_time=0;
    //int hold_time_temp;

};

#endif //WINDOW_H


