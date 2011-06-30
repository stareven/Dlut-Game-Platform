#ifndef JHALLWIDGET_H
#define JHALLWIDGET_H

#include <QWidget>

namespace Ui {
    class JHallWidget;
}

class JHallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JHallWidget(QWidget *parent = 0);
    ~JHallWidget();

private:
    Ui::JHallWidget *ui;
};

#endif // JHALLWIDGET_H
