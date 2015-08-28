#include "imagedatapainter.h"
#include <QDebug>
void steepVector3D(QVector3D &vec);

ImageDataPainter::ImageDataPainter(QImage *img,ModelManager *mgr,QObject *parent) : QObject(parent)
{
    m_image = img;
    m_model = mgr;
}

bool ImageDataPainter::draw()
{
    QVector<QVector3D> *data = m_model->vertexBuffer3D();
    QVector<QVector<int>> *faces = m_model->facesBuffer();

    for(int i = 0; i < faces->count() ; i++)
    {
        const QVector<int> *face = &faces->at(i);
        for(int j = 0 ; j < 3 ; j++)
        {
            QVector3D start = data->at( face->at(j) );
            QVector3D end = data->at( face->at((j+1)%3) );
            start.setX( (start.x()+1.)*(m_image->width()-1)/2.  );
            start.setY( (start.y()+1.)*(m_image->height()-1)/2.  );
            end.setX( (end.x()+1.)*(m_image->width()-1)/2.  );
            end.setY( (end.y()+1.)*(m_image->height()-1)/2.  );
            drawLine( start , end , QColor(255,255,255)  );
        }

    }





    return true;
}





bool ImageDataPainter::drawLine(QVector3D stPoint, QVector3D endPoint, const QColor &color)
{

    // if line is steep , transpose it
    bool steep = false;
    if(std::abs(endPoint.x() - stPoint.x() ) < std::abs(stPoint.y() - endPoint.y())  )
    {
        steep = true;
        steepVector3D(stPoint);
        steepVector3D(endPoint);
    }
    // for support symmetry render line from left to right
    if(stPoint.x() > endPoint.x())
        std::swap(stPoint,endPoint);

    int dx = endPoint.x() - stPoint.x();
    int dy = endPoint.y() - stPoint.y();

    int derror2 = std::abs(dy)*2;
    int error2 = 0;

    int y = stPoint.y();


    for(int x = stPoint.x(); x<endPoint.x();x++)
    {

        if(steep)
            m_image->setPixel(y,x,color.rgba()); // if transposed,de-transpose
        else
            m_image->setPixel(x,y,color.rgba());

        error2 += derror2;
        if (error2 > dx) {
            y += (endPoint.y()>stPoint.y()?1:-1);
            error2 -= dx*2;
        }

    }





    return true;
}



// UTILS FUNCTIONS
void steepVector3D(QVector3D &vec)
{
    float tmp;
    tmp = vec.x();
    vec.setX( vec.y() );
    vec.setY(tmp);
}





