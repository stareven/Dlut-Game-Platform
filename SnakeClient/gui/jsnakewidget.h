#ifndef JSNAKEWIDGET_H
#define JSNAKEWIDGET_H

#include <QWidget>

#include "global/jglobal.h"

namespace Ui {
    class JSnakeWidget;
}

class JSnakeGame;
class QLCDNumber;
class JSnakeSocket;

class JSnakeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JSnakeWidget(QWidget *parent = 0);
    ~JSnakeWidget();

protected:
    void paintEvent(QPaintEvent * event );
    void keyPressEvent(QKeyEvent *);
private:
    Ui::JSnakeWidget *ui;
    QLCDNumber *m_lcds[4][2];
	JSnakeGame* m_game;
	JSnakeSocket* m_socket;
	JID m_roomId;
protected slots:
//    void moveOn();
private slots:
	void om_socket_rcvEnterRoom(JID roomId,JID userId);
	void om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist);
};

#endif // JSNAKEWIDGET_H
