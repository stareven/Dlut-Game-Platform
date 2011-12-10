#ifndef JGAMECLIENTARGUMENTANALYSER_H
#define JGAMECLIENTARGUMENTANALYSER_H

#include "../global/jglobal.h"
#include "../global/shost.h"

class QStringList;

class JGameClientArgumentAnalyser
{
public:
    static JGameClientArgumentAnalyser* getInstance();
    void processArgument(const QStringList& arguments);
    JID getUserId()const;
    const QByteArray& getLoginHashCode()const;
    const SHost& getMainServer()const;
    const SHost& getGameServer()const;
private:
    JGameClientArgumentAnalyser();
    JID m_userId;
    QByteArray m_loginhashcode;
    SHost m_mainserver;
    SHost m_gameserver;
};

#endif // JGAMECLIENTARGUMENTANALYSER_H
