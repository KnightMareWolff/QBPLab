#include "QBP_SWDebugGraph.h"
#include "QBP_SWDebugEdge.h"
#include "QBP_SWDebugNode.h"
#include "QBP_SWDebugGrid.h"
#include "QBP_SWDebugNotes.h"
#include "QBP_SWDebugMask.h"
#include "QBP_SWDebugPartiture.h"
#include "QBP_SWDebugSong.h"
#include "QBP_SWDebugInfo.h"

CQBPSWDebugGraph::CQBPSWDebugGraph(QWidget *parent) : QGraphicsView(parent), timerId(0)
{
    SWDebugScene     = new QGraphicsScene(this);
    SWDebugGrid      = new CQBPSWDebugGrid(this);
    SWDebugBufferA   = new CQBPSWDebugNotes(this,0,QString("AAAAAAAAAAAAAA"));
    SWDebugBufferB   = new CQBPSWDebugNotes(this,1,QString("DDDDDDDDDDDDDD"));
    SWDebugSongNameA = new CQBPSWDebugSong(this,0,QString("DummySongA.mid"),14);
    SWDebugSongNameB = new CQBPSWDebugSong(this,1,QString("DummySongB.mid"),14);
    SWDebugMask      = new CQBPSWDebugMask(this);
    SWDebugInfo      = new CQBPSWDebugInfo(this);

    SWDebugSimbolicNotesA= new CQBPSWDebugPartiture(this,0,QString("qqqqqqqqqqqqqq"));
    SWDebugSimbolicNotesB= new CQBPSWDebugPartiture(this,1,QString("qqqqqqqqqqqqqq"));

    for(uint i=0;i<SWDebugGrid->getNumNodes();i++)
    {
        for(uint j=0;j<SWDebugGrid->getNumNodes();j++)
        {
            CQBPSWDebugNode *node = new CQBPSWDebugNode(this);
            node->setPos(j * SWDebugGrid->getStep() , i * SWDebugGrid->getStep());

            //Este nó é a borda
            if(j==0 || i==0)node->setType(QBP_ND_DBG_BRD);

            SWDebugScene->addItem(node);
        }
    }


    foreach (QGraphicsItem *item, SWDebugScene->items())
    {
        if (CQBPSWDebugNode *node = qgraphicsitem_cast<CQBPSWDebugNode *>(item))
            SWDebugNodes << node;
    }

    SWDebugScene->addItem(SWDebugGrid);
    SWDebugScene->addItem(SWDebugBufferA);
    SWDebugScene->addItem(SWDebugBufferB);
    SWDebugScene->addItem(SWDebugMask);
    //SWDebugScene->addItem(SWDebugSimbolicNotesA);
    //SWDebugScene->addItem(SWDebugSimbolicNotesB);
    SWDebugScene->addItem(SWDebugSongNameA);
    SWDebugScene->addItem(SWDebugSongNameB);
    SWDebugScene->addItem(SWDebugInfo);

    //Posiciona os buffers de comparação B
    QPointF pos1 = SWDebugBufferB->pos();
    QPointF pos2 = QPointF(pos1.x()-40,pos1.y()+40);

    SWDebugBufferB->setPos(pos2);

    //Posiciona os buffers de comparação A
    pos1 = SWDebugBufferA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-40);

    SWDebugBufferA->setPos(pos2);

    //Posiciona os buffers da Partitura A
    /*
    pos1 = SWDebugSimbolicNotesA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-90);

    SWDebugSimbolicNotesA->setPos(pos2);

    //Posiciona os buffers da Partitura B
    pos1 = SWDebugSimbolicNotesB->pos();
    pos2 = QPointF(pos1.x()-90,pos1.y()+40);

    SWDebugSimbolicNotesB->setPos(pos2);
    */

    //Posiciona os nomes da Musica A
    pos1 = SWDebugSongNameA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-140);

    SWDebugSongNameA->setPos(pos2);

    //Posiciona os nomes da Musica B
    pos1 = SWDebugSongNameB->pos();
    pos2 = QPointF(pos1.x()-140,pos1.y()+40);

    SWDebugSongNameB->setPos(pos2);

    SWDebugScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    SWDebugScene->setSceneRect(SWDebugScene->sceneRect());

    setScene(SWDebugScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(SmartViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorViewCenter);

    QSizeF size = SWDebugScene->sceneRect().size();
    setBaseSize(QSize(size.width(),size.height()));
    scale(qreal(0.6), qreal(0.6));

}

void CQBPSWDebugGraph::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void CQBPSWDebugGraph::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up   :{SWDebugMask->stepMove(0);SWDebugInfo->stepMove(0);}break;
    case Qt::Key_Down :{SWDebugMask->stepMove(1);SWDebugInfo->stepMove(1);}break;
    case Qt::Key_Left :{SWDebugMask->stepMove(2);SWDebugInfo->stepMove(2);}break;
    case Qt::Key_Right:{SWDebugMask->stepMove(3);SWDebugInfo->stepMove(3);}break;
    case Qt::Key_Plus:
        zoomOut();
        break;
    case Qt::Key_Minus:
        zoomIn();
        break;
    case Qt::Key_Escape:
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void CQBPSWDebugGraph::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<CQBPSWDebugNode *> nodes;
    foreach (QGraphicsItem *item, SWDebugScene->items()) {
        if (CQBPSWDebugNode *node = qgraphicsitem_cast<CQBPSWDebugNode *>(item))
            nodes << node;
    }

    killTimer(timerId);
    timerId = 0;
}


void CQBPSWDebugGraph::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
}

void CQBPSWDebugGraph::scaleView(qreal scaleFactor)
{
    scale(scaleFactor, scaleFactor);
}

void CQBPSWDebugGraph::zoomIn()
{
    scaleView(qreal(0.9));
}

void CQBPSWDebugGraph::zoomOut()
{
    scaleView(1 / qreal(0.9));
}

CQBPSWDebugNode* CQBPSWDebugGraph::getNodeByRef(int pRefX,int pRefY)
{
    for(int i=0;i<SWDebugNodes.size();i++)
    {
        int noderefX,noderefY;

        SWDebugNodes[i]->getMatrixRef(noderefX,noderefY);
        if(noderefX == pRefX &&
           noderefY == pRefY)
        {
            return SWDebugNodes[i];
        }
    }

    return nullptr;
}

bool CQBPSWDebugGraph::FillDebbug(CQBPSearch *pQBPExtractedSearch,uint pQBPAlignmentID)
{
    int    tDir;
    bool   tMatch;
    int    tVal;

    //Armazena o ponteiro para a busca atual
    pQBPActualSearch      = pQBPExtractedSearch;
    pQBPActualAlignmentID = pQBPAlignmentID;

    SWDebugScene->clear();
    SWDebugNodes.clear();
    SWDebugPath.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    SWDebugPath.shrink_to_fit();

    SWDebugScene   = new QGraphicsScene  (this);
    SWDebugGrid    = new CQBPSWDebugGrid (this,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getY()     );

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugBufferA = new CQBPSWDebugNotes(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf());
       SWDebugBufferB = new CQBPSWDebugNotes(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf());
    }
    else
    {
       SWDebugBufferA = new CQBPSWDebugNotes(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv());
       SWDebugBufferB = new CQBPSWDebugNotes(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv());
    }

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugSongNameA = new CQBPSWDebugSong(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPSystemSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf().size());
       SWDebugSongNameB = new CQBPSWDebugSong(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPUserSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf().size());
    }
    else
    {
        SWDebugSongNameA = new CQBPSWDebugSong(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPSystemSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv().size());
        SWDebugSongNameB = new CQBPSWDebugSong(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPUserSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv().size());
    }

    SWDebugMask    = new CQBPSWDebugMask(this);
    SWDebugInfo    = new CQBPSWDebugInfo(this);

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugSimbolicNotesA= new CQBPSWDebugPartiture(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf());
       SWDebugSimbolicNotesB= new CQBPSWDebugPartiture(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf());
    }
    else
    {
       SWDebugSimbolicNotesA= new CQBPSWDebugPartiture(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv());
       SWDebugSimbolicNotesB= new CQBPSWDebugPartiture(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv());
    }

    for(int i=0;i< pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getY() ;i++)
    {
        for(int j=0;j<pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getX();j++)
        {
            CQBPSWDebugNode *node = new CQBPSWDebugNode(this);
            node->setPos(j * SWDebugGrid->getStep() , i * SWDebugGrid->getStep());

            //seta no nó a referencia na Matriz
            node->setMatrixRef(j,i);

            //Pega e seta no nó o valor do score na Matrix
            tVal = pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getNode(j,i,tDir,tMatch);

            node ->setScore(tVal);
            node ->setDir(tDir);
            node ->setMatch(tMatch);

            //Customiza a aparencia de acordo com a direção do nó
            switch (tDir)
            {
               case QBP_VAL_DIR_DIAG:
               {
                   if(tMatch == false)
                   {
                       node->setType(QBP_ND_DBG_NUP);
                   }
                   else
                   {
                       node->setType(QBP_ND_DBG_NMA);
                   }
               }break;
               case QBP_VAL_DIR_LEFT:
               {
                   node->setType(QBP_ND_DBG_NIN);
               }break;
               case QBP_VAL_DIR_TOP:
               {
                   node->setType(QBP_ND_DBG_NEX);
               }break;
            }
            //Este nó é a borda
            if(j==0 || i==0)node->setType(QBP_ND_DBG_BRD);

            SWDebugScene->addItem(node);
        }
    }

    foreach (QGraphicsItem *item, SWDebugScene->items())
    {
        if (CQBPSWDebugNode *node = qgraphicsitem_cast<CQBPSWDebugNode *>(item))
            SWDebugNodes << node;
    }

    SWDebugScene->addItem(SWDebugGrid);
    SWDebugScene->addItem(SWDebugBufferA);
    SWDebugScene->addItem(SWDebugBufferB);
    SWDebugScene->addItem(SWDebugMask);
    SWDebugScene->addItem(SWDebugInfo);
    //SWDebugScene->addItem(SWDebugSimbolicNotesA);
    //SWDebugScene->addItem(SWDebugSimbolicNotesB);
    SWDebugScene->addItem(SWDebugSongNameA);
    SWDebugScene->addItem(SWDebugSongNameB);

    QPointF pos1 = SWDebugBufferB->pos();
    QPointF pos2 = QPointF(pos1.x()-40,pos1.y()+40);

    SWDebugBufferB->setPos(pos2);

    pos1 = SWDebugBufferA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-40);

    SWDebugBufferA->setPos(pos2);

    //Posiciona os buffers da Partitura A
    /*
    pos1 = SWDebugSimbolicNotesA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-90);

    SWDebugSimbolicNotesA->setPos(pos2);

    //Posiciona os buffers da Partitura B
    pos1 = SWDebugSimbolicNotesB->pos();
    pos2 = QPointF(pos1.x()-90,pos1.y()+40);

    SWDebugSimbolicNotesB->setPos(pos2);
    */

    //Posiciona os nomes da Musica A
    pos1 = SWDebugSongNameA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-140);

    SWDebugSongNameA->setPos(pos2);

    //Posiciona os nomes da Musica B
    pos1 = SWDebugSongNameB->pos();
    pos2 = QPointF(pos1.x()-140,pos1.y()+40);

    SWDebugSongNameB->setPos(pos2);

    SWDebugScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    SWDebugScene->setSceneRect(SWDebugScene->sceneRect());

    setScene(SWDebugScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(SmartViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorViewCenter);

    BuildFrames();

    QSizeF size = SWDebugScene->sceneRect().size();
    setBaseSize(QSize(size.width(),size.height()));

    return true;
}

bool CQBPSWDebugGraph::FillDebbug(CQBPSearch *pQBPExtractedSearch,uint pQBPAlignmentID,uint pQBPBackTraceID)
{
    int    tDir;
    bool   tMatch;
    int    tVal;

    //Armazena o ponteiro para a busca atual
    pQBPActualSearch      = pQBPExtractedSearch;
    pQBPActualAlignmentID = pQBPAlignmentID;

    SWDebugScene->clear();
    SWDebugNodes.clear();
    SWDebugPath.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    SWDebugPath.shrink_to_fit();

    SWDebugScene->update();

    SWDebugScene   = new QGraphicsScene  (this);
    SWDebugGrid    = new CQBPSWDebugGrid (this,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getY()     );

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugBufferA = new CQBPSWDebugNotes(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf());
       SWDebugBufferB = new CQBPSWDebugNotes(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf());
    }
    else
    {
       SWDebugBufferA = new CQBPSWDebugNotes(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv());
       SWDebugBufferB = new CQBPSWDebugNotes(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv());
    }

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugSongNameA = new CQBPSWDebugSong(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPSystemSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf().size());
       SWDebugSongNameB = new CQBPSWDebugSong(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPUserSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf().size());
    }
    else
    {
        SWDebugSongNameA = new CQBPSWDebugSong(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPSystemSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv().size());
        SWDebugSongNameB = new CQBPSWDebugSong(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->sQBPUserSongName,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv().size());
    }

    SWDebugMask    = new CQBPSWDebugMask(this);
    SWDebugInfo    = new CQBPSWDebugInfo(this);

    if(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getBufType()==QBP_BUFFER_TYPE_CHR)
    {
       SWDebugSimbolicNotesA= new CQBPSWDebugPartiture(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbuf());
       SWDebugSimbolicNotesB= new CQBPSWDebugPartiture(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbuf());
    }
    else
    {
       SWDebugSimbolicNotesA= new CQBPSWDebugPartiture(this,0,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getUbufv());
       SWDebugSimbolicNotesB= new CQBPSWDebugPartiture(this,1,pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getSbufv());
    }

    for(int i=0;i< pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getY() ;i++)
    {
        for(int j=0;j<pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getX();j++)
        {
            CQBPSWDebugNode *node = new CQBPSWDebugNode(this);
            node->setPos(j * SWDebugGrid->getStep() , i * SWDebugGrid->getStep());

            //seta no nó a referencia na Matriz
            node->setMatrixRef(j,i);

            //Pega e seta no nó o valor do score na Matrix
            tVal = pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->getNode(j,i,tDir,tMatch);

            node ->setScore(tVal);
            node ->setDir(tDir);
            node ->setMatch(tMatch);

            //Customiza a aparencia de acordo com a direção do nó
            switch (tDir)
            {
               case QBP_VAL_DIR_DIAG:
               {
                   if(tMatch == false)
                   {
                       node->setType(QBP_ND_DBG_NUP);
                   }
                   else
                   {
                       node->setType(QBP_ND_DBG_NMA);
                   }
               }break;
               case QBP_VAL_DIR_LEFT:
               {
                   node->setType(QBP_ND_DBG_NIN);
               }break;
               case QBP_VAL_DIR_TOP:
               {
                   node->setType(QBP_ND_DBG_NEX);
               }break;
            }
            //Este nó é a borda
            if(j==0 || i==0)node->setType(QBP_ND_DBG_BRD);

            SWDebugScene->addItem(node);
        }
    }

    foreach (QGraphicsItem *item, SWDebugScene->items())
    {
        if (CQBPSWDebugNode *node = qgraphicsitem_cast<CQBPSWDebugNode *>(item))
            SWDebugNodes << node;
    }

    SWDebugScene->addItem(SWDebugGrid);
    SWDebugScene->addItem(SWDebugBufferA);
    SWDebugScene->addItem(SWDebugBufferB);
    SWDebugScene->addItem(SWDebugMask);
    SWDebugScene->addItem(SWDebugInfo);
    //SWDebugScene->addItem(SWDebugSimbolicNotesA);
    //SWDebugScene->addItem(SWDebugSimbolicNotesB);
    SWDebugScene->addItem(SWDebugSongNameA);
    SWDebugScene->addItem(SWDebugSongNameB);

    QPointF pos1 = SWDebugBufferB->pos();
    QPointF pos2 = QPointF(pos1.x()-40,pos1.y()+40);

    SWDebugBufferB->setPos(pos2);

    pos1 = SWDebugBufferA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-40);

    SWDebugBufferA->setPos(pos2);

    //Posiciona os buffers da Partitura A
    /*
    pos1 = SWDebugSimbolicNotesA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-90);

    SWDebugSimbolicNotesA->setPos(pos2);

    //Posiciona os buffers da Partitura B
    pos1 = SWDebugSimbolicNotesB->pos();
    pos2 = QPointF(pos1.x()-90,pos1.y()+40);

    SWDebugSimbolicNotesB->setPos(pos2);
    */

    //Posiciona os nomes da Musica A
    pos1 = SWDebugSongNameA->pos();
    pos2 = QPointF(pos1.x()+40,pos1.y()-140);

    SWDebugSongNameA->setPos(pos2);

    //Posiciona os nomes da Musica B
    pos1 = SWDebugSongNameB->pos();
    pos2 = QPointF(pos1.x()-140,pos1.y()+40);

    SWDebugSongNameB->setPos(pos2);

    //Processa o Backtracing selectionado
    for(uint j=0; j < (uint)pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].iQBP_QtdPathNotes;j++)
    {
       CQBPSWDebugNode *node = getNodeByRef(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefX,
                                            pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefY);

       //O primeiro valor é a raiz do traceback
       if(j==0)
       {
          node->setType(QBP_ND_DBG_RPH);
       }
       else
       {
          //node->setType(QBP_ND_DBG_NPH);

          CQBPSWDebugNode *nodeant = getNodeByRef(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j-1].iQBPRefX,
                                                  pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j-1].iQBPRefY);

          CQBPSWDebugEdge *edge = new CQBPSWDebugEdge(nodeant,node);

          SWDebugScene->addItem(edge);
       }

       switch(node->getDir())
       {
       case QBP_VAL_DIR_DIAG:
       {
          if(node->getMatch())
          {
             SWDebugBufferB->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefY-1,QBP_DBG_NOTE_TARG);
             SWDebugBufferA->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefX-1,QBP_DBG_NOTE_TARG);
          }
          else
          {
             SWDebugBufferA->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefX-1,QBP_DBG_NOTE_UPDT);
             SWDebugBufferB->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefY-1,QBP_DBG_NOTE_UPDT);
          }
       }break;
       case QBP_VAL_DIR_LEFT:
       {
          SWDebugBufferB->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefY-1,QBP_DBG_NOTE_TARG);
          SWDebugBufferA->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefX-1,QBP_DBG_NOTE_INCL);
       }break;
       case QBP_VAL_DIR_TOP:
       {
          SWDebugBufferA->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefX-1,QBP_DBG_NOTE_TARG);
          SWDebugBufferB->setNoteType(pQBPExtractedSearch->pQBPSearchAlignments[pQBPAlignmentID]->pQBPGraphPathList[pQBPBackTraceID].pQBPGraphPath[j].iQBPRefY-1,QBP_DBG_NOTE_EXCL);
       }break;
       }
    }

    SWDebugScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    SWDebugScene->setSceneRect(SWDebugScene->sceneRect());

    setScene(SWDebugScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(SmartViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorViewCenter);

    BuildFrames();

    QSizeF size = SWDebugScene->sceneRect().size();
    setBaseSize(QSize(size.width(),size.height()));

    return true;
}

bool CQBPSWDebugGraph::SetNodes(uint pQBPFrame)
{
    int    tDir;
    bool   tMatch;
    int    tVal;
    int    tiQBPTopo;
    int    tiQBPDiagonal ;
    int    tiQBPLado;
    int    tiQBPMatch;
    int    tiQBPMissMatch;
    int    tiQBPGap;

    ClearNodes();

    int J,I;

    for(uint f=0;f<(uint)SWDebugFrames.size();f++)
    {
        J = SWDebugFrames[f].FrameX;
        I = SWDebugFrames[f].FrameY;

        //Pega e seta no nó o valor do score na Matrix
        tVal = pQBPActualSearch->pQBPSearchAlignments[pQBPActualAlignmentID]->getNode(J,I,tDir,tMatch);

        pQBPActualSearch->pQBPSearchAlignments[pQBPActualAlignmentID]->getDebug(J,I,tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

        CQBPSWDebugNode *node = getNodeByRef(J,I);

        //Frames menores são preenchidos normal
        if(f<=pQBPFrame)
        {
            node->setScore(tVal);
            node->setDir(tDir);
            node->setMatch(tMatch);
            //Customiza a aparencia de acordo com a direção do nó
            switch (tDir)
            {
               case QBP_VAL_DIR_DIAG:
               {
                   if(tMatch == false)
                   {
                      node->setType(QBP_ND_DBG_NUP);
                   }
                   else
                   {
                      node->setType(QBP_ND_DBG_NMA);
                   }
               }break;
               case QBP_VAL_DIR_LEFT:
               {
                   node->setType(QBP_ND_DBG_NIN);
               }break;
               case QBP_VAL_DIR_TOP:
               {
                   node->setType(QBP_ND_DBG_NEX);
               }break;
            }
            node->update(node->boundingRect());

            if(f==pQBPFrame)
            {
                SWDebugMask->setPos(QPointF((J-1)*40,(I-1)*40));

                QPointF posit = SWDebugMask->pos();

                SWDebugInfo->setDebugInfo(tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

                SWDebugInfo->setPos(QPointF(posit.x() - 80 , posit.y() - 80));
            }

        }
        else
        {
            node->setScore(0);
            node->setDir(QBP_VAL_DIR_NONE);
            node->setType(QBP_ND_DBG_BLK);
            node->update(node->boundingRect());
        }
    }

    return true;
}

bool CQBPSWDebugGraph::ClearNodes()
{
    int J,I;
    for(uint i=0;i<(uint)SWDebugNodes.size();i++)
    {
        SWDebugNodes[i]->setScore(0);
        SWDebugNodes[i]->setType(QBP_ND_DBG_BLK);

        SWDebugNodes[i]->getMatrixRef(I,J);

        //Este nó é a borda
        if(J==0 || I==0)SWDebugNodes[i]->setType(QBP_ND_DBG_BRD);

        SWDebugNodes[i]->update(SWDebugNodes[i]->boundingRect());
    }
    //CQBPSWDebugNode *node = getNodeByRef(1,1);

    return true;
}

bool CQBPSWDebugGraph::BuildFrames()
{
    int X,Y;
    stFrame frame;
    int     counter=0;

    //Limpa os Frames
    SWDebugFrames.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    SWDebugFrames.shrink_to_fit();

    for(uint i=0;i<(uint)SWDebugNodes.size();i++)
    {
        SWDebugNodes[i]->getMatrixRef(X,Y);

        //Este nó é a borda
        if(X==0 || Y==0)continue;

        frame.FrameID = counter;
        frame.FrameX  = X;
        frame.FrameY  = Y;

        SWDebugFrames.push_back(frame);

        counter++;
    }

    //Seta o Contador inverso e reinicializa o indice
    int FrameCount = (uint)SWDebugFrames.size();
    int iFrameIndex = 0;
    QVector<stFrame> SWDebugInvertedFrames;

    SWDebugInvertedFrames.resize(FrameCount);

    //Coleta o vetor invertido de traceback
    for (int k=FrameCount ;k > 0; k--)
    {
        SWDebugInvertedFrames[iFrameIndex].FrameID = SWDebugFrames[k-1].FrameID;
        SWDebugInvertedFrames[iFrameIndex].FrameX  = SWDebugFrames[k-1].FrameX;
        SWDebugInvertedFrames[iFrameIndex].FrameY  = SWDebugFrames[k-1].FrameY;
        iFrameIndex++;
    }

    SWDebugFrames = SWDebugInvertedFrames;

    return true;
}

