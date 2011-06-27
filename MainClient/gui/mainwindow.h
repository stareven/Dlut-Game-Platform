#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "global/jglobal.h"

namespace Ui {
    class MainWindow;
}

class JRequestGameInfo;
class JRequestUserInfo;
class JRequestPort;
class QListWidgetItem;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void showEvent ( QShowEvent * event );

private:
    Ui::MainWindow *ui;

private slots:
//	void on_btn_download_run_clicked();
//	void on_btn_get_servers_clicked();
	void on_btn_start_game_clicked();
 void on_list_game_itemClicked(QListWidgetItem* item);
    void on_btn_refresh_list_clicked();
	void on_gameinfosrv_gameListReady();
    void on_gameinfosrv_gameInfoReady(JID gameid);
private:
    JRequestGameInfo* m_gis;
	JRequestUserInfo* m_requserinfo;
	JRequestPort* m_reqport;
	JID m_currentId;
};

#endif // MAINWINDOW_H
