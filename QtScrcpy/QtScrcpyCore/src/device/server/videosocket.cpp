#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "videosocket.h"

VideoSocket::VideoSocket(QObject *parent) : QTcpSocket(parent)
{
}

VideoSocket::~VideoSocket()
{
}

qint32 VideoSocket::subThreadRecvData(quint8 *buf, qint32 bufSize)
{
    if (!buf) {
        return 0;
    }
    // this function cant call in main thread
    Q_ASSERT(QCoreApplication::instance()->thread() != QThread::currentThread());

    QThread *curThread = QThread::currentThread();
    while (bytesAvailable() < bufSize) {
        if (curThread && curThread->isInterruptionRequested()) {
            return 0;
        }
        if (state() != QAbstractSocket::ConnectedState) {
            return 0;
        }
        if (!waitForReadyRead(500)) {
            if (state() != QAbstractSocket::ConnectedState || (curThread && curThread->isInterruptionRequested())) {
                return 0;
            }
        }
    }

    // recv data
    return read((char *)buf, bufSize);
}
