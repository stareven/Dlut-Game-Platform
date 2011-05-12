#ifndef JSNAKEWIDGET_H
#define JSNAKEWIDGET_H

#include <QWidget>

namespace Ui {
    class JSnakeWidget;
}

class JSnakeGame;
class QLCDNumber;

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
protected slots:
    void moveOn();
};

#endif // JSNAKEWIDGET_H
