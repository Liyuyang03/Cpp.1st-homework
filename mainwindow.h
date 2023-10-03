#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include <Qlabel>
#include <QLineEdit>
#include <QImage>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::mainwindowClass ui;

private slots:
    void OpenImg();
    void GrayImg();
};
