#ifndef JSNAKEGAME_H
#define JSNAKEGAME_H

#include "../SnakeCommon/jsnake.h"

const int NUM_SNAKE=4;
const int MAXX=30;
const int MAXY=20;

const int Elapse=250;

const int NUM_FULL_LIFE=5;

class JSnakeGame
{
public:
	JSnakeGame();
	void resetSnake(int num=-1);
	void clearSnake(int num=-1);
	void resetLifeScore(int num=-1);
	void clearLifeScore(int num=-1);
    void turn(JSnake::EDire dire,int num);
	void growLonger(int num);
    const JSnake& getSnakes(int num)const;
    const QPoint& getBean()const;
private:
    JSnake m_snakes[NUM_SNAKE];
    QPoint m_bean;
public:

	// 0bit ~ (NUM_SNAKE-1)bit snake collision
	// (NUM_SNAKE)bit bean collision
	// (NUM_SNAKE+1)bit ~ (NUM_SNAKE+2)bit bean collision snake number
	qint16 getMoveOnCollision()const;

	void moveOn(int num);

	static bool isSnakeCollision(int num,qint16 bit);
	static bool isBeanCollision(qint16 bit);
	static int getBeanCollitionSnakeNumber(qint16 bit);

	void setBean(const QPoint&);

	// decrease and clear;
	void decreaseLife(int num);
	void increaseScore(int num);
private:
    int m_life[NUM_SNAKE];
    int m_score[NUM_SNAKE];
public:
    int getLife(int num)const;
    int getScore(int num)const;
};

#endif // JSNAKEGAME_H
