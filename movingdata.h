#ifndef MOVINGDATA_H
#define MOVINGDATA_H

#include <QWidget>
#include <qgraphicsscene.h>

class MovingData : public QWidget
{
    Q_OBJECT
public:
    MovingData();

    const int hight = 12;
    const int width = 16;

    int _from;
    int _to;
    QString _data;

    void moveTo(int id_from, int id_to, QString data, QPointF start, QPointF end);

    void start();

    QGraphicsProxyWidget *paintAtScene(QGraphicsScene *scene, qreal angle);
signals:
    void moved(int id_from, int id_to, QString data);

private slots:
    void moveFinished();
};

#endif // MOVINGDATA_H
