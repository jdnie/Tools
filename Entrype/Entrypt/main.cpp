/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
