#ifndef JSNAKEGAMEONSERVER_H
#define JSNAKEGAMEONSERVER_H

#include <QObject>

#include "jsnakegame.h"

class JSnakeGame;
class QTimer;

class JSnakeGameOnServer : public QObject
{
    Q_OBJECT
public:
	explicit JSnakeGameOnServer(QObject *parent = 0);
	virtual ~JSnakeGameOnServer();
	void start(int msec);
	void setTurn(JSnake::EDire dire,int num);
private:
	JSnakeGame* m_game;
signals:
	void countDown(int n);
	void getCommand();
	void turn(JSnake::EDire dire,int num);
	void collision(int num);
	void createBean(const QPoint& pt);
	void increaseScore(int num);
	void moveOn(int num);
private:
	QTimer* m_timer;
	int m_interval_msec;
	int m_countDown;
	JSnake::EDire m_dires[NUM_SNAKE];
private slots:
	void on_timer_timeout();
};

#endif // JSNAKEGAMEONSERVER_H
