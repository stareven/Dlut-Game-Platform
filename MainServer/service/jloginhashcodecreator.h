#ifndef JLOGINHASHCODECREATOR_H
#define JLOGINHASHCODECREATOR_H

#include <Global/Global>

class JLoginHashCodeCreator
{
public:
    JLoginHashCodeCreator();
	void setUserId(JID userId);
	QByteArray createLoginHashCode();
private:
	JID m_userId;
};

#endif // JLOGINHASHCODECREATOR_H
