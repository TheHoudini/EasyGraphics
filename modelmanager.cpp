#include "modelmanager.h"
#include <QFile>
#include <QStringList>
#include <QDebug>


ModelManager::ModelManager(QObject *parent) : QObject(parent)
{

}

bool ModelManager::loadModel(const QString &filename)
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        m_error = file.errorString();
        return false;
    }



    while(!file.atEnd())
    {
        QString line = file.readLine();
        if(line.left(2) == "v ")
        {
            // if it is vertex,process and append him to vertex buffer
            // vertex struct : v x y z ,where x y z - float data of vertex
            QStringList vertexData = line.split(" ");

            QVector3D vec( vertexData.at(1).toDouble(),
                           vertexData.at(2).toDouble(),
                           vertexData.at(3).toDouble() );
            m_vertexBuffer.append(vec);


        }else if (line.left(2) == "f ") {
            // if it is faces , process and append to faces buffer
            // they have struct like this : f a1/a2/a3 b1/b2/b3 c1/c2/c3
            // a1,b1 and c1 is three vertices of a triangle

            QStringList facesData = line.split(" ");
            QVector<int> triangleData;

            for(int i=1;i<=3;i++)
                triangleData.append( facesData.at(i).split("/").at(0).toInt() - 1);

            m_facesBuffer.append(triangleData);




        }

    }
    // debug info
    qDebug() << "Vertex size :" << m_vertexBuffer.size() << "Faces Size" << m_facesBuffer.size();
    return true;


}

QVector<QVector3D> *ModelManager::vertexBuffer3D()
{
    return &m_vertexBuffer;
}


QVector<QVector<int> > *ModelManager::facesBuffer()
{
    return &m_facesBuffer;
}

QString ModelManager::errorString()
{
    return m_error;
}

