#include "QBP_SWDebugSong.h"
#include "QBP_SWDebugGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>


CQBPSWDebugSong::CQBPSWDebugSong(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    direction= 0;
    sQBPSongName = "DummySong.mid";
    rect=QRectF(0,0,sQBPSongName.size()*40,40);
}

CQBPSWDebugSong::CQBPSWDebugSong(CQBPSWDebugGraph *graphWidget,uint pQBPDirection, QString pQBPSongName,uint pQBPSongSize)
    : graph(graphWidget),direction(pQBPDirection),sQBPSongName(pQBPSongName),iQBPSongSize(pQBPSongSize)
{
    //setCacheMode(DeviceCoordinateCache);
    //setZValue(3);
    rect=QRectF(0,0,iQBPSongSize*40,40);
}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugSong::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;

    pen = QPen(Qt::black, 0);
    pen.setWidth(1);

    painter->setPen(pen);

    QPointF posit = pos();

    //É construida a partitura horizontal e no caso da vertical tudo é rotacionado e posicionado...
    if(direction==1)
    {
        painter->save();
        painter->rotate(-90);
        //O 85 é apenas uma correção vertical devido a rotação e translação
        painter->translate(QPointF(posit.x()-((iQBPSongSize*40)-140),posit.y()-40));
    }

    pen.setWidth(5);
    pen.setColor(Qt::darkYellow);
    painter->setPen(pen);

    painter->drawRoundedRect(rect,3,3);

    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setBrush(Qt::yellow);
    painter->drawText(rect,Qt::AlignCenter, sQBPSongName);

    //No caso do desenho da vertical temos que restaurar o sistema de coordenadas senão bagunça tudo...
    if(direction==1)
    {
        //O 85 é apenas uma correção vertical devido a rotação e translação
        painter->translate(QPointF(-(posit.x()-((iQBPSongSize*40)-140)),-(posit.y()-40)));
        painter->rotate(90);
        painter->restore();
    }
}

QRectF CQBPSWDebugSong::boundingRect() const
{
    QRectF bounds;
    switch(direction)
    {
    case 0:
    {
        bounds= QRectF(0,0,iQBPSongSize*40,40);
    }break;
    case 1:
    {
        bounds= QRectF(0,0,iQBPSongSize*40,40);
    }break;
    }
    return bounds;
}
