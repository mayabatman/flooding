#include "view.h"
#include <QGraphicsItemAnimation>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QObject>
#include <QRandomGenerator>
#include <QTime>
#include <QTimeLine>
#include <qgraphicsproxywidget.h>

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);

    // node_left = new GraphicNode(-50, 0, ActorSize, ActorSize);
    // node_right = new GraphicNode(50, 0, ActorSize, ActorSize);
    // QGraphicsRectItem *item = new QGraphicsRectItem(-50, 0 - 4, 100, 8);
    // scene->addItem(item);
    // scene->addItem(node_left);
    // scene->addItem(node_right);
    // node_left->setBrush(QBrush(QColor(255, 128, 128)));
    // node_right->setBrush(QBrush(QColor(255, 128, 128)));
    QPoint tmp;
    for (int y = 0; y < nodeLines * 100; y += 100) {
        for (int x = 0; x < nodeInLine * 100; x += 100) {
            tmp = QPoint(x, y);
            AddNode(tmp);
        }
    }

    // AddNode(QPoint(-50, -50));
    // AddNode(QPoint(50, -50));
    // AddNode(QPoint(-50, 50));
    // AddNode(QPoint(50, 50));

    QRandomGenerator randGen = QRandomGenerator(QDateTime::currentMSecsSinceEpoch());
    for (int i = 0; i < nodeInLine * nodeLines; i++) {
        bool create = randGen.generate() % 2;
        if (create && i < nodeInLine * nodeLines - 1 && i % nodeInLine != nodeInLine - 1) {
            ConnectNodes(i, i + 1);
        }
        create = randGen.generate() % 2;
        if (create && i < nodeInLine * nodeLines - nodeInLine) {
            ConnectNodes(i, i + nodeInLine);
        }
        create = randGen.generate() % 2;
        if (create && i % nodeInLine % 5 != nodeInLine - 1
            && i < nodeInLine * nodeLines - nodeInLine) {
            ConnectNodes(i, i + nodeInLine + 1);
        }
        create = randGen.generate() % 2;
        if (create && i % nodeInLine != 0 && i < nodeInLine * nodeLines - nodeInLine) {
            ConnectNodes(i, i + nodeInLine - 1);
        }
    }
}
// void View::leftClicked()
// {
//     QGraphicsRectItem *item = new QGraphicsRectItem(-50 - ActorSize / 2, -5, ActorSize, 10);
//     scene->addItem(item);
//     item->stackBefore(node_left);
//     item->stackBefore(node_right);
//     const QPointF eventPos = QPointF(100, 0);
//     QTimeLine *timer = new QTimeLine(AnimationPeriodMS, this);
//     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timer);
//     animation->setItem(item);
//     animation->setTimeLine(timer);
//     animation->setPosAt(1.0, eventPos);
//     timer->start();
// }

// void View::rightClicked()
// {
//     QGraphicsRectItem *item = new QGraphicsRectItem(50 - ActorSize / 2, -5, ActorSize, 10);
//     scene->addItem(item);
//     item->stackBefore(node_left);
//     item->stackBefore(node_right);
//     const QPointF eventPos = QPointF(-100, 0);
//     QTimeLine *timer = new QTimeLine(AnimationPeriodMS, this);
//     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timer);
//     animation->setItem(item);
//     animation->setTimeLine(timer);
//     animation->setPosAt(1.0, eventPos);
//     timer->start();
// }

// void View::mousePressEvent(QMouseEvent *event)
// {
//     if (event->button() == Qt::LeftButton) {
//         // QPointF point = this->mapToScene(event->pos());
//         // if (point.x() >= -50 - ActorSize / 2 && point.x() <= -50 + ActorSize / 2) {
//         //     leftClicked();
//         // } else if (point.x() >= 50 - ActorSize / 2 && point.x() <= 50 + ActorSize / 2) {
//         //     rightClicked();
//         // }
//     }
// }

void View::gotDataMoved(int id_from, int id_to, QString data)
{
    nodes[id_to]->gotData(id_from, data);
}

void View::AddNode(QPoint point)
{
    GraphicNode *node = new GraphicNode(currentId, point);
    scene->addItem(node);

    nodes.insert(currentId, node);
    currentId++;
}

void View::ConnectNodes(int first, int second)
{
    if (first != second && !nodes[first]->connectedTo(second)) {
        QPointF pos_first = nodes[first]->scenePos();
        QPointF pos_second = nodes[second]->scenePos();

        Bridge *bridge = new Bridge(pos_first.x(),
                                    pos_first.y(),
                                    pos_second.x(),
                                    pos_second.y(),
                                    this);
        bridge->setIds(first, second);

        scene->addItem(bridge);
        bridge->stackBefore(nodes[first]);
        bridge->stackBefore(nodes[second]);

        nodes[first]->addBridge(second, bridge);
        nodes[second]->addBridge(first, bridge);
    }
}

void View::stackBeforeNodes(int id_first, int id_second, QGraphicsProxyWidget *moving_widget)
{
    moving_widget->stackBefore(nodes[id_first]);
    moving_widget->stackBefore(nodes[id_second]);
}
