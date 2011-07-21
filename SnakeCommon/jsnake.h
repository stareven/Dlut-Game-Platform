#ifndef JSNAKE_H
#define JSNAKE_H

#include <QPoint>
#include <QLinkedList>

class JSnake
{
public:
    JSnake();
    enum EDire{ED_UP,ED_RIGHT,ED_DOWN,ED_LEFT,ED_NONE};
    static EDire getOppsiteDire(EDire dire);
    JSnake(const QPoint& head,EDire dire);
    void reset(const QPoint& head,EDire dire);
    void clear();
    void turn(EDire);
    const QPoint& getHead()const;
    const QPoint& getHeadNext()const;
    void moveOn();
    void growLonger();
private:
    QPoint m_head;
    EDire m_moveDire;
    QLinkedList<EDire> m_body;

    //buffer
    QPoint m_headNext;
    void updateHeadNext();
public:
    class const_iterator;
    friend class const_iterator;
    class const_iterator
    {
        QLinkedList<EDire>::const_iterator m_it;
        QPoint m_pt;
        const_iterator(const QLinkedList<EDire>::const_iterator& it,const QPoint& pt=QPoint());
    public:
        const_iterator();

        const_iterator& operator++();
        const QPoint& getPoint();
        bool operator!=(const const_iterator& other)const;
        friend class JSnake;
    };
    const_iterator begin()const;
    const_iterator end()const;
};

#endif // JSNAKE_H
