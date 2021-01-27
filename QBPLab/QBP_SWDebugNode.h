#ifndef QBP_SWDEBUGNODE_H
#define QBP_SWDEBUGNODE_H
#include "QBP_GlobalDef.h"
#include <QGraphicsItem>
#include <QList>

class CQBPSWDebugEdge;
class CQBPSWDebugGraph;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class CQBPSWDebugNode : public QGraphicsItem
{
public:
    CQBPSWDebugNode(CQBPSWDebugGraph *graphWidget);

    void addEdge(CQBPSWDebugEdge *edge);
    QList<CQBPSWDebugEdge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setType  (int type);
    void setScore (int score);
    void setDir   (int dir  );
    void setMatch (bool match){nodeMatch = match;}
    int  getDir   (         );
    int  getScore (         );
    bool getMatch (         ){return nodeMatch;}

    void setMatrixRef(int  pMatrixPosX,int  pMatrixPosY);
    void getMatrixRef(int &pMatrixPosX,int &pMatrixPosY);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<CQBPSWDebugEdge *> edgeList  ;
    QPointF                  newPos    ;
    QRectF                   bound     ;
    CQBPSWDebugGraph        *graph     ;
    float                    radius    ;
    float                    diameter  ;
    int                      nodetype  ;
    int                      nodescore ;
    int                      nodedir   ;
    int                      MatrixPosX;
    int                      MatrixPosY;
    bool                     nodeMatch ;
};

#endif // QBP_SWDEBUGNODE_H
