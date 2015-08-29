#ifndef IMAGEDATAPAINTER_H
#define IMAGEDATAPAINTER_H

#include <QObject>
#include "modelmanager.h"
#include <QImage>
#include <QColor>
#include "tgaimage.h"

class ImageDataPainter : public QObject
{
    Q_OBJECT
public:
    explicit ImageDataPainter(QImage *img,ModelManager *mgr,QObject *parent = 0);

    bool draw();

    void drawLine(QVector3D stPoint,QVector3D endPoint,const QColor &color);
    void drawTriangle(QVector3D v0 , QVector3D v1 , QVector3D v2 , const QColor &color, int *zBuffer);


signals:

public slots:

private:
    TGAImage *image;
    QImage *m_image;
    ModelManager *m_model;
};

#endif // IMAGEDATAPAINTER_H
