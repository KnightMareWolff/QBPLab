#ifndef QBP_SWDEBUGEDGE_H
#define QBP_SWDEBUGEDGE_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>

class CQBPSWDebugNode;

class CQBPSWDebugEdge : public QGraphicsItem
{
public:
    CQBPSWDebugEdge(CQBPSWDebugNode *sourceNode, CQBPSWDebugNode *destNode);

    CQBPSWDebugNode *sourceNode() const;
    CQBPSWDebugNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    CQBPSWDebugNode *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // QBP_SWDEBUGEDGE_H
