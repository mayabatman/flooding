#ifndef BRIDGE_H
#define BRIDGE_H

#include <QGraphicsLineItem>
#include <QPen>
#include <qgraphicsview.h>

class Bridge : public QGraphicsLineItem
{
public:
    Bridge(qreal x_from, qreal y_from, qreal x_to, qreal y_to, QGraphicsView *view);

    void setIds(int first, int second);

private:
    const qreal width = 8;
    const int dif = 13;

    int id_1;
    int id_2;

    QGraphicsView *parentView;

public:
    void moveFrom(int id, QString data);
};

#endif // BRIDGE_H
