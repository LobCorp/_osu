
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <time.h>
#include <stdio.h>
#include <QTime>
#include <vector>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *openAction;

    void keyPressEvent(QKeyEvent *event);   // gamecore
    void keyReleaseEvent(QKeyEvent *event);
    void Miss();
    void Correct();
    void Correct_Long();
    const int eps = 400;

    double start_time = 0; // timer

    int id = 0; // id : music track num

    int score = 0;
    int combo = 0;

    int Track_num; // data of music track
    int Total_time;
    int Key_num[11];
    int ptr[11];
    std :: vector<std::pair<int,int> > tm[11];

    QString Path; // Music Data Path
    void Read_Music_Data(const QString & Path);
    int ReadInt(QFile* file);

    void Pressed_Effect(int pos); //Special Effects

private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
