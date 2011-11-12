#ifndef JDLGLOGIN_H
#define JDLGLOGIN_H

#include <QDialog>

#include "settings/jsettinglogin.h"

#include <Global/Global>

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
	JRequestLogin *m_rqslogin;

private slots:
	void on_btn_register_clicked();
 void on_cb_role_currentIndexChanged(int index);
	void on_edt_passwd_editingFinished();
    void on_edt_username_editingFinished();
signals:
    void autoLogin();
};

#endif // JDLGLOGIN_H
