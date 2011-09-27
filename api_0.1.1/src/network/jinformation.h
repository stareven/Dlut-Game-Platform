#ifndef JINFORMATION_H
#define JINFORMATION_H

#include <QtGlobal>
#include <QByteArray>

namespace NetworkData{
	class JInformation
	{
	public:
		JInformation();
	private:
		qint32 m_head;
		uint m_time_t;
		QByteArray m_data;
	};
}

#endif // JINFORMATION_H
