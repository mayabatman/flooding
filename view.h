#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "graphicnode.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

    // protected:
    //     void mousePressEvent(QMouseEvent *event);

public slots:
    void gotDataMoved(int id_from, int id_to, QString data);

private:
    const int nodeLines = 5;
    const int nodeInLine = 5;

    int currentId = 0;

    QGraphicsScene *scene;
    QMap<int, GraphicNode *> nodes;

    void AddNode(QPoint point);

    void ConnectNodes(int first, int second);

public:
    void stackBeforeNodes(int id_first, int id_second, QGraphicsProxyWidget *moving_widget);
};

#endif // VIEW_H
