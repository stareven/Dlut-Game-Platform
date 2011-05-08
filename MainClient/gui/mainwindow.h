#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "jglobal.h"

namespace Ui {
    class MainWindow;
}

class JGameInfoService;
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
    void on_list_game_itemClicked(QListWidgetItem* item);
    void on_btn_refresh_list_clicked();
    void on_gameinfosrv_nameListReady();
    void on_gameinfosrv_gameInfoReady(JID gameid);
private:
    JGameInfoService* m_gis;
};

#endif // MAINWINDOW_H
