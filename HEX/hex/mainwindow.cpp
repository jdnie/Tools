/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_Src_textChanged(const QString &arg1)
{
    QString zero("0");
    QString one("1");
    QString invalid("#");
    QString::iterator it, it_end;
    int size = 0, start, i;
    char chart;

    size = arg1.size();
    if ((size > 10) || (size == 0))
    {
        return;
    }

    if (size >= 2)
    {
        if ((arg1.at(0) == '0') && ((arg1.at(1) == 'x') || (arg1.at(1) == 'X')))
        {
            result = arg1;
        }
        else
        {
            result = arg1;
            result.push_front("0x");
        }
    }
    else
    {
        result = arg1;
        result.push_front("0x");
    }


    while (result.size() != 10)
    {
        result.insert(2, '0');
    }

    it = result.begin(); it++; it++;
    it_end = result.end();
    start = 32;
    while (it != it_end)
    {
        chart = it->toAscii();
        if ((chart >= 'A') && (chart <= 'F'))
        {
            chart -= 'A';
            chart += 10;
        }
        else if ((chart >= 'a') && (chart <= 'f'))
        {
            chart -= 'a';
            *it = chart + 'A';
            chart += 10;
        }
        else if ((chart >= '0') && (chart <= '9'))
        {
            chart -= '0';
        }
        else
        {
            chart = 0x10;
            *it = '#';
        }

        if (chart == 0x10)
        {
            for (i=0; i<4; i++)
            {
                bits[start-i-1] = '#';
            }
            start-=4;
        }
        else
        {
            for (i=4; i>0; i--)
            {
                bits[start-i] = (chart & 0x1) ? '1' : '0';
                chart = chart >> 1;
            }
            start-=4;
        }
        it++;
    }

    ui->textEdit_Result->setText(result);
    ui->lineEdit_031->setText(bits[31]);
    ui->lineEdit_030->setText(bits[30]);
    ui->lineEdit_029->setText(bits[29]);
    ui->lineEdit_028->setText(bits[28]);
    ui->lineEdit_027->setText(bits[27]);
    ui->lineEdit_026->setText(bits[26]);
    ui->lineEdit_025->setText(bits[25]);
    ui->lineEdit_024->setText(bits[24]);
    ui->lineEdit_023->setText(bits[23]);
    ui->lineEdit_022->setText(bits[22]);
    ui->lineEdit_021->setText(bits[21]);
    ui->lineEdit_020->setText(bits[20]);
    ui->lineEdit_019->setText(bits[19]);
    ui->lineEdit_018->setText(bits[18]);
    ui->lineEdit_017->setText(bits[17]);
    ui->lineEdit_016->setText(bits[16]);
    ui->lineEdit_015->setText(bits[15]);
    ui->lineEdit_014->setText(bits[14]);
    ui->lineEdit_013->setText(bits[13]);
    ui->lineEdit_012->setText(bits[12]);
    ui->lineEdit_011->setText(bits[11]);
    ui->lineEdit_010->setText(bits[10]);
    ui->lineEdit_009->setText(bits[9]);
    ui->lineEdit_008->setText(bits[8]);
    ui->lineEdit_007->setText(bits[7]);
    ui->lineEdit_006->setText(bits[6]);
    ui->lineEdit_005->setText(bits[5]);
    ui->lineEdit_004->setText(bits[4]);
    ui->lineEdit_003->setText(bits[3]);
    ui->lineEdit_002->setText(bits[2]);
    ui->lineEdit_001->setText(bits[1]);
    ui->lineEdit_000->setText(bits[0]);
    ui->lineEdit_031->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_030->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_029->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_028->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_027->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_026->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_025->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_024->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_023->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_022->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_021->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_020->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_019->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_018->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_017->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_016->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_015->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_014->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_013->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_012->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_011->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_010->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_009->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_008->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_007->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_006->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_005->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_004->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_003->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_002->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_001->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
    ui->lineEdit_000->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 255);"));
}

void MainWindow::on_lineEdit_id_textEdited(const QString &arg1, int id)
{
    int seg;

    seg = id / 4;
    seg <<= 2;
    if ((arg1.size() != 1) || ((arg1.at(0) != '0') && (arg1.at(0) != '1')))
    {
        return;
    }

    char tmp = 0;
    bits[id] = arg1.at(0);
    tmp |= (bits[seg+3] == '1'); tmp <<= 1;
    tmp |= (bits[seg+2] == '1'); tmp <<= 1;
    tmp |= (bits[seg+1] == '1'); tmp <<= 1;
    tmp |= (bits[seg] == '1');

    if (tmp < 10)
    {
        tmp += '0';
    }
    else
    {
        tmp -= 10;
        tmp += 'A';
    }

    seg >>= 2;
    result.replace(9-seg, 1, tmp);
    ui->textEdit_Result->setText(result);
}

void MainWindow::on_lineEdit_031_textEdited(const QString &arg1)
{
    int id = 31;

    ui->lineEdit_031->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_031->setText(bits[id]);
}

void MainWindow::on_lineEdit_030_textEdited(const QString &arg1)
{
    int id = 30;

    ui->lineEdit_030->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_030->setText(bits[id]);
}

void MainWindow::on_lineEdit_029_textEdited(const QString &arg1)
{
    int id = 29;

    ui->lineEdit_029->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_029->setText(bits[id]);
}

void MainWindow::on_lineEdit_028_textEdited(const QString &arg1)
{
    int id = 28;

    ui->lineEdit_028->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_028->setText(bits[id]);
}

void MainWindow::on_lineEdit_027_textEdited(const QString &arg1)
{
    int id = 27;

    ui->lineEdit_027->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_027->setText(bits[id]);
}

void MainWindow::on_lineEdit_026_textEdited(const QString &arg1)
{
    int id = 26;

    ui->lineEdit_026->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_026->setText(bits[id]);
}

void MainWindow::on_lineEdit_025_textEdited(const QString &arg1)
{
    int id = 25;

    ui->lineEdit_025->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_025->setText(bits[id]);
}

void MainWindow::on_lineEdit_024_textEdited(const QString &arg1)
{
    int id = 24;

    ui->lineEdit_024->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_024->setText(bits[id]);
}

void MainWindow::on_lineEdit_023_textEdited(const QString &arg1)
{
    int id = 23;

    ui->lineEdit_023->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_023->setText(bits[id]);
}

void MainWindow::on_lineEdit_022_textEdited(const QString &arg1)
{
    int id = 22;

    ui->lineEdit_022->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_022->setText(bits[id]);
}

void MainWindow::on_lineEdit_021_textEdited(const QString &arg1)
{
    int id = 21;

    ui->lineEdit_021->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_021->setText(bits[id]);
}

void MainWindow::on_lineEdit_020_textEdited(const QString &arg1)
{
    int id = 20;

    ui->lineEdit_020->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_020->setText(bits[id]);
}

void MainWindow::on_lineEdit_019_textEdited(const QString &arg1)
{
    int id = 19;

    ui->lineEdit_019->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_019->setText(bits[id]);
}

void MainWindow::on_lineEdit_018_textEdited(const QString &arg1)
{
    int id = 18;

    ui->lineEdit_018->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_018->setText(bits[id]);
}

void MainWindow::on_lineEdit_017_textEdited(const QString &arg1)
{
    int id = 17;

    ui->lineEdit_017->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_017->setText(bits[id]);
}

void MainWindow::on_lineEdit_016_textEdited(const QString &arg1)
{
    int id = 16;

    ui->lineEdit_016->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_016->setText(bits[id]);
}

void MainWindow::on_lineEdit_015_textEdited(const QString &arg1)
{
    int id = 15;

    ui->lineEdit_015->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_015->setText(bits[id]);
}

void MainWindow::on_lineEdit_014_textEdited(const QString &arg1)
{
    int id = 14;

    ui->lineEdit_014->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_014->setText(bits[id]);
}

void MainWindow::on_lineEdit_013_textEdited(const QString &arg1)
{
    int id = 13;

    ui->lineEdit_013->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_013->setText(bits[id]);
}

void MainWindow::on_lineEdit_012_textEdited(const QString &arg1)
{
    int id = 12;

    ui->lineEdit_012->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_012->setText(bits[id]);
}

void MainWindow::on_lineEdit_011_textEdited(const QString &arg1)
{
    int id = 11;

    ui->lineEdit_011->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_011->setText(bits[id]);
}

void MainWindow::on_lineEdit_010_textEdited(const QString &arg1)
{
    int id = 10;

    ui->lineEdit_010->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_010->setText(bits[id]);
}

void MainWindow::on_lineEdit_009_textEdited(const QString &arg1)
{
    int id = 9;

    ui->lineEdit_009->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_009->setText(bits[id]);
}

void MainWindow::on_lineEdit_008_textEdited(const QString &arg1)
{
    int id = 8;

    ui->lineEdit_008->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_008->setText(bits[id]);
}

void MainWindow::on_lineEdit_007_textEdited(const QString &arg1)
{
    int id = 7;

    ui->lineEdit_007->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_007->setText(bits[id]);
}

void MainWindow::on_lineEdit_006_textEdited(const QString &arg1)
{
    int id = 6;

    ui->lineEdit_006->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_006->setText(bits[id]);
}

void MainWindow::on_lineEdit_005_textEdited(const QString &arg1)
{
    int id = 5;

    ui->lineEdit_005->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_005->setText(bits[id]);
}

void MainWindow::on_lineEdit_004_textEdited(const QString &arg1)
{
    int id = 4;

    ui->lineEdit_004->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_004->setText(bits[id]);
}

void MainWindow::on_lineEdit_003_textEdited(const QString &arg1)
{
    int id = 3;

    ui->lineEdit_003->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_003->setText(bits[id]);
}

void MainWindow::on_lineEdit_002_textEdited(const QString &arg1)
{
    int id = 2;

    ui->lineEdit_002->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_002->setText(bits[id]);
}

void MainWindow::on_lineEdit_001_textEdited(const QString &arg1)
{
    int id = 1;

    ui->lineEdit_001->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_001->setText(bits[id]);
}

void MainWindow::on_lineEdit_000_textEdited(const QString &arg1)
{
    int id = 0;

    ui->lineEdit_000->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(255, 0, 0);"));

    on_lineEdit_id_textEdited(arg1, id);

    ui->lineEdit_000->setText(bits[id]);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        show();
    }
    else
    {
        Qt::WindowFlags type = windowFlags();
        type &= ~Qt::WindowStaysOnTopHint;
        setWindowFlags(type);
        show();
    }
}
