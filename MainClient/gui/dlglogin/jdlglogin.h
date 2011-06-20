#ifndef JDLGLOGIN_H
#define JDLGLOGIN_H

#include <QDialog>

#include "settings/jsettinglogin.h"
#include "global/jglobal.h"

namespace Ui {
    class JDlgLogin;
}

#include <QAbstractSocket>

class JRequestLogin;

class JDlgLogin : public QDialog {
    Q_OBJECT
public:
    JDlgLogin(QWidget *parent = 0);
    ~JDlgLogin();
protected:
    void changeEvent(QEvent *e);
protected slots:
    void accept();
    void error(QAbstractSocket::SocketError);
protected:

private:
    Ui::JDlgLogin *ui;
    JSettingLogin m_remember;

    //bool is_accepted;
	JRequestLogin *m_rqslogin;

private slots:
    void on_edt_passwd_editingFinished();
    void on_edt_username_editingFinished();
//    void on_cb_server_selectUpdate();
//    void on_loginsrv_loginMsg(JCode);
signals:
    void autoLogin();
private:
//    void outputLoginMsg(const char*);
};

#endif // JDLGLOGIN_H
