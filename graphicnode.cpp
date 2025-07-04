#include "graphicnode.h"
#include <QGraphicsSceneMouseEvent>
#include "colorcreator.h"

GraphicNode::GraphicNode(int id, QPoint pos, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent)
{
    setPos(pos);
    setRect(0, 0, radius * 2, radius * 2);
    _id = id;

    setBrush(ColorCreator::getColor(id));
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //анимация нажатия
        clicked();
    }
}
void GraphicNode::clicked()
{
    QString data = QString("%1_%2").arg(_id).arg(counter++);
    for (auto [key, value] : bridges.asKeyValueRange()) {
        value->moveFrom(_id, data);
    }
    data_got.push_back(data);
}

void GraphicNode::gotData(int from, QString data)
{
    if (!data_got.contains(data)) {
        for (auto [key, value] : bridges.asKeyValueRange()) {
            if (key != from)
                value->moveFrom(_id, data);
        }
        data_got.push_back(data);
    }
}

void GraphicNode::addBridge(int id_to, Bridge *bridge)
{
    if (!bridges.contains(id_to) && id_to != _id) {
        bridges.insert(id_to, bridge);
    }
}

bool GraphicNode::connectedTo(int id)
{
    return bridges.contains(id);
}
