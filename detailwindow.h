#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H



#include "mainwindow.h"

class DetailWindow : public MainWindow {
public:
    DetailWindow(){
        setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    }
    ~DetailWindow(){}
};

#endif // DETAILWINDOW_H
