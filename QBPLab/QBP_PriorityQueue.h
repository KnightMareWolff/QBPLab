#ifndef QBP_PRIORITYQUEUE_H
#define QBP_PRIORITYQUEUE_H

#include "QBP_GlobalDef.h"

class CQBPPriorityQueueNode
{
public:
    CQBPPriorityQueueNode()
    {
        pQBPSongName.clear();
        pQBPSongScore=0;
        pQBPSongClassification=0;
        pQBP_NextNode = pQBP_PriorNode = NULL;
    }

    ~CQBPPriorityQueueNode()
    {
        pQBPSongName.clear();
        pQBPSongScore=0;
        pQBPSongClassification=0;
        pQBP_NextNode = pQBP_PriorNode = NULL;
    }

    CQBPPriorityQueueNode( const CQBPPriorityQueueNode &obj)
    {
        pQBPSongName          = obj.pQBPSongName;
        pQBPSongScore         = obj.pQBPSongScore;
        pQBPSongClassification= obj.pQBPSongClassification;
    }

    CQBPPriorityQueueNode(QString pQBP_SongName,int pQBP_SongScore,int pQBP_SongClassification)
    {
        pQBPSongName           = pQBP_SongName;
        pQBPSongScore          = pQBP_SongScore;
        pQBPSongClassification = pQBP_SongClassification;

        pQBP_NextNode = pQBP_PriorNode = 0;
    }

    QString pQBPSongName;
    int     pQBPSongScore;
    int     pQBPSongClassification;

    //WAMPriorityNode   *pWAM_QueueNode;
    CQBPPriorityQueueNode   *pQBP_NextNode;
    CQBPPriorityQueueNode   *pQBP_PriorNode;
};

class CQBPPriorityQueue
{
public:
      CQBPPriorityQueue();
     ~CQBPPriorityQueue()
     {
         QueueClean();
         delete pQBP_QueueBegin;
         delete pQBP_QueueEnd;
     }

    void                   QueueClean ();
    bool                   QueueEmpty () { return iQBP_QueueSize == 0; }
    void                   SetMaxSize (uint pQBP_MaxSize){iQBP_MaxSize = pQBP_MaxSize;}
    void                   Enqueue    (CQBPPriorityQueueNode *no);
    void                   EnqueueMax (CQBPPriorityQueueNode *no);
    void                   Dequeue    ();
    void                   DequeueBack();
    void                   Dequeue    (QString &pQBP_SongName, int &pQBP_SongScore, int &pQBP_SongClassification);
    void                   DequeueBack(QString &pQBP_SongName, int &pQBP_SongScore, int &pQBP_SongClassification);
    void                   Remove     (CQBPPriorityQueueNode *no);
    bool                   Contain    (CQBPPriorityQueueNode *no) const;

private:

    uint                   iQBP_QueueSize;
    uint                   iQBP_MaxSize;
    uint                   iQBP_Max;
    uint                   iQBP_Min;
    CQBPPriorityQueueNode *pQBP_QueueBegin;
    CQBPPriorityQueueNode *pQBP_QueueEnd;
};


#endif // QBP_PRIORITYQUEUE_H
