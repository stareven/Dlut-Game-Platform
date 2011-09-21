#ifndef JNETWORKDATAPROCESSORBASE_H
#define JNETWORKDATAPROCESSORBASE_H

#include <QObject>

class QByteArray;

class JNetworkDataProcessorBase : public QObject
{
    Q_OBJECT
public:
    JNetworkDataProcessorBase (QObject *parent = 0)
        :QObject(parent){}
    virtual void process(const QByteArray& data)=0;
};

#endif // JNETWORKDATAPROCESSORBASE_H
