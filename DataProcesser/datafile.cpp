#include "datafile.h"

static DataFile* _instance = FP_ZERO;

DataFile* DataFile::instance(void)
{
    if(FP_ZERO == _instance) {
       _instance = new DataFile();
    }
    return _instance;
}

DataFile::DataFile(QObject *parent) : QObject(parent)
{
    m_iport = 5555;
    m_pUdpSocket = new QUdpSocket(this);

    connect(m_pUdpSocket,SIGNAL(readyRead()), this, SLOT(dataReceived()));

    bool result=m_pUdpSocket->bind(m_iport);
    if(!result)
    {
        qDebug()<<"DataFile--> udp socket create error!";
        return;
    }
}

bool DataFile::readData(QString filePath)
{
    return true;
}

void DataFile::dataReceived()
{
    while(m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(datagram.data(),datagram.size());
        QString msg=datagram.data();
        m_vecMsgs.push_back(msg);

    }
}

QVector<QString> DataFile::getUdpDataFromROV()
{
    return m_vecMsgs;
}
