#ifndef COLORCREATOR_H
#define COLORCREATOR_H

#include <qbrush.h>
#include <qdatetime.h>
#include <qrandom.h>

class ColorCreator
{
public:
    static QBrush getColor(int id)
    {
        static QRandomGenerator randGen = QRandomGenerator(QDateTime::currentMSecsSinceEpoch());
        static QMap<int, QBrush> colors;
        if (!colors.contains(id)) {
            QBrush brush = QBrush(QColor(randGen.generate() % 255,
                                         randGen.generate() % 255,
                                         randGen.generate() % 255));
            colors.insert(id, brush);
        }
        return colors[id];
    }
};

#endif // COLORCREATOR_H
