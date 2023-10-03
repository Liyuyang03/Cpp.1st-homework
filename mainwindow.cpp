#pragma execution_character_set("utf-8")

#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit->setFocusPolicy(Qt::NoFocus);
    connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(OpenImg()));
    connect(ui.pushButton_2, SIGNAL(clicked(bool)), this, SLOT(GrayImg()));
}

void mainwindow::OpenImg()
{
    QString OpenFile, OpenFilePath;
    QImage image;
    //读取原始图片
    OpenFile = QFileDialog::getOpenFileName(this,
        "请选择图片",
        "",
        "Image Files(*.jpg *.png *.bmp *.pgm *.pbm)");
    //label放置图片,按比例缩放
    if (OpenFile != "")
    {
        image.load(OpenFile);
        ui.label->setPixmap(QPixmap::fromImage(image).scaled(ui.label->size()));
    //显示图片路径
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui.lineEdit->setText(OpenFilePath);
    }
}

void mainwindow::GrayImg()
{
    //读取路径
    QString OpenFile = ui.lineEdit->text();
    string path = OpenFile.toStdString();
    if (path != "")
    {
        //读取原始图片
        Mat srcimage = imread(path);

        Mat retumage;
        //灰度处理 灰度是单通道8位 QImage是24位三通道
        cvtColor(srcimage, retumage, COLOR_BGR2GRAY);
        cvtColor(retumage, retumage, COLOR_GRAY2BGR);

        //Mat转QImage 像素  label放置图像处理后图片
        QImage image = QImage(retumage.data, retumage.cols, retumage.rows, retumage.cols * retumage.channels(), QImage::Format_RGB888);
        image = image.scaled(ui.label->width(), ui.label->height());
        ui.label->setPixmap(QPixmap::fromImage(image).scaled(ui.label->size()));
    }
}