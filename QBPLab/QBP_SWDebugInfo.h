#ifndef QBP_SWDEBUGINFO_H
#define QBP_SWDEBUGINFO_H

#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

class CQBPSWDebugInfo : public QGraphicsItem
{
public:
    CQBPSWDebugInfo(CQBPSWDebugGraph *graphWidget);
    CQBPSWDebugInfo(CQBPSWDebugGraph *graphWidget,int  piQBPTopo ,int piQBPDiagonal ,int piQBPLado,int piQBPMatch,int piQBPMissMatch,int piQBPGap);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    bool advancePosition();
    void stepMove(int Direction);

    void setDebugInfo(int  piQBPTopo ,int piQBPDiagonal ,int piQBPLado,int piQBPMatch,int piQBPMissMatch,int piQBPGap);

private:
   QRectF                   rect    ;
   CQBPSWDebugGraph        *graph   ;
   QPointF                  newPos  ;

   //Valores utilizados para registro do funcionamento passo a passo
   int    iQBPTopo;
   int    iQBPDiagonal;
   int    iQBPLado;
   int    iQBPMatch;
   int    iQBPMissMatch;
   int    iQBPGap;
};

#endif // QBP_SWDEBUGINFO_H
