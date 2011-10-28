#ifndef JLOGINHASHCODERECORDER_H
#define JLOGINHASHCODERECORDER_H

#include <QByteArray>

#include "global/jglobal.h"

#include "clientapi_global.h"

class CLIENTAPISHARED_EXPORT JLoginHashCodeRecorder
{
public:
    void set(const QByteArray& code,JID userId);
    void setCode(const QByteArray& code);
    void setUserId(JID userId);
    const QByteArray& getCode()const;
    JID getUserId()const;
private:
    static QByteArray s_code;
    static JID s_userId;
};

#endif // JLOGINHASHCODERECORDER_H
