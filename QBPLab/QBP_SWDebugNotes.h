#ifndef QBP_SWDEBUGNOTES_H
#define QBP_SWDEBUGNOTES_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QVector>

class CQBPSWDebugGraph;

struct DebugNote
{
    QString NoteName;
    QRectF  NoteRect;
    int     NoteType;
};

class CQBPSWDebugNotes : public QGraphicsItem
{
public:
    CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget);
    CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,QString                   pQBPNotes);
    CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,vector<stQBPStringBuffer> pQBPNotes);
    CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection,vector<stQBPMusicBuffer > pQBPNotes);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    uint getSize(){return size;}
    uint getStep(){return step;}
    uint getNumNotes(){return qtdnotes;}
    void setNoteType(int Id,int Type){buffer[Id].NoteType=Type;}

private:
   QVector<DebugNote>       buffer  ;
   QVector<QRectF>          rects   ;
   CQBPSWDebugGraph        *graph   ;
   uint                     size    ;
   uint                     step    ;
   uint                     qtdnotes;
   uint                     direction;
   uint                     bufftype;

   QString                   notes;
   vector<stQBPStringBuffer> notesstr;
   vector<stQBPMusicBuffer>  notesv;
};

#endif // QBP_SWDEBUGNOTES_H
