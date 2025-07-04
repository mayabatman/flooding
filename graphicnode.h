#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsEllipseItem>
#include "bridge.h"

class GraphicNode : public QGraphicsEllipseItem
{
public:
    GraphicNode(int id, QPoint pos, QGraphicsItem *parent = nullptr);

private:
    const int radius = 13;
    QBrush brush = QBrush(QColor(255, 128, 128));

    int _id;
    QMap<int, Bridge *> bridges;
    int counter = 0;
    QStringList data_got;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void clicked();

public:
    void gotData(int from, QString data);

    void addBridge(int id_to, Bridge *bridge);

    bool connectedTo(int id);
};

#endif // GRAPHICNODE_H
