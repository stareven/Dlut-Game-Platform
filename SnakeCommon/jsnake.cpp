#include "jsnake.h"

const QPoint dires[JSnake::ED_NONE+1]={
    QPoint(0,-1),
    QPoint(1,0),
    QPoint(0,1),
    QPoint(-1,0),
    QPoint(0,0)
};

JSnake::JSnake()
{
    reset(QPoint(-1,-1),ED_NONE);
}

JSnake::EDire JSnake::getOppsiteDire(EDire dire)
{
    EDire ans;
    switch(dire)
    {
    case ED_UP:
        ans=ED_DOWN;
        break;
    case ED_RIGHT:
        ans=ED_LEFT;
        break;
    case ED_DOWN:
        ans=ED_UP;
        break;
    case ED_LEFT:
        ans=ED_RIGHT;
        break;
    case ED_NONE:
        ans=ED_NONE;
        break;
    }
    return ans;
}

JSnake::JSnake(const QPoint& head,EDire dire)
{
    reset(head,dire);
}

void JSnake::reset(const QPoint& head,EDire dire)
{
    m_head=head;
    m_moveDire=dire;
    m_body.clear();
    int n=3;
    while(n--)
    {
        m_body.push_back(JSnake::ED_NONE);
    }
    m_body.push_back(JSnake::ED_NONE);
    updateHeadNext();
}

void JSnake::clear()
{
    m_head=QPoint(-1,-1);
    m_moveDire=ED_NONE;
    m_body.clear();
    updateHeadNext();
}

void JSnake::turn(EDire dire)
{
    if( dire!=m_moveDire
        && ( m_body.empty()
             || dire != m_body.front()
             )
        )
    {
        m_moveDire=dire;
        updateHeadNext();
    }
}

const QPoint& JSnake::getHead()const
{
    return m_head;
}

const QPoint& JSnake::getHeadNext()const
{
    return m_headNext;
}

void JSnake::moveOn()
{
    m_head=getHeadNext();
    QLinkedList<EDire>::Iterator it;
    for(it=m_body.end()-1;it != m_body.begin();--it)
    {
        *it=*(it-1);
    }
    if(!m_body.empty())
    {
        m_body.front()=getOppsiteDire(m_moveDire);
    }
    updateHeadNext();
}

void JSnake::growLonger()
{
    m_head=getHeadNext();
    m_body.push_front(getOppsiteDire(m_moveDire));
    updateHeadNext();
}

void JSnake::updateHeadNext()
{
    m_headNext=m_head+dires[m_moveDire];
}

JSnake::const_iterator JSnake::begin()const
{
    return JSnake::const_iterator(m_body.begin(),m_head);
}

JSnake::const_iterator JSnake::end()const
{
    return JSnake::const_iterator(m_body.end());
}

JSnake::const_iterator::const_iterator()
{
}

JSnake::const_iterator::const_iterator(const QLinkedList<EDire>::const_iterator& it,const QPoint& pt)
{
    m_it=it;
    m_pt=pt;
}

JSnake::const_iterator& JSnake::const_iterator::operator++()
{
    m_pt+=dires[*m_it];
    ++m_it;
    return *this;
}

const QPoint& JSnake::const_iterator::getPoint()
{
    return m_pt;
}

bool JSnake::const_iterator::operator!=(const JSnake::const_iterator& other)const
{
    return m_it!=other.m_it;
}
