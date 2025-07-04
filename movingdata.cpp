#include "movingdata.h"
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include "colorcreator.h"
#include <qtimeline.h>

MovingData::MovingData()
{
    resize(width, hight);
}

void MovingData::moveTo(int id_from, int id_to, QString data, QPointF start, QPointF end)
{
    _from = id_from;
    _to = id_to;
    _data = data;

    auto data_content = data.split('_');
    QString name_color = ColorCreator::getColor(data_content.at(0).toInt()).color().name();
    this->setStyleSheet(QString("background: %1;").arg(name_color));

    //начало анимации движения и привязывание к слоту окончание этой анимации
    qreal line_length = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
    int time = line_length * 10;

    QTimeLine *timer = new QTimeLine(time, this);
    QPropertyAnimation *animation = new QPropertyAnimation(timer);
    animation->setDuration(time);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setTargetObject(this);
    animation->setPropertyName("pos");
    animation->setStartValue(QPoint(start.x(), start.y()));
    animation->setEndValue(QPoint(end.x(), end.y()));

    connect(animation, SIGNAL(finished()), this, SLOT(moveFinished()));

    animation->start();
}

QGraphicsProxyWidget *MovingData::paintAtScene(QGraphicsScene *scene, qreal angle)
{
    QGraphicsProxyWidget *w = scene->addWidget(this);
    w->setRotation(angle);
    return w;
}

void MovingData::moveFinished()
{
    emit moved(_from, _to, _data);
    this->deleteLater();
}
