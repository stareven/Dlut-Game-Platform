#ifndef JGAMELIST_H
#define JGAMELIST_H

#include "jserializabledata.h"

#include <QMap>

class JGameList : public JSerializableData , public QMap<JID,QString>
{
public:
    JGameList();
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;
private:
	//QMap<JID,QString> m_list;
};

#endif // JGAMELIST_H
