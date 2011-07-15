#ifndef JHALLWIDGET_H
#define JHALLWIDGET_H

#include <QWidget>

namespace Ui {
    class JHallWidget;
}

#include "global/jglobal.h"
class JSnakeSocket;
class JRequestUserInfo;
class JRequestPort;
class JRoomListModel;
namespace Snake
{
	class JRoom;
}

class JHallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JHallWidget(QWidget *parent = 0);
    ~JHallWidget();

private:
    Ui::JHallWidget *ui;
	JSnakeSocket *m_socket;
	JRequestUserInfo *m_reqUserInfo;
	JRequestPort *m_reqPort;
	JRoomListModel *m_roomlistmodel;
private slots:
	void on_btn_refresh_room_clicked();
	void on_btn_enter_room_clicked();
	void on_btn_create_room_clicked();
	void on_btn_refresh_userlist_clicked();
	void om_socket_rcvHello(JCode code);
	void om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist);
	void om_socket_rcvAddRoom(const Snake::JRoom&);
	void om_socket_rcvEnterRoom(JID roomId,JID userId);
	void om_socket_rcvEscapeRoom(JID roomId,JID userId);
signals:
	void enterGame(int);
};

#endif // JHALLWIDGET_H
