/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encrypt.h"
#include <QFileDialog>
#include <QFile>
#include <string.h>
#include <memory.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Open_Encrypt_clicked()
{
    srcEnFileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*)"));
    dstEnFileName = srcEnFileName;
    dstEnFileName.push_back(".mi");
    ui->lineEdit_SrcFile_Encrypt->setText(srcEnFileName);
    ui->lineEdit_DstFile_Encrypt->setText(dstEnFileName);
}

void MainWindow::on_pushButton_Open_Decrypt_clicked()
{
    srcDeFileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("加密文件(*.mi)"));
    dstDeFileName = srcDeFileName;
    dstDeFileName.remove(".mi");
    ui->lineEdit_SrcFile_Decrypt->setText(srcDeFileName);
    ui->lineEdit_DstFile_Decrypt->setText(dstDeFileName);
}

void MainWindow::on_lineEdit_DstFile_Encrypt_textEdited(const QString &arg1)
{
    dstEnFileName = arg1;
}

void MainWindow::on_lineEdit_DstFile_Decrypt_textEdited(const QString &arg1)
{
    dstDeFileName = arg1;
}

void MainWindow::on_lineEdit_Key_Encrypt_textEdited(const QString &arg1)
{
    enKey = arg1;
}

void MainWindow::on_lineEdit_Key_Decrypt_textEdited(const QString &arg1)
{
    deKey = arg1;
}

void MainWindow::on_pushButton_Done_Encrypt_clicked()
{
    encrypt algs;
    long hashenKey;
    long long file_len, tmp, en_len = 0;
    int  i, size = sizeof(long);
    unsigned char src[8];
    char dst[32] = {0};
    char ming_wen[4096];
    char mi_wen[4096];
    int  stat;
    QByteArray enKeyAscii = enKey.toAscii();
    QFile srcFile(srcEnFileName), dstFile(dstEnFileName);

    if (!(srcFile.open(QFile::ReadOnly)))
    {
        return;
    }
    if (!(dstFile.open(QFile::WriteOnly)))
    {
        return;
    }
    ui->progressBar->setVisible(true);
    QDataStream srcStream(&srcFile), dstStream(&dstFile);

    hashenKey = algs.JSHash(enKeyAscii.data());
    for (i=0; i<size; i++)
    {
        src[i] = (unsigned char)((hashenKey >> (i*8)) & 0xFF);
    }
    if (size == 4)
    {
        for (i=4; i<8; i++)
        {
            src[i] = src[i-4];
        }
    }

    algs.MD5_Encrypt((unsigned char *)dst, src, 8);

    file_len = srcFile.size();
    for (i=0; i<8; i++)
    {
        ming_wen[i+7] = (char)((file_len >> (i*8)) & 0xFF);
    }
    size = 64;
    algs.DesEncrypt(mi_wen, ming_wen, size, dst, strlen(dst));
    dstStream.writeRawData(mi_wen, size);
    dstFile.flush();
    stat = 10;
    ui->progressBar->setValue(stat);

    while (1)
    {
        size = srcStream.readRawData(ming_wen, 4096);
        if (size <= 0)
        {
            break;
        }

        if (size % 64)
        {
            size = ((size / 64) + 1) * 64;
        }
        algs.DesEncrypt(mi_wen, ming_wen, size, dst, strlen(dst));
        //algs.DesEncrypt(mi_wen, ming_wen, size, enKeyAscii.data(), strlen(enKeyAscii.data()));
        dstStream.writeRawData(mi_wen, size);
        dstFile.flush();
        en_len += size;
        stat = en_len * 90 / file_len + 10;
        ui->progressBar->setValue(stat);
    };
    ui->progressBar->setValue(100);
}

void MainWindow::on_pushButton_Done_Decrypt_clicked()
{
    encrypt algs;
    long hashenKey;
    long long file_len = 0, tmp, en_len = 0;
    int  i, size = sizeof(long);
    unsigned char src[8];
    char dst[32] = {0};
    char ming_wen[4096];
    char mi_wen[4096];
    int  stat;
    QByteArray enKeyAscii = deKey.toAscii();
    QFile srcFile(srcDeFileName), dstFile(dstDeFileName);

    if (!(srcFile.open(QFile::ReadOnly)))
    {
        return;
    }
    if (!(dstFile.open(QFile::WriteOnly)))
    {
        return;
    }
    ui->progressBar->setVisible(true);
    QDataStream srcStream(&srcFile), dstStream(&dstFile);

    hashenKey = algs.JSHash(enKeyAscii.data());
    for (i=0; i<size; i++)
    {
        src[i] = (unsigned char)((hashenKey >> (i*8)) & 0xFF);
    }
    if (size == 4)
    {
        for (i=4; i<8; i++)
        {
            src[i] = src[i-4];
        }
    }

    algs.MD5_Encrypt((unsigned char *)dst, src, 8);

    size = srcStream.readRawData(mi_wen, 64);
    if (size != 64)
    {
        return;
    }
    algs.DesDecrypt(ming_wen, mi_wen, size, dst, strlen(dst));
    for (i=0; i<8; i++)
    {
        tmp = ming_wen[i+7];
        file_len |= (tmp & 0xFF) << (i*8);
    }
    if (srcFile.size() < file_len)
    {
        return;
    }
    stat = 10;
    ui->progressBar->setValue(stat);

    while (1)
    {
        size = srcStream.readRawData(mi_wen, 4096);
        if (size <= 0)
        {
            break;
        }

        algs.DesDecrypt(ming_wen, mi_wen, size, dst, strlen(dst));
        //algs.DesDecrypt(ming_wen, mi_wen, size, enKeyAscii.data(), strlen(enKeyAscii.data()));
        if (file_len > size)
        {
            file_len -= size;
        }
        else
        {
            size = file_len;
        }

        dstStream.writeRawData(ming_wen, size);
        dstFile.flush();
        en_len += size;
        stat = en_len * 90 / file_len + 10;
        ui->progressBar->setValue(stat);
    };
    ui->progressBar->setValue(100);
}

void MainWindow::on_Encrypt_currentChanged(int index)
{
    ui->progressBar->setVisible(false);
}
