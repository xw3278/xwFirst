#ifndef DATAFILE_H
#define DATAFILE_H

#include <QObject>
#include <vector>
#include <QString>
#include <QFile>
#include <QUdpSocket>
#include <QHostAddress>

typedef struct
{
    QString qTime;                  //time
    float dDepth;                   //depth
    float dLength;
    float dLongitude;               //Longitude
    float dlatitude;                //latitude
    int   ix;
    int   iy;

}stNodeInfo;

class DataFile : public QObject
{
    Q_OBJECT
public:
    static DataFile* instance(void);
    bool             readData(QString filePath);
    QVector<QString> getUdpDataFromROV();
signals:

public slots:
    void dataReceived();
private:
    explicit         DataFile(QObject *parent = FP_ZERO);

private:
    std::vector<stNodeInfo> m_vecNodes;
    QFile* m_pFile = FP_ZERO;


    int m_iport;
    QUdpSocket *m_pUdpSocket;
    QVector<QString> m_vecMsgs;
};

#endif // DATAFILE_H
