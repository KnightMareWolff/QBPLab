#ifndef QBP_SWDEBUGPARTITURE_H
#define QBP_SWDEBUGPARTITURE_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

struct DebugSimbolicNote
{
    QString  NoteName;
    QRectF   NoteRect;
    QPointF  Line1Start;
    QPointF  Line1End;
    QPointF  Line2Start;
    QPointF  Line2End;
    QPointF  Line3Start;
    QPointF  Line3End;
    QPointF  Line4Start;
    QPointF  Line4End;
    QPointF  Line5Start;
    QPointF  Line5End;
    QPainterPath  tablaturepath;//usada para desenhar as linhas
    int      NoteType;
};

class CQBPSWDebugPartiture : public QGraphicsItem
{
public:
    CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget);
    CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,QString                   pQBPNotes);
    CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,vector<stQBPStringBuffer> pQBPNotes);
    CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,vector<stQBPMusicBuffer>  pQBPNotes);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    //QPainterPath shape() const override;

    uint getSize(){return size;}
    uint getStep(){return step;}
    uint getNumNotes(){return qtdnotes;}
    void setNoteType(int Id,int Type){buffer[Id].NoteType=Type;}

private:
   QVector<DebugSimbolicNote>       buffer  ;
   QVector<QRectF>                  rects   ;
   CQBPSWDebugGraph                *graph   ;

   uint                     size         ;
   uint                     step         ;
   uint                     qtdnotes     ;
   uint                     direction    ;
   uint                     radius       ;

   QString                   notes        ;
   vector<stQBPStringBuffer> notesstr     ;
   vector<stQBPMusicBuffer>  notesv       ;

   int                      fontID       ;
   QStringList              fontfamily   ;

   //Para garantir fonte carregada apenas uma vez...
   static bool                     bHasFont;
   static QFont                    font;
};

#endif // QBP_SWDEBUGPARTITURE_H
