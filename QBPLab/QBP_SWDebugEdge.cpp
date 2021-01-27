#include "QBP_SWDebugEdge.h"
#include "QBP_SWDebugNode.h"

#include <qmath.h>
#include <QPainter>

CQBPSWDebugEdge::CQBPSWDebugEdge(CQBPSWDebugNode *sourceNode, CQBPSWDebugNode *destNode)
    : arrowSize(10)
{
    setZValue(2);
    //setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}


CQBPSWDebugNode *CQBPSWDebugEdge::sourceNode() const
{
    return source;
}

CQBPSWDebugNode *CQBPSWDebugEdge::destNode() const
{
    return dest;
}

void CQBPSWDebugEdge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 20, 20), mapFromItem(dest, 20, 20));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 2) / length, (line.dy() * 2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF CQBPSWDebugEdge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void CQBPSWDebugEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::darkBlue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrow
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
