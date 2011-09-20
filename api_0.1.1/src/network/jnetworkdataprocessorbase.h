#ifndef JNETWORKDATAPROCESSORBASE_H
#define JNETWORKDATAPROCESSORBASE_H

class QByteArray;

class JNetworkDataProcessorBase
{
public:
    JNetworkDataProcessorBase ();
    virtual void process(const QByteArray& data);
};

#endif // JNETWORKDATAPROCESSORBASE_H

