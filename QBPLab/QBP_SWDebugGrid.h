#ifndef QBP_SWDEBUGGRID_H
#define QBP_SWDEBUGGRID_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

class CQBPSWDebugGrid : public QGraphicsItem
{
public:
     CQBPSWDebugGrid(CQBPSWDebugGraph *graphWidget);
     CQBPSWDebugGrid(CQBPSWDebugGraph *graphWidget, uint pQBPSize);

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
     QRectF boundingRect() const override;

     uint getSize(){return size;}
     uint getStep(){return step;}
     uint getNumNodes(){return qtdnodes;}

     bool resize(int pQBP_Size);

private:
    QVector<QRectF>          grid    ;
    QRectF                   bound   ;
    CQBPSWDebugGraph        *graph   ;
    uint                     size    ;
    uint                     step    ;
    uint                     qtdnodes;

};

#endif // QBP_SWDEBUGGRID_H
