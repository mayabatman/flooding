#include "bridge.h"
#include <QGraphicsScene>
#include <QtMath>
#include "movingdata.h"
#include "view.h"

Bridge::Bridge(qreal x_from, qreal y_from, qreal x_to, qreal y_to, QGraphicsView *view)
{
    setLine(x_from + dif, y_from + dif, x_to + dif, y_to + dif);
    QPen pen;
    pen.setWidth(width);
    setPen(pen);
    parentView = view;
}

void Bridge::setIds(int first, int second)
{
    id_1 = first;
    id_2 = second;
}

void Bridge::moveFrom(int id, QString data)
{
    MovingData *moving = new MovingData();

    qreal k1 = qAbs(line().x1() - line().x2());
    qreal k2 = qAbs(line().y1() - line().y2());
    qreal angle = qAtan(k2 / k1);
    bool backword = line().x1() > line().x2();
    if (backword)
        angle = qDegreesToRadians(180) - angle;

    auto proxy = moving->paintAtScene(this->scene(), qRadiansToDegrees(angle));
    ((View *) parentView)->stackBeforeNodes(id_1, id_2, proxy);
    MovingData::connect(moving,
                        SIGNAL(moved(int, int, QString)),
                        parentView,
                        SLOT(gotDataMoved(int, int, QString)));

    qreal sin = qSin(angle);
    qreal adding = width * sin;

    QPoint start = QPoint(this->line().x1() + adding,
                          backword ? this->line().y1() + width / 2 : this->line().y1() - width / 2);
    QPoint finish = QPoint(this->line().x2() + adding,
                           backword ? this->line().y2() + width / 2 : this->line().y2() - width / 2);
    if (id == id_1)
        moving->moveTo(id_1, id_2, data, start, finish);
    else
        moving->moveTo(id_2, id_1, data, finish, start);
}
