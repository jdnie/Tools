/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Open_Encrypt_clicked();

    void on_pushButton_Open_Decrypt_clicked();

    void on_lineEdit_DstFile_Encrypt_textEdited(const QString &arg1);

    void on_lineEdit_DstFile_Decrypt_textEdited(const QString &arg1);

    void on_lineEdit_Key_Encrypt_textEdited(const QString &arg1);

    void on_lineEdit_Key_Decrypt_textEdited(const QString &arg1);

    void on_pushButton_Done_Encrypt_clicked();

    void on_pushButton_Done_Decrypt_clicked();

    void on_Encrypt_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    QString srcEnFileName;
    QString dstEnFileName;
    QString enKey;
    QString srcDeFileName;
    QString dstDeFileName;
    QString deKey;
};

#endif // MAINWINDOW_H
