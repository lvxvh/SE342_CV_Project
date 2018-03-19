#ifndef CROPRECT_H
#define CROPRECT_H
#include <QPoint>
#include <QPainter>

class CropRect
{
public:
    CropRect(){}
    ~CropRect(){}
    void setStart(QPoint s)
    {
        start = s;
    }

    void setEnd(QPoint e)
    {
        end = e;
    }

    QPoint startPoint() const
    {
        return start;
    }

    QPoint endPoint() const
    {
        return end;
    }
    void reset()
    {
        QPoint P(0,0);
        start = P;
        end = P;
    }

    QSize size() const
    {
        return QSize(width(), height());
    }

    int height() const
    {
        return qAbs(startPoint().y() - endPoint().y());
    }

    int width() const
    {
        return qAbs(startPoint().x() - endPoint().x());
    }

    QRect getRect()
    {
        if (start.x() < end.x())
            {
                if (start.y() < end.y())
                {
                    //start point in the top to the end point.
                    return QRect(start.x(), start.y(), width(), height());
                }
                else{
                    //start point in the bottom to the end point.
                    return QRect(start.x(), end.y(), width(), height());
                }
            }
            else
            {
                if (start.y() > end.y())
                {
                    return QRect(end.x(), end.y(), width(), height());

                }
                else{
                    return QRect(end.x(), start.y(), width(), height());

                }
            }
    }

private:
    QPoint start;
    QPoint end;
};

#endif // CROPRECT_H
