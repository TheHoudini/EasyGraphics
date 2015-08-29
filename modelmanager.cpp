#include "modelmanager.h"
#include <QFile>
#include <QStringList>
#include <QDebug>


ModelManager::ModelManager(QObject *parent) : QObject(parent)
{

}

ModelManager::~ModelManager()
{
}

bool ModelManager::loadModel(const QString &filename, const QString &texturePath)
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
            // a2,b2,c2 - texture data
            // a3,b3,c3 - normal data

            QStringList facesData = line.split(" ");
            QVector<FaceData> triangleData;

            for(int i=1;i<=3;i++)
            {
                FaceData data;
                data.vertex = facesData.at(i).split("/").at(0).toInt() - 1;
                data.tCoord = facesData.at(i).split("/").at(1).toInt() - 1;
                data.norm   = facesData.at(i).split("/").at(2).toInt() - 1;
                triangleData.append(data);
            }

            m_facesBuffer.append(triangleData);

        }else if (line.left(2) == "vt") {
            QStringList lineData = line.split(" ");
            QVector2D vec(lineData.at(2).toFloat() , lineData.at(3).toFloat());
            m_textureBuffer.append(vec);
        }

    }
    // debug info
    qDebug() << "Vertex size :" << m_vertexBuffer.size() << "Faces Size" << m_facesBuffer.size();
    qDebug() << "Texture data size : " << m_textureBuffer.size();

    if(!texturePath.isEmpty())
    {
        if(!loadTexture(texturePath))
        {
            qDebug() << "cant' read texture file";
            return false;
        }
    }
    return true;


}

QVector<QVector3D> *ModelManager::vertexBuffer3D()
{
    return &m_vertexBuffer;
}


QVector<QVector<FaceData> > *ModelManager::facesBuffer()
{
    return &m_facesBuffer;
}

QVector<QVector2D> *ModelManager::textureBuffer()
{
    return &m_textureBuffer;
}

QColor ModelManager::diffuseColor(const QVector2D &coord)
{

    TGAColor color = m_tData.get(coord.x(),coord.y());


    QColor trColor = QColor(color[2],color[1],color[0]);
    return trColor;
}

QVector2D ModelManager::uvCoord(int face, int nvert)
{
    int id = m_facesBuffer.at(face).at(nvert).tCoord;
    QVector2D vec( m_textureBuffer.at(id).x() * m_tData.get_width(), m_textureBuffer.at(id).y() * m_tData.get_height()  );
    vec.setX( (int) vec.x() );
    vec.setY( (int)vec.y()  );

    return vec;
}

bool ModelManager::loadTexture(const QString &path)
{
    bool isOk =  m_tData.read_tga_file(path.toStdString().c_str());
    if(isOk ) m_tData.flip_vertically();
    return isOk;
}




QString ModelManager::errorString()
{
    return m_error;
}

