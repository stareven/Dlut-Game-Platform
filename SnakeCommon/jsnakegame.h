#ifndef JSNAKEGAME_H
#define JSNAKEGAME_H

#include "../SnakeCommon/jsnake.h"

const int NUM_SNAKE=4;
const int MAXX=30;
const int MAXY=20;

class JSnakeGame
{
public:
    explicit JSnakeGame();
    void reset(int num=-1);
    void turn(JSnake::EDire dire,int num);
    const JSnake& getSnakes(int num)const;
    const QPoint& getBean()const;
private:
    JSnake m_snakes[NUM_SNAKE];
    QPoint m_bean;
public:
    void moveOn();
protected:
    void createBean(const QPoint& pt=QPoint());
// life ans score
private:
    int m_life[NUM_SNAKE];
    int m_score[NUM_SNAKE];
public:
    int getLife(int num)const;
    int getScore(int num)const;
};

#endif // JSNAKEGAME_H
