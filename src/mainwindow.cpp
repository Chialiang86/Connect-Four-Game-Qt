#include "mainwindow.h"

window::window(QWidget *parent): QWidget(parent)
{
    //視窗設定
    setWindowTitle("程設二守衛戰");
    resize(670,540);

    //背景
    background=new QLabel(this);
    bg.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/background.png");
    background->setGeometry(0,0,670,540);
    background->setAlignment(Qt::AlignCenter);
    background->setPixmap(bg.scaled(670,540,Qt::KeepAspectRatioByExpanding));
    background->show();

    //初始頁面
    beg=new beginPage(this);

    //落下聲
    down=new QMediaPlayer(this);
    down->setMedia(QUrl::fromLocalFile("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/down.mp3"));
    down->setVolume(30);

    //碰地聲
    floor=new QMediaPlayer(this);
    floor->setMedia(QUrl::fromLocalFile("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/floor.mp3"));
    floor->setVolume(30);

    //背景音樂
    bgm=new QMediaPlayer(this);
    bgmlist=new QMediaPlaylist(this);
    bgmlist->addMedia(QUrl::fromLocalFile("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/bgm.mp3"));
    bgmlist->setCurrentIndex(1);
    bgmlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm->setPlaylist(bgmlist);
    bgm->setVolume(30);
    bgm->play();

    //遊戲頁按鈕
    pc=new pushObject(this);
    pc->restart->close();
    pc->end->close();
    pc->undo->close();
    pc->mainMenu->close();

    //暫時關閉遊戲頁按鈕
    for(int i=0;i<7;i++)
        pc->column[i]->close();


    scorel=new QLabel(this);//分數標籤
    scoref=new QFrame(this);//分數欄
    plate=new QLabel(this);//棋盤
    player=new QLabel(this);//玩家標籤
    playerImage=new QLabel(this);//棋子標籤
    countDown=new QLabel(this);//落子時間標籤
    totalLabel=new QLabel(this);//剩餘子標籤
    for(int i=0;i<6;i++)
        for(int j=0;j<7;j++)
             d[i][j] = new QLabel(this);//棋盤落子位置標籤

    connect(beg,SIGNAL(pToP()),beg,SLOT(setClose()));//關閉初始頁
    connect(beg,SIGNAL(pToP()),this,SLOT(noai()));//連接雙人對戰
    connect(beg,SIGNAL(setEasy()),beg,SLOT(setClose()));//關閉初始頁
    connect(beg,SIGNAL(setEasy()),this,SLOT(connectEasy()));//連接簡單對戰
    connect(beg,SIGNAL(setNormal()),beg,SLOT(setClose()));//關閉初始頁
    connect(beg,SIGNAL(setNormal()),this,SLOT(connectNormal()));//連接普通對戰
    connect(beg,SIGNAL(setHard()),beg,SLOT(setClose()));//關閉初始頁
    connect(beg,SIGNAL(setHard()),this,SLOT(connectHard()));//連接困難對戰

    connect(this,SIGNAL(set()),this,SLOT(put()));//連接下棋動畫
    connect(this,SIGNAL(undoSet()),this,SLOT(undoPut()));//回到上一步
    connect(this,SIGNAL(next()),this,SLOT(play()));//連接下一步設定
    connect(this,SIGNAL(undoAgain()),this,SLOT(undoClicked()));//連接再次回到上一步
    connect(this,SIGNAL(aiThinking()),this,SLOT(aiPut()));//連接ai程式
    connect(this,SIGNAL(aiFirst()),this,SLOT(aiPut()));//連接ai下子
    //QWidget::connect(this,SIGNAL(setTime()),this,SLOT(countTime()));
    connect(this,SIGNAL(toMenu()),beg,SLOT(back()));//連接回到初始頁

    connect(pc->end,SIGNAL(clicked()),this,SLOT(toCloseApp()));//連接關閉遊戲
    connect(pc->restart,SIGNAL(clicked()),this,SLOT(reset()));//連接重設
    connect(pc->undo,SIGNAL(clicked()),this,SLOT(undoClicked()));//連接上一步設定
    connect(pc->mainMenu,SIGNAL(clicked()),this,SLOT(backToMenu()));//連接回到初始頁
    connect(pc->column[0],SIGNAL(clicked()),this,SLOT(col1Clicked()));//連接落子設定
    connect(pc->column[1],SIGNAL(clicked()),this,SLOT(col2Clicked()));//連接落子設定
    connect(pc->column[2],SIGNAL(clicked()),this,SLOT(col3Clicked()));//連接落子設定
    connect(pc->column[3],SIGNAL(clicked()),this,SLOT(col4Clicked()));//連接落子設定
    connect(pc->column[4],SIGNAL(clicked()),this,SLOT(col5Clicked()));//連接落子設定
    connect(pc->column[5],SIGNAL(clicked()),this,SLOT(col6Clicked()));//連接落子設定
    connect(pc->column[6],SIGNAL(clicked()),this,SLOT(col7Clicked()));//連接落子設定

    tframe=new test(nullptr);//debug

}

void window::start()
{
    p.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/plate.png");
    plate->setGeometry(30,80,490,410);
    plate->setAlignment(Qt::AlignCenter);
    plate->setPixmap(p.scaled(490,410,Qt::KeepAspectRatio));
    plate->show();

    pc->restart->show();
    pc->end->show();
    pc->undo->show();
    pc->mainMenu->show();
    for(int i=0;i<7;i++)
        pc->column[i]->show();
    //bgm->stop();

    QCoreApplication::processEvents();

    //初始紀錄
    for(int i=0;i<TOTAL;i++)
        col_record[i]=-1;

    //初始化ai棋盤
    for(int i=0;i<6;++i){
        vector<char> board_1;
        for(int j=0;j<7;j++){
            board_1.push_back('\0');
        }
        board_.push_back(board_1);
    }

    //初始棋盤
    for(int j=0;j<7;j++)
        for(int i=0;i<6;i++)
            board[i][j]=disk[2];

    //位置參數初始
    for(int i=0;i<6;++i)
        diskypos[i]=422-i*high;
    for(int j=0;j<7;j++)
        diskxpos[j]=33+j*colWidth;

    //每個欄的stack初始
    for(int i=0;i<7;i++)
        board_i[i]=0;

    //初始化四連子記錄參數
    for(int i=0;i<4;i++){
        connect_four[i].x=0;
        connect_four[i].y=0;
    }

    p1score=0;
    p2score=0;
    aiscore=0;
    yourscore=0;
    total_disk=0;
    undo_num=2;
    draw=false;
    start_clicked=false;
    first=true;
    conti=true;
    disk_color=false;
    disk_color_record=false;
    pause=false;
    column_clicked=false;

    score_text="%1%2%3%4";
    if(!ai){
        score_text=score_text.arg("Score(P1:P2)\n\n",QString::number(p1score)," : ",QString::number(p2score));
        scorel->setText(score_text);

        player_text="%1%2%3";
        player_text=player_text.arg("player ",QString::number(disk_color+1),"'s turn");
        player->setText(player_text);
    }
    else{
        score_text=score_text.arg("Score(YOU:AI)\n\n",QString::number(yourscore)," : ",QString::number(aiscore));
        scorel->setText(score_text);

        player->setText("your turn");
    }
    scorel->setGeometry(520,270,150,45);
    scorel->setFont(QFont("Courier",14));
    scorel->setAlignment(Qt::AlignCenter);
    scorel->show();

    player->setGeometry(525,320,140,20);
    player->setFont(QFont("Courier",14));
    player->setAlignment(Qt::AlignCenter);
    player->show();

    //disk 圖案

    d1.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/disk1.png");
    d2.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/disk2.png");
    d1=setImageRound(d1,250);
    d2=setImageRound(d2,250);
    playerImage->setGeometry(545,350,100,100);
    playerImage->setAlignment(Qt::AlignCenter);
    playerImage->setPixmap(d1.scaled(100,100,Qt::KeepAspectRatio));
    playerImage->show();

    total_text="%1%2%3";
    total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
    totalLabel->setText(total_text);
    totalLabel->setGeometry(525,470,140,20);
    totalLabel->setFont(QFont("Courier",14));
    totalLabel->setAlignment(Qt::AlignCenter);
    totalLabel->show();

    this->show();
    emit closeBeginPage();
    QCoreApplication::processEvents();
    //emit setTime();
}

void window::reset()
{

    for(int i=0;i<TOTAL;i++)
        col_record[i]=-1;
    for(int j=0;j<7;j++)
        board_i[j]=0;

    for(int j=0;j<7;j++)
        for(int i=0;i<6;i++)
            board[i][j]=disk[2];

    for(int i=5;i>=0;i--){
        for(int j=0;j<7;j++){
            if(d[i][j]){
                d[i][j]->close();
                QCoreApplication::processEvents();
            }
        }
    }

    if(conti){//有人贏才能對調順序
        disk_color=disk_color_record;
    }
    else{
        disk_color=!disk_color_record;
        disk_color_record=disk_color;
        conti=true;
    }

    for(int i=0;i<4;i++){
        connect_four[i].x=0;
        connect_four[i].y=0;
    }
    undo_num=2;
    total_disk=0;
    draw=false;
    pause=false;

    if(ai){
        if(disk_color_record){
            player->setText("AI's turn");
            player->update();
            playerImage->setPixmap(d2.scaled(100,100,Qt::KeepAspectRatio));
            playerImage->show();
            QCoreApplication::processEvents();
            column_clicked=true;

            emit aiThinking();
        }
        else{
            player->setText("your turn");
            player->update();
            playerImage->setPixmap(d1.scaled(100,100,Qt::KeepAspectRatio));
            playerImage->show();
            QCoreApplication::processEvents();

            column_clicked=false;
            emit setTime();
        }
    }
    else{
        if(disk_color_record){
            player_text="%1%2%3";
            player_text=player_text.arg("player ",QString::number(disk_color+1),"'s turn");
            player->setText(player_text);
            player->update();
            playerImage->setPixmap(d2.scaled(100,100,Qt::KeepAspectRatio));
            playerImage->update();

            column_clicked=false;
            emit setTime();
        }
        else{
            player_text="%1%2%3";
            player_text=player_text.arg("player ",QString::number(disk_color+1),"'s turn");
            player->setText(player_text);
            player->update();
            playerImage->setPixmap(d1.scaled(100,100,Qt::KeepAspectRatio));
            playerImage->update();

            column_clicked=false;
            emit setTime();
        }
    }


}

void window::backToMenu()
{
    if(!pause){
        pc->restart->close();
        pc->end->close();
        pc->undo->close();
        pc->mainMenu->close();
        for(int i=0;i<7;i++){
            pc->column[i]->close();
        }
        scorel->close();
        playerImage->close();
        player->close();
        plate->close();
        totalLabel->close();
        for(int i=5;i>=0;i--){
            for(int j=0;j<7;j++){
                if(d[i][j]){
                    d[i][j]->close();
                    QCoreApplication::processEvents();
                }
            }
        }
        emit toMenu();
    }
}

void window::put()
{
    down->play();
    for(int i=0;(float)(n+G*i*i)<=(float)diskypos[board_i[temp_c]-1];i++){
        d[board_i[temp_c]-1][temp_c]->setGeometry(diskxpos[temp_c],n+G*i*i,65,65);        //設定位置大小
        d[board_i[temp_c]-1][temp_c]->setAlignment(Qt::AlignCenter);
        if(disk_color)
            d[board_i[temp_c]-1][temp_c]->setPixmap(d2.scaled(65,65,Qt::KeepAspectRatio));
        else
            d[board_i[temp_c]-1][temp_c]->setPixmap(d1.scaled(65,65,Qt::KeepAspectRatio));
        d[board_i[temp_c]-1][temp_c]->show();
        QCoreApplication::processEvents();
    }

    down->stop();

    d[board_i[temp_c]-1][temp_c]->setGeometry(diskxpos[temp_c],diskypos[board_i[temp_c]-1],65,65);        //設定位置大小
    d[board_i[temp_c]-1][temp_c]->setAlignment(Qt::AlignCenter);
    if(disk_color)
        d[board_i[temp_c]-1][temp_c]->setPixmap(d2.scaled(65,65,Qt::KeepAspectRatio));
    else
        d[board_i[temp_c]-1][temp_c]->setPixmap(d1.scaled(65,65,Qt::KeepAspectRatio));
    d[board_i[temp_c]-1][temp_c]->show();
    QCoreApplication::processEvents();


    floor->play();
    for(int i=0;i<15000;i++)
        QCoreApplication::processEvents();
    floor->stop();

    n=80;
    pause=false;

    emit next();
}

void window::undoPut()
{

    d[board_i[col_record[total_disk]]][col_record[total_disk]]->close();
    pause=false;//還原
    QCoreApplication::processEvents();

    if(ai){
        if(undo_num>0)
            emit undoAgain();
        else {
            undo_num=2;
            disk_color=!disk_color;
            emit next();
        }
    }
    else
        emit next();
}

QPixmap window::setImageRound(QPixmap &src,int radius){
    if(src.isNull()){
        return QPixmap();
    }

    QSize size(2*radius,2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(),999,999);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;

}

void window::play()
{

    if(!isWin(board,disk_color)&&total_disk<42)
    {
        if(!ai){
            disk_color = !disk_color;
            player_text="%1%2%3";
            player_text=player_text.arg("player ",QString::number(disk_color+1),"'s turn");
            player->setText(player_text);
            player->update();

            if(disk_color){
                playerImage->setPixmap(d2.scaled(100,120,Qt::KeepAspectRatio));
            }
            else {
                playerImage->setPixmap(d1.scaled(100,120,Qt::KeepAspectRatio));
            }
            playerImage->update();
        }
        else if(ai&&!disk_color_record){
            if(disk_color==disk_color_record){
                disk_color = !disk_color;

                player->setText("蔡孟勳's turn");
                player->update();
                QCoreApplication::processEvents();

                playerImage->setPixmap(d2.scaled(100,120,Qt::KeepAspectRatio));
                playerImage->update();
                QCoreApplication::processEvents();

                emit aiThinking();

            }
            else{
                disk_color = !disk_color;
                player->setText("your turn");
                player->update();

                playerImage->setPixmap(d1.scaled(100,120,Qt::KeepAspectRatio));
                playerImage->update();

                //emit setTime();
            }

        }
        else if(ai&&disk_color_record)  {
            if(disk_color==disk_color_record){
                disk_color = !disk_color;

                player->setText("your turn");
                player->update();

                playerImage->setPixmap(d1.scaled(100,120,Qt::KeepAspectRatio));
                playerImage->update();

                //emit setTime();

            }
            else{
                disk_color = !disk_color;
                player->setText("蔡孟勳's turn");
                player->update();
                QCoreApplication::processEvents();

                playerImage->setPixmap(d2.scaled(100,120,Qt::KeepAspectRatio));
                playerImage->update();
                QCoreApplication::processEvents();


                emit aiThinking();
            }
        }
    }
    else if(!isWin(board,disk_color)&&total_disk==42){
        draw=true;
        total_text="%1%2%3";
        total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
        totalLabel->setText(total_text);
        if(ai){
            score_text="%1%2%3%4";
            score_text=score_text.arg("Score(YOU/AI)\n\n",QString::number(yourscore)," : ",QString::number(aiscore));
            scorel->setText(score_text);
            scorel->update();
        }
        else{

            score_text="%1%2%3%4";
            score_text=score_text.arg("Score(P1/P2)\n\n",QString::number(p1score)," : ",QString::number(p2score));
            scorel->setText(score_text);
            scorel->update();
        }

        oframe=new over(draw,disk_color,ai,disk_color,disk_color_record,nullptr);
        connect(oframe->again,SIGNAL(clicked()),this,SLOT(reset()));
        connect(oframe->again ,&QPushButton::clicked,oframe,&over::quit_);
        connect(oframe->closed,SIGNAL(clicked()),this,SLOT(toEnd()));
        connect(oframe->closed,&QPushButton::clicked,oframe,&over::quit_);

        oframe->show();
        conti=false;
    }
    else{

        //QRgb * record_line;
        QPixmap *d1change;
        d1change=new QPixmap;
        *d1change=d1;
        for(int i=0;i<d1change->height();i++)
        {
        }

        ai ? ( disk_color==1 ? aiscore++ : yourscore++ ) : ( disk_color==1 ? p2score++ : p1score++ );

        total_text="%1%2%3";
        total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
        totalLabel->setText(total_text);
        if(ai){
            score_text="%1%2%3%4";
            score_text=score_text.arg("Score(YOU/AI)\n\n",QString::number(yourscore)," : ",QString::number(aiscore));
            scorel->setText(score_text);
            scorel->update();
        }
        else{

            score_text="%1%2%3%4";
            score_text=score_text.arg("Score(P1/P2)\n\n",QString::number(p1score)," : ",QString::number(p2score));
            scorel->setText(score_text);
            scorel->update();
        }
        oframe=new over(draw,disk_color,ai,disk_color,disk_color_record,nullptr);

        connect(oframe->again,SIGNAL(clicked()),this,SLOT(reset()));
        connect(oframe->again ,&QPushButton::clicked,oframe,&over::quit_);
        connect(oframe->closed,SIGNAL(clicked()),this,SLOT(toEnd()));
        connect(oframe->closed,&QPushButton::clicked,oframe,&over::quit_);
        connect(pc->undo,&QPushButton::clicked,oframe,&over::quit_);

        oframe->show();
        conti=false;
        disk_color = !disk_color;
    }

}

void window::aiPut()
{
    QCoreApplication::processEvents();
    if(!disk_color_record){
        switch(diff){
        case Easy:
            get=E.easy_ai(board_,disk[1],disk[0]);
            break;
        case Normal:
            get=N.normal_ai(board_,disk[1],disk[0]);
            break;
        case Hard:
            get=H.hard_ai(board_,disk[1],disk[0]);
            break;
        default:
            break;
        }

        switch(get)
        {
        case 0:
            col1Clicked();
            break;
        case 1:
            col2Clicked();
            break;
        case 2:
            col3Clicked();
            break;
        case 3:
            col4Clicked();
            break;
        case 4:
            col5Clicked();
            break;
        case 5:
            col6Clicked();
            break;
        case 6:
            col7Clicked();
            break;

        }
    }
    else{
        switch(diff){
        case Easy:
            get=E.easy_ai(board_,disk[1],disk[0]);
            break;
        case Normal:
            get=N.normal_ai(board_,disk[1],disk[0]);
            break;
        case Hard:
            get=H.hard_ai(board_,disk[1],disk[0]);
            break;
        default:
            break;
        }

        switch(get)
        {
        case 0:
            col1Clicked();
            break;
        case 1:
            col2Clicked();
            break;
        case 2:
            col3Clicked();
            break;
        case 3:
            col4Clicked();
            break;
        case 4:
            col5Clicked();
            break;
        case 5:
            col6Clicked();
            break;
        case 6:
            col7Clicked();
            break;

        }
    }


}

/*
void window::countTime()
{

    if(!column_clicked){
        hold_time=0;
        while(hold_time<=2000){
            time_text="%1%2%3";
            time_text=time_text.arg("remain ",QString::number(20-hold_time/100)," sec");
            countDown->setGeometry(530,380,120,40);
            countDown->setText(time_text);
            countDown->setFont(QFont("Courier",14));
            countDown->update();
            QCoreApplication::processEvents();
            //sleep(1);
            hold_time++;
        }
        wframe=new winner(disk_color,ai,disk_color,disk_color_record,nullptr);
        connect(wframe->again,SIGNAL(clicked()),this,SLOT(reset()));
        connect(wframe->again,&QPushButton::clicked,wframe,&winner::quit_);
        connect(wframe->closed,&QPushButton::clicked,this,&window::close);

        wframe->show();
    }
    else {
        column_clicked=false;
    }


}
*/

void window::toEnd()
{
    if(ai)
        re=new resultpage(ai,yourscore,aiscore,nullptr);
    else
        re=new resultpage(ai,p1score,p2score,nullptr);

    re->show();
    connect(re->ok,SIGNAL(clicked()),this,SLOT(toCloseApp()));
    connect(re->mainMenu,SIGNAL(clicked()),this,SLOT(backToMenu()));
    connect(re->mainMenu,SIGNAL(clicked()),re,SLOT(toClose()));
}

void window::toCloseApp()
{
    emit toClose();
}

void window::noai()
{
    diff=None;
    ai=false;
    start();
}

void window::connectEasy()
{
    diff=Easy;
    ai=true;
    start();
}

void window::connectNormal()
{
    diff=Normal;
    ai=true;
    start();
}

void window::connectHard()
{
    diff=Hard;
    ai=true;
    start();
}

bool window::isWin(char b[6][7], bool c) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (j + 3 < 7) {
                if (b[i][j] == disk[c] && b[i][j+1] == disk[c] && b[i][j + 2] == disk[c] && b[i][j + 3] == disk[c]) {

                    for(int k=0;k<4;k++){
                        connect_four[k].x=i;
                        connect_four[k].y=j+k;
                    }
                    return 1;
                }
            }
            if (i + 3 < 6) {
                if (b[i][j] == disk[c] && b[i + 1][j] == disk[c] && b[i + 2][j] == disk[c]&& b[i + 3][j]== disk[c]) {
                    for(int k=0;k<4;k++){
                        connect_four[k].x=i+k;
                        connect_four[k].y=j;
                    }
                    return 1;
                }
            }
            if ((j + 3 < 7) && (i + 3 < 6)) {
                if (b[i][j] == disk[c]&& b[i + 1][j + 1] == disk[c] && b[i + 2][j + 2] == disk[c] && b[i + 3][j + 3]== disk[c]) {
                    for(int k=0;k<4;k++){
                        connect_four[k].x=i+k;
                        connect_four[k].y=j+k;
                    }
                    return 1;
                }
            }
            if ((j - 3 >= 0) && (i + 3 < 6)) {
                if (b[i][j] == disk[c] && b[i + 1][j - 1]== disk[c] && b[i + 2][j - 2] == disk[c] && b[i + 3][j - 3]== disk[c]) {
                    for(int k=0;k<4;k++){
                        connect_four[k].x=i+k;
                        connect_four[k].y=j-k;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}






void window::setboard_()
{
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            board_[i][j]=board[5-i][j];
        }
    }
}

void window::undoClicked()
{
    //if(conti){
        //column_clicked=true;
        if(total_disk-1>=0){
            conti=true;
            total_disk--;
            board_i[col_record[total_disk]]-=1;
            pause=true;
            board[board_i[col_record[total_disk]]][col_record[total_disk]]=disk[2];
            setboard_();

            //board_i[col_record[total_disk]]-=1;

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);


            tframe->set(board_);


            //tframe->show();
            //emit setTime();
            if(ai){
                undo_num--;
            }
            emit undoSet();

        }
        else{
            full=false;
            eframe=new error(full,nullptr);
            eframe->show();
        }
    //}
}

void window::col1Clicked()
{
    if(conti&&!pause){
        column_clicked=true;
        if(board_i[0]<6){
            pause=true;
            temp_c=0;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[0]][0]=disk[disk_color];
            board_i[0]+=1;
            setboard_();
            tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();

            //emit setTime();
            emit set();
        }
        else
            if(board_i[0]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

void window::col2Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[1]<6){
            pause=true;
            temp_c=1;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[1]][1]=disk[disk_color];
            board_i[1]+=1;
            setboard_();

            //tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();
            //emit setTime();
            emit set();
        }
        else
            if(board_i[1]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

void window::col3Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[2]<6){
            pause=true;
            temp_c=2;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[2]][2]=disk[disk_color];
            board_i[2]+=1;
            setboard_();

            tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();
            //emit setTime();
            emit set();
        }
        else
            if(board_i[2]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

void window::col4Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[3]<6){
            temp_c=3;
            pause=true;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[3]][3]=disk[disk_color];
            board_i[3]+=1;
            setboard_();

            tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();
            //emit setTime();
            emit set();
        }
        else
            if(board_i[3]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }
}

void window::col5Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[4]<6){
            pause=true;
            temp_c=4;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[4]][4]=disk[disk_color];
            board_i[4]+=1;
            setboard_();

            tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();

            //emit setTime();
            emit set();
        }
        else
            if(board_i[4]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

void window::col6Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[5]<6){
            pause=true;
            temp_c=5;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[5]][5]=disk[disk_color];
            board_i[5]+=1;
            setboard_();

            tframe->set(board_);

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);
            //tframe->show();
            //emit setTime();
            emit set();
        }
        else
            if(board_i[5]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

void window::col7Clicked()
{
    if(conti&&!pause){

        column_clicked=true;
        if(board_i[6]<6){
            pause=true;
            temp_c=6;
            col_record[total_disk]=temp_c;
            total_disk++;
            board[board_i[6]][6]=disk[disk_color];
            board_i[6]+=1;
            setboard_();

            total_text="%1%2%3";
            total_text=total_text.arg("remain ",QString::number(TOTAL-total_disk)," disks");
            totalLabel->setText(total_text);

            tframe->set(board_);
            //tframe->show();
            //emit setTime();
            emit set();
        }
        else
            if(board_i[6]==6){
                full=true;
                eframe=new error(full,nullptr);
                eframe->show();
            }
    }

}

