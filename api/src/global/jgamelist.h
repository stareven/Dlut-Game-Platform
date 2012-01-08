#ifndef JGAMELIST_H
#define JGAMELIST_H

#include "jserializabledata.h"

#include <QMap>

/*!
    \file jgamelist.h
    \ingroup global
    \brief 定义了 JGameList 类
*/

class JGameList : public JSerializableData , public QMap<JID,QString>
{
public:
    JGameList();
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;
};

#endif // JGAMELIST_H
