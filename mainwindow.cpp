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
    //��ȡԭʼͼƬ
    OpenFile = QFileDialog::getOpenFileName(this,
        "��ѡ��ͼƬ",
        "",
        "Image Files(*.jpg *.png *.bmp *.pgm *.pbm)");
    //label����ͼƬ,����������
    if (OpenFile != "")
    {
        image.load(OpenFile);
        ui.label->setPixmap(QPixmap::fromImage(image).scaled(ui.label->size()));
    //��ʾͼƬ·��
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui.lineEdit->setText(OpenFilePath);
    }
}

void mainwindow::GrayImg()
{
    //��ȡ·��
    QString OpenFile = ui.lineEdit->text();
    string path = OpenFile.toStdString();
    if (path != "")
    {
        //��ȡԭʼͼƬ
        Mat srcimage = imread(path);

        Mat retumage;
        //�Ҷȴ��� �Ҷ��ǵ�ͨ��8λ QImage��24λ��ͨ��
        cvtColor(srcimage, retumage, COLOR_BGR2GRAY);
        cvtColor(retumage, retumage, COLOR_GRAY2BGR);

        //MatתQImage ����  label����ͼ�����ͼƬ
        QImage image = QImage(retumage.data, retumage.cols, retumage.rows, retumage.cols * retumage.channels(), QImage::Format_RGB888);
        image = image.scaled(ui.label->width(), ui.label->height());
        ui.label->setPixmap(QPixmap::fromImage(image).scaled(ui.label->size()));
    }
}