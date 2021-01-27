#ifndef QBP_SWDEBUGGRAPH_H
#define QBP_SWDEBUGGRAPH_H
#include "QBP_GlobalDef.h"
#include <QGraphicsView>
#include "QBP_Matrix.h"
#include "QBP_Search.h"

class CQBPSWDebugNode;
class CQBPSWDebugGrid;
class CQBPSWDebugNotes;
class CQBPSWDebugMask;
class CQBPSWDebugPartiture;
class CQBPSWDebugSong;
class CQBPSWDebugInfo;

struct stFrame
{
    int FrameID;
    int FrameX;
    int FrameY;
};

class CQBPSWDebugGraph : public QGraphicsView
{
    Q_OBJECT

public:

    virtual ~CQBPSWDebugGraph(){}

    CQBPSWDebugGraph(QWidget *parent = 0);

    void itemMoved();
    uint size(){return scenesize;}

    bool FillDebbug (CQBPSearch *pQBPExtractedSearch, uint pQBPAlignmentID);//Limpa e recalcula o grafico baseado na SW
    bool FillDebbug (CQBPSearch *pQBPExtractedSearch, uint pQBPAlignmentID, uint pQBPBackTraceID);//Limpa e recalcula o grafico baseado na SW
    bool SetNodes   (uint pQBPFrame);
    bool ClearNodes (              );
    bool BuildFrames(              );

    CQBPSWDebugNode* getNodeByRef(int pRefX,int pRefY);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int  timerId;
    uint scenesize;
    QGraphicsScene           *SWDebugScene;
    CQBPSWDebugGrid          *SWDebugGrid;
    CQBPSWDebugNotes         *SWDebugBufferA;
    CQBPSWDebugNotes         *SWDebugBufferB;
    CQBPSWDebugPartiture     *SWDebugSimbolicNotesA;
    CQBPSWDebugPartiture     *SWDebugSimbolicNotesB;
    CQBPSWDebugSong          *SWDebugSongNameA;
    CQBPSWDebugSong          *SWDebugSongNameB;
    CQBPSWDebugMask          *SWDebugMask;
    CQBPSWDebugInfo          *SWDebugInfo;
    QList<CQBPSWDebugNode   *>SWDebugNodes;
    QVector<QPointF>          SWDebugPath;
    QVector<stFrame>          SWDebugFrames;
    CQBPSearch               *pQBPActualSearch;
    uint                      pQBPActualAlignmentID;
};

#endif // QBP_SWDEBUGGRAPH_H
