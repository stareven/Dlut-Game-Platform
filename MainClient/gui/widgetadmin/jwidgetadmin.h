#ifndef JWIDGETADMIN_H
#define JWIDGETADMIN_H

#include <QWidget>

namespace Ui {
    class JWidgetAdmin;
}

class JWidgetAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit JWidgetAdmin(QWidget *parent = 0);
    ~JWidgetAdmin();

private:
    Ui::JWidgetAdmin *ui;

private slots:
	void on_btn_restart_mainserver_clicked();
	void on_btn_shutdown_mainserver_clicked();
};

#endif // JWIDGETADMIN_H
