#include "QBP_SWDebugNode.h"
#include "QBP_SWDebugEdge.h"
#include "QBP_SWDebugGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

CQBPSWDebugNode::CQBPSWDebugNode(CQBPSWDebugGraph *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
    radius   = 20.0f;
    diameter = 40.0f;
    bound    = QRectF(0,0,diameter,diameter);
    nodetype = QBP_ND_DBG_BLK;
    nodescore= 0;
    nodeMatch=false;
}

void CQBPSWDebugNode::addEdge(CQBPSWDebugEdge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<CQBPSWDebugEdge *> CQBPSWDebugNode::edges() const
{
    return edgeList;
}

bool CQBPSWDebugNode::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF CQBPSWDebugNode::boundingRect() const
{
    return QRectF( 0 ,0, diameter, diameter);
}

QPainterPath CQBPSWDebugNode::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void CQBPSWDebugNode::setType(int type)
{
    nodetype = type;
}

void CQBPSWDebugNode::setScore(int score)
{
    nodescore = score;
}

void CQBPSWDebugNode::setDir(int dir)
{
    nodedir = dir;
}

int CQBPSWDebugNode::getDir()
{
    return nodedir;
}

int CQBPSWDebugNode::getScore()
{
    return nodescore;
}

void CQBPSWDebugNode::setMatrixRef(int  pMatrixPosX,int  pMatrixPosY)
{
    MatrixPosX = pMatrixPosX;
    MatrixPosY = pMatrixPosY;
}

void CQBPSWDebugNode::getMatrixRef(int &pMatrixPosX,int &pMatrixPosY)
{
    pMatrixPosX = MatrixPosX;
    pMatrixPosY = MatrixPosY;
}

void CQBPSWDebugNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;
    pen = QPen(Qt::black, 0);
    pen.setWidth(3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    QRadialGradient gradient(0,0,radius/3);

    switch(nodetype)
    {
    case QBP_ND_DBG_BLK:
    {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::white);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_RPH:
    {
        gradient.setColorAt(0, Qt::black);
        gradient.setColorAt(1, Qt::red);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_NPH:
    {
        gradient.setColorAt(0, Qt::black);
        gradient.setColorAt(1, Qt::cyan);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_NIN:
    {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::gray);
        pen.setBrush(Qt::darkGreen);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_NUP:
    {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::gray);
        pen.setBrush(Qt::darkYellow);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_NEX:
    {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::gray);
        pen.setBrush(Qt::darkBlue);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_NMA:
    {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::gray);
        pen.setBrush(Qt::darkRed);
        painter->setPen(pen);
        setZValue(1);
    }break;
    case QBP_ND_DBG_BRD:
    {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::yellow);
        pen.setBrush(Qt::darkYellow);
        painter->setPen(pen);
        setZValue(1);
    }break;
    }

    painter->setBrush(gradient);
    painter->drawEllipse(boundingRect());
    painter->drawText(boundingRect(), Qt::AlignCenter, QString("%1").arg(nodescore));

}

QVariant CQBPSWDebugNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        foreach (CQBPSWDebugEdge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void CQBPSWDebugNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CQBPSWDebugNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

