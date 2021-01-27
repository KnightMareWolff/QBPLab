#include "QBP_SWDebugGrid.h"
#include "QBP_SWDebugGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

CQBPSWDebugGrid::CQBPSWDebugGrid(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    qtdnodes = 15;
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

CQBPSWDebugGrid::CQBPSWDebugGrid(CQBPSWDebugGraph *graphWidget, uint pQBPSize)
    : graph(graphWidget),qtdnodes(pQBPSize)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
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
bool CQBPSWDebugGrid::resize(int pQBP_Size)
{
    qtdnodes = pQBP_Size;
    step     = 40;
    size     = qtdnodes * step;

    bound    = QRectF(0,0,size,size);

    if(grid.size()>0)
    {
        grid.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        grid.shrink_to_fit();
    }

    for(uint i=0;i<qtdnodes;i++)
    {
        for(uint j=0;j<qtdnodes;j++)
        {
            QRectF rect = QRectF(j * step,i * step,step,step);

            grid.push_back(rect);
        }
    }

    return true;
}

//Paint e boundingRect Precisam ser implementadas obrigatoriamente
void CQBPSWDebugGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::darkGreen);
    //painter->drawRects(grid);
}

QRectF CQBPSWDebugGrid::boundingRect() const
{
    return QRectF( 0 ,0, size, size);
}
