#ifndef JHALLWIDGET_H
#define JHALLWIDGET_H

#include <QWidget>

namespace Ui {
    class JHallWidget;
}

#include "global/jglobal.h"
class JSnakeSocket;

class JHallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JHallWidget(QWidget *parent = 0);
    ~JHallWidget();

private:
    Ui::JHallWidget *ui;
	JSnakeSocket *m_socket;
private slots:
	void on_btn_refresh_clicked();
	void on_socket_rcvHello(JCode code);
	void on_socket_rcvUserlist(JID roomId,const QList<JID>& userlist);
};

#endif // JHALLWIDGET_H
