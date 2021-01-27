#include "QBP_SWDebugMask.h"
#include "QBP_SWDebugGraph.h"


CQBPSWDebugMask::CQBPSWDebugMask(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(5);
    qtdnodes = 2;
    step     = 40;
    size     = qtdnodes * step;

    bound    = QRectF(0,0,size,size);

    for(uint i=0;i<qtdnodes;i++)
    {
        for(uint j=0;j<qtdnodes;j++)
        {
            QRectF rect = QRectF(j * step,i * step,step,step);

            grid.push_back(rect);
        }
    }
}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugMask::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;
    pen = QPen(Qt::black, 0);
    pen.setWidth(3);
    painter->setBrush(Qt::NoBrush);

    for(uint i=0;i<grid.size();i++)
    {
        switch(i)
        {
        case 0:
        {
            pen.setColor(Qt::red);
            painter->setPen(pen);
        }break;
        case 1:
        {
            pen.setColor(Qt::blue);
            painter->setPen(pen);
        }break;
        case 2:
        {
            pen.setColor(Qt::green);
            painter->setPen(pen);
        }break;
        case 3:
        {
            pen.setColor(Qt::black);
            painter->setPen(pen);
        }break;
        }

        painter->drawRect(grid[i]);
    }
}

QRectF CQBPSWDebugMask::boundingRect() const
{
    return QRectF( 0 ,0, size, size);
}

bool CQBPSWDebugMask::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    update();
    return true;
}

void CQBPSWDebugMask::stepMove(int Direction)
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

