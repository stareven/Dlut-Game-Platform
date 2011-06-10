#ifndef JVERSION_H
#define JVERSION_H

#include "jglobal.h"

class JVersion
{
public:
	JVersion();
	explicit JVersion(qint32 data);
	bool isNull()const;//-1 is NULL
	bool operator<(const JVersion&)const;
	bool operator>(const JVersion&)const;
	qint32 getData()const;
private:
	bool isLowerThan(const JVersion&)const;
	bool isHigherThan(const JVersion&)const;
	
private:
	qint32 m_data;
	friend QDataStream& operator<<(QDataStream& stream,const JVersion& ver);
	friend QDataStream& operator>>(QDataStream& stream,JVersion& ver);
};

#endif
