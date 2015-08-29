#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <tgaimage.h>
#include <QColor>


struct FaceData {
    int vertex;
    int tCoord;
    int norm;

};


class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject *parent = 0);
    ~ModelManager();

    // Load model from @filename , read all data(like vertex,faces and other)
    // and write data to buffer
    // return true on success, false on error
    bool loadModel(const QString &filename,const QString &texturePath = "");

    // data getters
    QVector<QVector3D> *vertexBuffer3D();
    QVector<QVector<FaceData>> *facesBuffer();
    QVector<QVector2D> *textureBuffer();

    QColor diffuseColor(const QVector2D &coord);
    QVector2D uvCoord(int face, int nvert);

    bool loadTexture(const QString &path);

    // return last ModelManager error;
    QString errorString();

signals:

public slots:

private:
    QVector<QVector3D> m_vertexBuffer;
    QVector<QVector<FaceData> > m_facesBuffer;
    QVector<QVector2D > m_textureBuffer;

    TGAImage m_tData;
    QString m_error;
};

#endif // MODELMANAGER_H
