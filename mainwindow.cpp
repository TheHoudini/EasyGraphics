#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmanager.h"
#include "painters/imagedatapainter.h"
#include <QDebug>
#include <QTransform>

#include <QRgb>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_image = nullptr;

    ModelManager mgr;
    if(!mgr.loadModel(":/african_head.obj"))
        qDebug() << "error on model load" << mgr.errorString();
    m_image = new QImage(width(),height(),QImage::Format_RGB32);
    m_image->fill(qRgba(0, 0, 0, 255));

    ImageDataPainter painter(m_image,&mgr,this);
    painter.draw();

    QTransform transform;
    transform.rotate(180);
    ui->ImgLabel->setPixmap(QPixmap::fromImage(m_image->transformed(transform)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
