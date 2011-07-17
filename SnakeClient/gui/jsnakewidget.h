#ifndef JSNAKEWIDGET_H
#define JSNAKEWIDGET_H

#include <QWidget>

#include "global/jglobal.h"
#include "jsnake.h"

namespace Ui {
    class JSnakeWidget;
}

class JSnakeGame;
class QLCDNumber;
class QLabel;
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
	QLabel *m_lab_ready[4];
    QLCDNumber *m_lcds[4][2];
	JSnakeGame* m_game;
	JSnakeSocket* m_socket;
	JID m_roomId;
protected slots:
//    void moveOn();
signals:
	void escape(int a);
private slots:
	void on_btn_escape_clicked();
	void on_btn_ready_clicked(bool ready);
	void om_socket_rcvEnterRoom(JID roomId,JID userId);
	void om_socket_rcvEscapeRoom(JID roomId,JID userId);
	void om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist);
	void om_socket_rcvGA_Ready(bool ready,int num);
	void om_socket_rcvGA_CountDown(int sec);
	void om_socket_rcvGA_GetCommand();
	void om_socket_rcvGA_Turn(qint16 dire,int num);
	void om_socket_rcvGA_Collision(int num);
	void om_socket_rcvGA_CreateBean(const QPoint& pt);
	void om_socket_rcvGA_Increase(int num);
	void om_socket_rcvGA_MoveOn(int num);
private:
	JSnake::EDire m_command;
private:
	void updateLifeNScore();
};

#endif // JSNAKEWIDGET_H
