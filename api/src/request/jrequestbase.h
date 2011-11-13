#ifndef JREQUESTBASE_H
#define JREQUESTBASE_H

#include <QObject>

class JRequestBase : public QObject
{
	Q_OBJECT
public:
	explicit JRequestBase(QObject *parent = 0);
};

#endif // JREQUESTBASE_H
