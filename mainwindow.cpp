#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmanager.h"
#include <QDebug>

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
}

MainWindow::~MainWindow()
{
    if(m_image != nullptr)
    {
        delete m_image;
        m_image = nullptr;
    }
    delete ui;
}
