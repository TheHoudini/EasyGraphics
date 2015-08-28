#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QVector3D>
#include <QVector>


class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject *parent = 0);

    // Load model from @filename , read all data(like vertex,faces and other)
    // and write data to buffer
    // return true on success, false on error
    bool loadModel(const QString &filename);

    // data getters
    QVector<QVector3D> *vertexBuffer();
    QVector<QVector<int>> *facesBuffer();

    // return last ModelManager error;
    QString errorString();

signals:

public slots:

private:
    QVector<QVector3D> m_vertexBuffer;
    QVector< QVector<int> > m_facesBuffer;

    QString m_error;
};

#endif // MODELMANAGER_H
