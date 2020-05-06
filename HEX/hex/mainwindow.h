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
    void on_lineEdit_Src_textChanged(const QString &arg1);

    void on_lineEdit_id_textEdited(const QString &arg1, int id);

    void on_lineEdit_031_textEdited(const QString &arg1);

    void on_lineEdit_030_textEdited(const QString &arg1);

    void on_lineEdit_029_textEdited(const QString &arg1);

    void on_lineEdit_028_textEdited(const QString &arg1);

    void on_lineEdit_027_textEdited(const QString &arg1);

    void on_lineEdit_026_textEdited(const QString &arg1);

    void on_lineEdit_025_textEdited(const QString &arg1);

    void on_lineEdit_024_textEdited(const QString &arg1);

    void on_lineEdit_023_textEdited(const QString &arg1);

    void on_lineEdit_022_textEdited(const QString &arg1);

    void on_lineEdit_021_textEdited(const QString &arg1);

    void on_lineEdit_020_textEdited(const QString &arg1);

    void on_lineEdit_019_textEdited(const QString &arg1);

    void on_lineEdit_018_textEdited(const QString &arg1);

    void on_lineEdit_017_textEdited(const QString &arg1);

    void on_lineEdit_016_textEdited(const QString &arg1);

    void on_lineEdit_015_textEdited(const QString &arg1);

    void on_lineEdit_014_textEdited(const QString &arg1);

    void on_lineEdit_013_textEdited(const QString &arg1);

    void on_lineEdit_012_textEdited(const QString &arg1);

    void on_lineEdit_011_textEdited(const QString &arg1);

    void on_lineEdit_010_textEdited(const QString &arg1);

    void on_lineEdit_009_textEdited(const QString &arg1);

    void on_lineEdit_008_textEdited(const QString &arg1);

    void on_lineEdit_007_textEdited(const QString &arg1);

    void on_lineEdit_006_textEdited(const QString &arg1);

    void on_lineEdit_005_textEdited(const QString &arg1);

    void on_lineEdit_004_textEdited(const QString &arg1);

    void on_lineEdit_003_textEdited(const QString &arg1);

    void on_lineEdit_002_textEdited(const QString &arg1);

    void on_lineEdit_001_textEdited(const QString &arg1);

    void on_lineEdit_000_textEdited(const QString &arg1);

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QString result;
    QChar bits[32];
};

#endif // MAINWINDOW_H
