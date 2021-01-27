#ifndef QBP_SWDEBUGSONG_H
#define QBP_SWDEBUGSONG_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

class CQBPSWDebugSong : public QGraphicsItem
{
public:
    CQBPSWDebugSong(CQBPSWDebugGraph *graphWidget);
    CQBPSWDebugSong(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,QString pQBPSongName,uint pQBPSongSize);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
   QRectF                   rect         ;
   uint                     direction    ;
   QString                  sQBPSongName ;
   uint                     iQBPSongSize ;
   CQBPSWDebugGraph        *graph        ;

};

#endif // QBP_SWDEBUGSONG_H
