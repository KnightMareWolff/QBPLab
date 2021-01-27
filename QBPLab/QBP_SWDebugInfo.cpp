#include "QBP_SWDebugInfo.h"

CQBPSWDebugInfo::CQBPSWDebugInfo(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(5);
    rect=QRectF(0,0,80,80);

    iQBPTopo     =  1;
    iQBPDiagonal =  2;
    iQBPLado     =  3;
    iQBPMatch    =  1;
    iQBPMissMatch= -1;
    iQBPGap      = -2;

    QPointF posit = pos();

    setPos(QPointF(posit.x() - 80 , posit.y() - 80));


}

CQBPSWDebugInfo::CQBPSWDebugInfo(CQBPSWDebugGraph *graphWidget,int  piQBPTopo ,int piQBPDiagonal ,int piQBPLado,int piQBPMatch,int piQBPMissMatch,int piQBPGap)
    : graph(graphWidget),
      iQBPTopo(piQBPTopo),
      iQBPDiagonal(piQBPDiagonal),
      iQBPLado(piQBPLado),
      iQBPMatch(piQBPMatch),
      iQBPMissMatch(piQBPMissMatch),
      iQBPGap(piQBPGap)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(5);
    rect=QRectF(0,0,80,80);

    QPointF posit = pos();

    setPos(QPointF(posit.x() - 80 , posit.y() - 80));

}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;
    QString Espaco1;
    QString Linha01;
    QString Linha02;
    QString Linha03;
    QString Linha04;
    QString Linha05;
    QString Linha06;
    QString Espaco2;

    Espaco1 = QString("                \n");
    Linha01 = QString(" Topo         : ") + QString("%1").arg(iQBPTopo) + QString(" \n ");
    Linha02 = QString(" Diagonal     : ") + QString("%1").arg(iQBPDiagonal) + QString(" \n ");
    Linha03 = QString(" Lado         : ") + QString("%1").arg(iQBPLado) + QString(" \n ");
    Linha04 = QString(" Match        : ") + QString("%1").arg(iQBPMatch) + QString(" \n ");
    Linha05 = QString(" Mismatch     : ") + QString("%1").arg(iQBPMissMatch) + QString(" \n ");
    Linha06 = QString(" Gap(Penalty) : ") + QString("%1").arg(iQBPGap) + QString(" \n ");
    Espaco2 = QString("                \n");

    pen = QPen(Qt::black, 0);
    pen.setWidth(1);

    painter->setPen(pen);

    pen.setWidth(5);
    pen.setColor(Qt::darkYellow);
    painter->setPen(pen);
    painter->setBrush(Qt::gray);
    painter->drawRoundedRect(rect,3,3);

    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setBrush(Qt::yellow);

    QFont font = painter->font();
    font.setPixelSize(8);
    painter->setFont(font);

    painter->drawText(rect,Qt::AlignLeft, Espaco1 +
                                          Linha01 +
                                          Linha02 +
                                          Linha03 +
                                          Linha04 +
                                          Linha05 +
                                          Linha06 +
                                          Espaco2 );

}

QRectF CQBPSWDebugInfo::boundingRect() const
{
    QRectF bounds;

    bounds= QRectF(0,0,80,80);

    return bounds;
}

bool CQBPSWDebugInfo::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    update();
    return true;
}

void CQBPSWDebugInfo::stepMove(int Direction)
{
    QPointF pos1 = pos();

    switch(Direction)
    {
    case 0:{newPos = QPointF(pos1.x()   ,pos1.y()-40);}break;
    case 1:{newPos = QPointF(pos1.x()   ,pos1.y()+40);}break;
    case 2:{newPos = QPointF(pos1.x()-40,pos1.y());}break;
    case 3:{newPos = QPointF(pos1.x()+40,pos1.y());}break;
    }

    advancePosition();
}

void CQBPSWDebugInfo::setDebugInfo(int  piQBPTopo ,int piQBPDiagonal ,int piQBPLado,int piQBPMatch,int piQBPMissMatch,int piQBPGap)
{
    iQBPTopo     = piQBPTopo;
    iQBPDiagonal = piQBPDiagonal;
    iQBPLado     = piQBPLado;
    iQBPMatch    = piQBPMatch;
    iQBPMissMatch= piQBPMissMatch;
    iQBPGap      = piQBPGap;

    update();
}


