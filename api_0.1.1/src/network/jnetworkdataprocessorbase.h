#ifndef JNETWORKDATAPROCESSORBASE_H
#define JNETWORKDATAPROCESSORBASE_H

#include <QObject>

#include "../global/jglobal.h"

class QByteArray;

class JNetworkDataProcessorBase : public QObject
{
    Q_OBJECT
public:
    JNetworkDataProcessorBase (QObject *parent = 0)
        :QObject(parent){}
    virtual void process(const QByteArray& data)=0;
    virtual JID getProcessorId()const=0;

    enum EProcessorId{
        EPI_LOGIN,
    };
};

#endif // JNETWORKDATAPROCESSORBASE_H
