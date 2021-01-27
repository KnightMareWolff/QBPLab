#include "QBP_SWDebugNotes.h"
#include "QBP_SWDebugGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

CQBPSWDebugNotes::CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = 14;
    step     = 40;
    size     = qtdnotes * step;
    direction= 0;

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugNote note;
       note.NoteRect = QRectF(i * step,0 * step,step,step);
       note.NoteName = QString("A");
       note.NoteType = QBP_DBG_NOTE;
       buffer.push_back(note);
       rects.push_back(note.NoteRect);
    }
}

CQBPSWDebugNotes::CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, QString pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notes(pQBPNotes),bufftype(QBP_BUFFER_TYPE_CHR)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    size     = qtdnotes * step;

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);
           note.NoteName = QString(notes.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(0 * step,i * step,step,step);
           note.NoteName = QString(notes.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }
}

CQBPSWDebugNotes::CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, vector<stQBPStringBuffer> pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notesstr(pQBPNotes),bufftype(QBP_BUFFER_TYPE_CHR)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    size     = qtdnotes * step;

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);
           note.NoteName = QString(notesstr[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(0 * step,i * step,step,step);
           note.NoteName = QString(notesstr[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }
}

CQBPSWDebugNotes::CQBPSWDebugNotes(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, vector<stQBPMusicBuffer> pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notesv(pQBPNotes),bufftype(QBP_BUFFER_TYPE_STR)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    size     = qtdnotes * step;

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);
           note.NoteName = QString(notesv[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(0 * step,i * step,step,step);
           note.NoteName = QString(notesv[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }
}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugNotes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;

    pen = QPen(Qt::black, 0);
    pen.setWidth(3);

    painter->setPen(pen);


    for(uint i=0;i<qtdnotes;i++)
    {
       switch(buffer[i].NoteType)
       {
       case QBP_DBG_NOTE     :{painter->setBrush(Qt::black) ;painter->setPen(Qt::white);}break;
       case QBP_DBG_NOTE_EXCL:{painter->setBrush(Qt::blue)  ;painter->setPen(Qt::black);}break;
       case QBP_DBG_NOTE_INCL:{painter->setBrush(Qt::green) ;painter->setPen(Qt::black);}break;
       case QBP_DBG_NOTE_TARG:{painter->setBrush(Qt::white) ;painter->setPen(Qt::black);}break;
       case QBP_DBG_NOTE_UPDT:{painter->setBrush(Qt::yellow);painter->setPen(Qt::black);}break;
       }
       painter->drawRect(buffer[i].NoteRect);
       painter->drawText(buffer[i].NoteRect, Qt::AlignCenter, buffer[i].NoteName);
    }
}

QRectF CQBPSWDebugNotes::boundingRect() const
{
    QRectF bounds;
    switch(direction)
    {
    case 0:
    {
        bounds= QRectF( 0 ,0,size,step);
    }break;
    case 1:
    {
        bounds= QRectF( 0 ,0,step,size);
    }break;
    }
    return bounds;
}
