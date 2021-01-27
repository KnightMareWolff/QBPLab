#ifndef QBP_SWDEBUGMASK_H
#define QBP_SWDEBUGMASK_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

class CQBPSWDebugMask : public QGraphicsItem
{
public:
     CQBPSWDebugMask(CQBPSWDebugGraph *graphWidget);

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
     QRectF boundingRect() const override;

     bool advancePosition();

     void stepMove(int Direction);

private:
    QVector<QRectF>          grid    ;
    QRectF                   bound   ;
    QPointF                  newPos  ;
    CQBPSWDebugGraph        *graph   ;
    uint                     size    ;
    uint                     step    ;
    uint                     qtdnodes;
};

#endif // QBP_SWDEBUGMASK_H
