#ifndef JVERSION_H
#define JVERSION_H

#include "globalapi_global.h"

class GLOBALAPISHARED_EXPORT JVersion
{
public:
	explicit JVersion(quint32 data=0xFFFFFFFF);
	bool isNull()const;
	bool operator<(const JVersion&)const;
	bool operator>(const JVersion&)const;
	bool operator==(const JVersion&)const;
	bool operator!=(const JVersion&)const;
	quint32 getData()const;
private:
	bool isLowerThan(const JVersion&)const;
	bool isHigherThan(const JVersion&)const;
	
private:
	quint32 m_data;
	friend QDataStream& operator<<(QDataStream& stream,const JVersion& ver);
	friend QDataStream& operator>>(QDataStream& stream,JVersion& ver);
};

GLOBALAPISHARED_EXPORT QDataStream& operator<<(QDataStream& stream,const JVersion& ver);
GLOBALAPISHARED_EXPORT QDataStream& operator>>(QDataStream& stream,JVersion& ver);

#endif
