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


    qDebug() << m_image->width() << " " << m_image->height();
    for(int i = 0; i < faces->count() ; i++)
    {
        const QVector<int> *face = &faces->at(i);

        QVector3D triangleCoords[3];

        for(int j = 0 ; j < 3 ; j++ )
        {
            QVector3D vec = data->at( face->at(j));
            vec.setX( (vec.x() + 1.)*(m_image->width()-1.)/2. );
            vec.setY( (vec.y() + 1.)*(m_image->height()-1.)/2.);
            triangleCoords[j] = vec;
        }

        drawTriangle(triangleCoords[0],triangleCoords[1],triangleCoords[2],QColor(qrand()%255, qrand()%255,qrand()%255 ));




        /*
        for(int j = 0 ; j < 3 ; j++)
        {
            QVector3D start = data->at( face->at(j) );
            QVector3D end = data->at( face->at((j+1)%3) );
            start.setX( (start.x()+1.)*(m_image->width()-1)/2.  );
            start.setY( (start.y()+1.)*(m_image->height()-1)/2.  );
            end.setX( (end.x()+1.)*(m_image->width()-1)/2.  );
            end.setY( (end.y()+1.)*(m_image->height()-1)/2.  );
            drawLine( start , end , QColor(255,255,255)  );
        }*/





    }



    return true;
}





void ImageDataPainter::drawLine(QVector3D stPoint, QVector3D endPoint, const QColor &color)
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





}

void ImageDataPainter::drawTriangle(QVector3D v0, QVector3D v1, QVector3D v2, const QColor &color)
{
    if( v0.y() == v1.y()  && v0.y() == v2.y() ) return ; // ignore degenerate triangles

    if(v0.y() > v1.y() ) std::swap(v0,v1);
    if(v0.y() > v2.y() ) std::swap(v0,v2);
    if(v1.y() > v2.y() ) std::swap(v1,v2);


    int total_height = v2.y() - v0.y();
    for(int i = 0 ; i<total_height;i++)
    {
        bool second_half = i > (v1.y() - v0.y()) || v1.y() == v0.y();
        int  segment_height = second_half ? v2.y() - v1.y() : v1.y() - v0.y();

        if(total_height == 0 || segment_height == 0 ) return;

        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? v1.y()-v0.y() : 0))/segment_height;

        QVector3D A = v0 + (v2 - v0)*alpha;
        QVector3D B = (second_half ? (v1 + (v2-v1)*beta) : (v0 + (v1-v0)*beta)  )  ;

        if(A.x() > B.x() ) std::swap(A,B);

        for(int j = A.x() ; j< B.x() ; j++)
        {
            m_image->setPixel(j , v0.y() + i , color.rgb() );
        }



    }


}



// UTILS FUNCTIONS
void steepVector3D(QVector3D &vec)
{
    float tmp;
    tmp = vec.x();
    vec.setX( vec.y() );
    vec.setY(tmp);
}





