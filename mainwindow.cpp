
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QToolBar>
#include <QMenu>
#include <QKeyEvent>
#include <QString>
#include <QDebug>
#include <time.h>
#include <QTime>
#include <QFile>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openAction = new QAction(tr("&Start Game"), this);

    QMenu *menu = menuBar() -> addMenu(tr("&test0"));
    menu -> addAction(openAction);

    QToolBar *toolBar = addToolBar("&tool bar");
    toolBar -> addAction(openAction);

    start_time = clock();

    Key_num[1] = Qt :: Key_1;
    Key_num[2] = Qt :: Key_3;// I'll complete it in Option menu later

    Path = "E:/Music_game/test0/Data/1.txt";

    Read_Music_Data(Path);

}

int MainWindow :: ReadInt(QFile* file){
    char c = 0; int ans = 0;
    file -> getChar(&c);
    while(c < '0' || c > '9')file -> getChar(&c);
    while(c >= '0' && c <= '9'){
        ans = ans * 10 + c - '0';
        bool flag = file -> getChar(&c);
        if(flag == 0) return ans;
    }
    return ans;
}

void MainWindow :: Read_Music_Data(const QString & Path){
    QFile file(Path);
    file.open(QIODevice :: ReadOnly | QIODevice :: Text);
    Track_num = ReadInt(&file);
    Total_time = ReadInt(&file);
    for(int i = 1; i <= Track_num; i ++){
        int m = ReadInt(&file);
        for(int j = 1; j <= m; j ++){
            int x = ReadInt(&file), l, r;
            if(x == 1){
                l = ReadInt(&file);
                tm[i].push_back(std :: make_pair(l,-1));
            }
            else{
                l = ReadInt(&file), r = ReadInt(&file);
                tm[i].push_back(std :: make_pair(l, r));
            }
        }
        tm[i].push_back(std :: make_pair(Total_time + 114514, -1));
        ptr[i] = 0;
    }
    for(int i = 1; i <= Track_num; i ++)
        qDebug() << tm[i].size() << " "; qDebug() << "\n";
    //qDebug() << "Read End!";
}

void MainWindow::Miss(){
    combo = 0;
    //qDebug() << "No!";
}

void MainWindow :: Correct(){
    combo ++;
    //qDebug() << "Yes!";
}

void MainWindow :: Correct_Long(){
    combo ++;
    //qDebug() << "Yes Long!";
}

void MainWindow :: Pressed_Effect(int x){
    //Some Special Effect
}

void MainWindow :: keyPressEvent(QKeyEvent *event){
    for(int i = 1; i <= Track_num; i ++){
        if(event -> key() == Key_num[i]){
            if(event -> isAutoRepeat())return;
            Pressed_Effect(i);
            double now_time = clock() - start_time;
            while(ptr[i] < tm[i].size() && now_time - tm[i][ptr[i]].first > eps){
                ptr[i] ++;
            }
            if(abs(now_time - tm[i][ptr[i]].first) <= eps){
                if(tm[i][ptr[i]].second == -1)Correct(),ptr[i]++;
            }
            else{
                if(now_time > tm[i][ptr[i]].first)tm[i][ptr[i]].second = -1;
                Miss();
            }
        }
    }
}

void MainWindow :: keyReleaseEvent(QKeyEvent *event){
    for(int i = 1; i <= Track_num; i ++){
        if(event -> key() == Key_num[i]){
            if(event -> isAutoRepeat())return;
            double now_time = clock() - start_time;
            int R = tm[i][ptr[i]].second;
            if(R == -1)return;
            if(abs(now_time - R) <= eps){
                Correct_Long();
            }
            else{
                Miss();
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


