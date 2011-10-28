#ifndef JMAINSERVER_H
#define JMAINSERVER_H

#include <Socket/JServerBase>

class JMainServer : public JServerBase
{
    Q_OBJECT
public:
    explicit JMainServer(QObject *parent = 0);
};

#endif // JMAINSERVER_H
