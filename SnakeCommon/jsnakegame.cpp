#include "jsnakegame.h"

#include <QRect>
#include <QSet>
//#include <QTime>

JSnakeGame::JSnakeGame()
{
	resetSnake();
	clearLifeScore();
}

void JSnakeGame::resetSnake(int num)
{
    const static JSnake snakes[NUM_SNAKE]={
        JSnake(QPoint(MAXX*0.2,MAXY*0.2),JSnake::ED_DOWN),
		JSnake(QPoint(MAXX*0.8,MAXY*0.8),JSnake::ED_UP),
		JSnake(QPoint(MAXX*0.2,MAXY*0.8),JSnake::ED_RIGHT),
        JSnake(QPoint(MAXX*0.8,MAXY*0.2),JSnake::ED_LEFT)
    };
    if(num<0 || num>=NUM_SNAKE)
	{
        for(int i=0;i<NUM_SNAKE;++i)
        {
			m_snakes[i]=snakes[i];
		}
	}else{
        m_snakes[num]=snakes[num];
    }
}

void JSnakeGame::clearSnake(int num)
{
	if(num<0 || num>=NUM_SNAKE)
	{
		for(int i=0;i<NUM_SNAKE;++i)
		{
			m_snakes[i].clear();
		}
	}else{
		m_snakes[num].clear();
	}
}

void JSnakeGame::resetLifeScore(int num)
{
	if(num<0 || num>=NUM_SNAKE)
	{
		for(int i=0;i<NUM_SNAKE;++i)
		{
			m_life[i]=NUM_FULL_LIFE;
			m_score[i]=0;
		}
	}else{
		m_life[num]=NUM_FULL_LIFE;
		m_score[num]=0;
	}
}

void JSnakeGame::clearLifeScore(int num)
{
	if(num<0 || num>=NUM_SNAKE)
	{
		for(int i=0;i<NUM_SNAKE;++i)
		{
			m_life[i]=0;
			m_score[i]=0;
		}
	}else{
		m_life[num]=0;
		m_score[num]=0;
	}
}

void JSnakeGame::turn(JSnake::EDire dire,int num)
{
    if(num<0 || num>=NUM_SNAKE)
    {
        return;
    }
    if(m_life[num]>0)
    {
        m_snakes[num].turn(dire);
    }
}

void JSnakeGame::growLonger(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_snakes[num].growLonger();
	}
}

const JSnake& JSnakeGame::getSnakes(int num)const
{
    if(num<0 || num>=NUM_SNAKE)
    {
        static JSnake empty;
        return empty;
    }else{
        return m_snakes[num];
    }
}

const QPoint& JSnakeGame::getBean()const
{
    return m_bean;
}

uint qHash(const QPoint& pt)
{
    return pt.x()*MAXY+pt.y();
}

qint16 JSnakeGame::getMoveOnCollision()const
{
	qint16 ret;
	ret=0;
	int i,j;
	for(i=0;i<NUM_SNAKE;++i)
	{
		if(m_life[i]<=0) continue;
		for(j=0;j<i;++j)
		{
			if(m_snakes[i].getHeadNext()==m_snakes[j].getHeadNext())
			{
				//needReset[i]=true;
				//needReset[j]=true;
				ret |= (1<<i) | (1<<j);
			}
		}
	}
	QSet<QPoint> ptset;
	for(i=0;i<NUM_SNAKE;++i)
	{
		if(m_life[i]<=0) continue;
		JSnake::const_iterator it;
		for(it=m_snakes[i].begin();it != m_snakes[i].end();++it)
		{
			ptset.insert(it.getPoint());
		}
	}
	for(i=0;i<NUM_SNAKE;++i)
	{
		if(m_life[i]<=0) continue;
		const static QRect region(0,0,MAXX,MAXY);
		if( !( ret & (1<<i))
			&& (ptset.contains(m_snakes[i].getHeadNext())
				|| !region.contains(m_snakes[i].getHeadNext())
				)
			)
		{
			//needReset[i]=true;
			ret |= (1<<i);
		}
	}
	for(i=0;i<NUM_SNAKE;++i)
	{
		if(m_life[i]<=0) continue;
		//if( !needReset[i] )
		if( ! ( ret & (1<<i)))
		{
			if(m_snakes[i].getHeadNext()==m_bean)
			{
//				m_snakes[i].growLonger();
//				++m_score[i];
//				createBean();
				ret |= ( 1<<NUM_SNAKE);
				ret |= ( i<<(NUM_SNAKE+1));
			}
		}
//		else{
//			--m_life[i];
//			if(m_life[i]<=0)
//			{
//				m_snakes[i].clear();
//			}else{
//				reset(i);
//			}
//		}
	}
	return ret;
}

void JSnakeGame::moveOn(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_snakes[num].moveOn();
	}
}

bool JSnakeGame::isSnakeCollision(int num,qint16 bit)
{
	return (bit & (1<<num));
}

bool JSnakeGame::isBeanCollision(qint16 bit)
{
	return (bit & (1<<NUM_SNAKE));
}

int JSnakeGame::getBeanCollitionSnakeNumber(qint16 bit)
{
	return (bit>>(NUM_SNAKE+1))%NUM_SNAKE;
}

void JSnakeGame::setBean(const QPoint& pt)
{
	m_bean=pt;
}

// decrease and clear;
void JSnakeGame::decreaseLife(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		--m_life[num];
		if(m_life[num]<=0)
		{
			m_snakes[num].clear();
		}
	}
}

void JSnakeGame::increaseScore(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		++m_score[num];
	}
}

//void JSnakeGame::moveOn()
//{
//    int i,j;
//    bool needReset[NUM_SNAKE];
//    for(i=0;i<NUM_SNAKE;++i)
//    {
//        needReset[i]=false;
//    }
//    for(i=0;i<NUM_SNAKE;++i)
//    {
//        if(m_life[i]<=0) continue;
//        for(j=0;j<i;++j)
//        {
//            if(m_snakes[i].getHeadNext()==m_snakes[j].getHeadNext())
//            {
//                needReset[i]=true;
//                needReset[j]=true;
//            }
//        }
//    }
//    QSet<QPoint> ptset;
//    for(i=0;i<NUM_SNAKE;++i)
//    {
//        if(m_life[i]<=0) continue;
//        JSnake::const_iterator it;
//        for(it=m_snakes[i].begin();it != m_snakes[i].end();++it)
//        {
//            ptset.insert(it.getPoint());
//        }
//    }
//    for(i=0;i<NUM_SNAKE;++i)
//    {
//        if(m_life[i]<=0) continue;
//        const static QRect region(0,0,MAXX,MAXY);
//        if( !needReset[i]
//            && (ptset.contains(m_snakes[i].getHeadNext())
//                || !region.contains(m_snakes[i].getHeadNext())
//                )
//            )
//        {
//            needReset[i]=true;
//        }
//    }
//    for(i=0;i<NUM_SNAKE;++i)
//    {
//        if(m_life[i]<=0) continue;
//        if( !needReset[i] )
//        {
//            if(m_snakes[i].getHeadNext()==m_bean)
//            {
//                m_snakes[i].growLonger();
//                ++m_score[i];
//                createBean();
//            }else{
//                m_snakes[i].moveOn();
//            }
//        }else{
//            --m_life[i];
//            if(m_life[i]<=0)
//            {
//                m_snakes[i].clear();
//            }else{
//                reset(i);
//            }
//        }
//	}
//}

//void JSnakeGame::createBean(const QPoint& pt)
//{
//    static bool first=true;
//    if(first){
//        first=false;
//        qsrand(QTime::currentTime().msecsTo(QTime()));
//    }
//    if(pt.isNull())
//    {
//        m_bean.setX(qrand()%MAXX);
//        m_bean.setY(qrand()%MAXY);
//    }else{
//        m_bean=pt;
//    }
//}

int JSnakeGame::getLife(int num)const
{
    if(num<0 || num>NUM_SNAKE)
    {
        return -1;
    }else{
        return m_life[num];
    }
}

int JSnakeGame::getScore(int num)const
{
    if(num<0 || num>NUM_SNAKE)
    {
        return -1;
    }else{
        return m_score[num];
    }
}
