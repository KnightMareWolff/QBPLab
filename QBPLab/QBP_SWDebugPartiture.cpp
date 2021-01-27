#include "QBP_SWDebugPartiture.h"
#include "QBP_SWDebugGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

bool  CQBPSWDebugPartiture::bHasFont=false;
QFont CQBPSWDebugPartiture::font;

CQBPSWDebugPartiture::CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = 14;
    step     = 40;
    radius   = step/2;
    size     = qtdnotes * step;
    direction= 0;

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugSimbolicNote note;
       note.NoteRect = QRectF(i * step,0 * step,step,step);
       note.NoteName = QString("q");
       note.NoteType = QBP_DBG_NOTE;
       buffer.push_back(note);
       rects.push_back(note.NoteRect);
    }

    if(!bHasFont)
    {
       fontID = QFontDatabase::addApplicationFont("Fonts/guido2.ttf");
       fontfamily = QFontDatabase::applicationFontFamilies(fontID);
       bHasFont=true;
       font = QFont(fontfamily.at(0));
    }
}

CQBPSWDebugPartiture::CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, QString pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notes(pQBPNotes)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    radius   = step/2;
    size     = qtdnotes * step;

    //pega a string reversa das notas
    QString reverse;
    reverse.reserve(notes.size());
    for(int k=notes.size()-1; k>=0; k--)
    {
        reverse.push_back(notes.at(k));
    }

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugSimbolicNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(notes.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(reverse.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }

    if(!bHasFont)
    {
       fontID = QFontDatabase::addApplicationFont("Fonts/guido2.ttf");
       fontfamily = QFontDatabase::applicationFontFamilies(fontID);
       font = QFont(fontfamily.at(0));
       bHasFont=true;
    }


}

CQBPSWDebugPartiture::CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, vector<stQBPStringBuffer> pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notesstr(pQBPNotes)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    radius   = step/2;
    size     = qtdnotes * step;

    //pega a string reversa das notas
    QString reverse;
    reverse.reserve(notesstr.size());
    for(int k=notesstr.size()-1; k>=0; k--)
    {
        reverse.push_back(notesstr[k].sQBP_Note.c_str());
    }

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugSimbolicNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(notesstr[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(reverse.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }

    if(!bHasFont)
    {
       fontID = QFontDatabase::addApplicationFont("Fonts/guido2.ttf");
       fontfamily = QFontDatabase::applicationFontFamilies(fontID);
       font = QFont(fontfamily.at(0));
       bHasFont=true;
    }


}

CQBPSWDebugPartiture::CQBPSWDebugPartiture(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, vector<stQBPMusicBuffer> pQBPNotes)
    : graph(graphWidget),direction(pQBPDirection),notesv(pQBPNotes)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    qtdnotes = pQBPNotes.size();
    step     = 40;
    radius   = step/2;
    size     = qtdnotes * step;

    //pega a string reversa das notas
    QString reverse;
    reverse.reserve(notesv.size());
    for(int k=notesv.size()-1; k>=0; k--)
    {
        reverse.push_back(notesv[k].sQBP_Note.c_str());
    }

    for(uint i=0;i<qtdnotes;i++)
    {
       DebugSimbolicNote note;

       switch(direction)
       {
       case 0:
       {

           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(notesv[i].sQBP_Note.c_str());
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       case 1:
       {
           note.NoteRect = QRectF(i * step,0 * step,step,step);

           QPointF center = note.NoteRect.center();

           note.Line1Start = QPointF(center.x()-radius,center.y()+radius/2);
           note.Line1End   = QPointF(center.x()+radius,center.y()+radius/2);

           note.Line2Start = QPointF(center.x()-radius,center.y()+radius/3);
           note.Line2End   = QPointF(center.x()+radius,center.y()+radius/3);

           note.Line3Start = QPointF(center.x()-radius,center.y());
           note.Line3End   = QPointF(center.x()+radius,center.y());

           note.Line4Start = QPointF(center.x()-radius,center.y()-radius/3);
           note.Line4End   = QPointF(center.x()+radius,center.y()-radius/3);

           note.Line5Start = QPointF(center.x()-radius,center.y()-radius/2);
           note.Line5End   = QPointF(center.x()+radius,center.y()-radius/2);

           note.tablaturepath.moveTo(note.Line1Start);
           note.tablaturepath.lineTo(note.Line1End);

           note.tablaturepath.moveTo(note.Line2Start);
           note.tablaturepath.lineTo(note.Line2End);

           note.tablaturepath.moveTo(note.Line3Start);
           note.tablaturepath.lineTo(note.Line3End);

           note.tablaturepath.moveTo(note.Line4Start);
           note.tablaturepath.lineTo(note.Line4End);

           note.tablaturepath.moveTo(note.Line5Start);
           note.tablaturepath.lineTo(note.Line5End);

           note.NoteName = QString(reverse.at(i));
           note.NoteType = QBP_DBG_NOTE;
           buffer.push_back(note);
           rects.push_back(note.NoteRect);
       }break;
       }
    }

    if(!bHasFont)
    {
       fontID = QFontDatabase::addApplicationFont("Fonts/guido2.ttf");
       fontfamily = QFontDatabase::applicationFontFamilies(fontID);
       font = QFont(fontfamily.at(0));
       bHasFont=true;
    }


}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugPartiture::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;
    QPointF center ;
    QPointF posnote;

    pen = QPen(Qt::black, 0);
    pen.setWidth(1);

    painter->setPen(pen);
    painter->setFont(font);

    QPointF posit = pos();

    //É construida a partitura horizontal e no caso da vertical tudo é rotacionado e posicionado...
    if(direction==1)
    {
        painter->save();
        painter->rotate(-90);
        //O 85 é apenas uma correção vertical devido a rotação e translação
        painter->translate(QPointF(posit.x()-((qtdnotes*step)-90),posit.y()-(step)));
    }

    pen.setWidth(5);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(QRectF(0,0,size,step),3,3);

    for(uint i=0;i<qtdnotes;i++)
    {
       pen.setWidth(1);
       pen.setColor(Qt::black);
       painter->setPen(pen);
       painter->setBrush(Qt::white);
       painter->drawPath(buffer[i].tablaturepath);

       center  = buffer[i].NoteRect.center();

       //buffer[i].NoteName
       if(buffer[i].NoteName == "C"){posnote = QPointF(center.x(),center.y()+radius/2);}
       if(buffer[i].NoteName == "D"){posnote = QPointF(center.x(),center.y()+radius/3);}
       if(buffer[i].NoteName == "E"){posnote = QPointF(center.x(),center.y()+radius/4);}
       if(buffer[i].NoteName == "F"){posnote = QPointF(center.x(),center.y()         );}
       if(buffer[i].NoteName == "G"){posnote = QPointF(center.x(),center.y()-radius/4);}
       if(buffer[i].NoteName == "A"){posnote = QPointF(center.x(),center.y()-radius/3);}
       if(buffer[i].NoteName == "B"){posnote = QPointF(center.x(),center.y()-radius/2);}

       painter->drawText(posnote,"q");
    }

    //No caso do desenho da vertical temos que restaurar o sistema de coordenadas senão bagunça tudo...
    if(direction==1)
    {
        //O 85 é apenas uma correção vertical devido a rotação e translação
        painter->translate(QPointF(-(posit.x()-((qtdnotes*step)-90)),-(posit.y()-(step))));
        painter->rotate(90);
        painter->restore();
    }




}

QRectF CQBPSWDebugPartiture::boundingRect() const
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
/*
QPainterPath CQBPSWDebugPartiture::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
*/
