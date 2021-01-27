#include "QBP_PriorityQueue.h"

CQBPPriorityQueue::CQBPPriorityQueue()
{
    iQBP_QueueSize = 0;
    pQBP_QueueBegin = new CQBPPriorityQueueNode();
    //Seta escore gigante;
    pQBP_QueueBegin->pQBPSongScore = 9999;

    pQBP_QueueEnd   = new CQBPPriorityQueueNode();
    pQBP_QueueEnd->pQBPSongScore = 0;

    pQBP_QueueBegin->pQBP_NextNode  = pQBP_QueueEnd;
    pQBP_QueueBegin->pQBP_PriorNode = NULL;
    pQBP_QueueEnd->pQBP_PriorNode   = pQBP_QueueBegin;
    pQBP_QueueEnd->pQBP_NextNode    = NULL;

    iQBP_Max = 0;
    iQBP_Min = 0;
}


void CQBPPriorityQueue::Enqueue(CQBPPriorityQueueNode * no)
{
    CQBPPriorityQueueNode *novo = no;

    /*******************************************************************/
    /*The Nodes are enqueued acoordingly with your priority            */
    /*in this case how much greater is the cost...less is your priority*/
    /*******************************************************************/
    CQBPPriorityQueueNode *temp = pQBP_QueueBegin;

    //we cannot have a empty begin node AND ENQUEUE NODE...
    if (temp == NULL || no == NULL)return;

    //Just check
    if(temp->pQBP_NextNode!=NULL)
    {
       while ((no->pQBPSongScore < temp->pQBPSongScore) && temp != pQBP_QueueEnd)
       {
          temp = temp->pQBP_NextNode;
       }
    }

    /****************************************/
    /*Insert the node in the prior position */
    /****************************************/
    novo->pQBP_PriorNode = temp->pQBP_PriorNode;
    novo->pQBP_NextNode  = temp;
    temp->pQBP_PriorNode = novo;
    novo->pQBP_PriorNode->pQBP_NextNode = novo;

    iQBP_QueueSize++;

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    if(iQBP_QueueSize==1)
    {
        iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
        iQBP_Min = 0;
    }
    else
    {
       iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
       iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;
    }
}

void CQBPPriorityQueue::EnqueueMax(CQBPPriorityQueueNode * no)
{
    CQBPPriorityQueueNode *novo = no;

    //Caso o score seja mais baixo que o minimo
    if(novo->pQBPSongScore < iQBP_Min)
    {
        return;
    }
    //No caso de chegarmos no balanço maximo do Bag...
    if((novo->pQBPSongScore >= iQBP_Min && iQBP_QueueSize == iQBP_MaxSize))
    {
        DequeueBack();
    }
    /*******************************************************************/
    /*The Nodes are enqueued acoordingly with your priority            */
    /*in this case how much greater is the cost...less is your priority*/
    /*******************************************************************/
    CQBPPriorityQueueNode *temp = pQBP_QueueBegin;

    //we cannot have a empty begin node AND ENQUEUE NODE...
    if (temp == NULL || no == NULL)return;

    //Just check
    if(temp->pQBP_NextNode!=NULL)
    {
       while ((no->pQBPSongScore < temp->pQBPSongScore) && temp != pQBP_QueueEnd)
       {
          temp = temp->pQBP_NextNode;
       }
    }

    /****************************************/
    /*Insert the node in the prior position */
    /****************************************/
    novo->pQBP_PriorNode = temp->pQBP_PriorNode;
    novo->pQBP_NextNode  = temp;
    temp->pQBP_PriorNode = novo;
    novo->pQBP_PriorNode->pQBP_NextNode = novo;


    iQBP_QueueSize++;

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    if(iQBP_QueueSize==1)
    {
        iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
        iQBP_Min = 0;
    }
    else
    {
       iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
       iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;
    }
}

void CQBPPriorityQueue::Dequeue()
{
    /******************************************/
    /*we allways remove from the beggining....*/
    /******************************************/
    if (iQBP_QueueSize > 0)
    {
        CQBPPriorityQueueNode *temp = new CQBPPriorityQueueNode();

        pQBP_QueueBegin->pQBP_NextNode->pQBP_NextNode->pQBP_PriorNode = pQBP_QueueBegin;

        temp = pQBP_QueueBegin->pQBP_NextNode;

        pQBP_QueueBegin->pQBP_NextNode = pQBP_QueueBegin->pQBP_NextNode->pQBP_NextNode;

        delete temp;
    }

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
    iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;

    iQBP_QueueSize--;
}

void CQBPPriorityQueue::DequeueBack()
{
    /************************************/
    /*we allways remove from the end....*/
    /************************************/
    if (iQBP_QueueSize > 0)
    {
        CQBPPriorityQueueNode *temp = new CQBPPriorityQueueNode();

        pQBP_QueueEnd->pQBP_PriorNode->pQBP_PriorNode->pQBP_NextNode = pQBP_QueueEnd;

        temp = pQBP_QueueEnd->pQBP_PriorNode;

        pQBP_QueueEnd->pQBP_PriorNode = pQBP_QueueEnd->pQBP_PriorNode->pQBP_PriorNode;

        delete temp;
    }

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
    iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;

    iQBP_QueueSize--;
}

void CQBPPriorityQueue::Dequeue(QString &pQBP_SongName, int &pQBP_SongScore, int &pQBP_SongClassification)
{
    /******************************************/
    /*we allways remove from the beggining....*/
    /******************************************/
    if (iQBP_QueueSize > 0)
    {
        CQBPPriorityQueueNode *temp = new CQBPPriorityQueueNode();

        pQBP_QueueBegin->pQBP_NextNode->pQBP_NextNode->pQBP_PriorNode = pQBP_QueueBegin;

        temp = pQBP_QueueBegin->pQBP_NextNode;

        pQBP_QueueBegin->pQBP_NextNode = pQBP_QueueBegin->pQBP_NextNode->pQBP_NextNode;

        pQBP_SongName           = temp->pQBPSongName;
        pQBP_SongScore          = temp->pQBPSongScore;
        pQBP_SongClassification = temp->pQBPSongClassification;

        delete temp;
    }

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
    iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;

    iQBP_QueueSize--;
}

void CQBPPriorityQueue::DequeueBack(QString &pQBP_SongName, int &pQBP_SongScore, int &pQBP_SongClassification)
{
    /************************************/
    /*we allways remove from the end....*/
    /************************************/
    if (iQBP_QueueSize > 0)
    {
        CQBPPriorityQueueNode *temp = new CQBPPriorityQueueNode();

        pQBP_QueueEnd->pQBP_PriorNode->pQBP_PriorNode->pQBP_NextNode = pQBP_QueueEnd;

        temp = pQBP_QueueEnd->pQBP_PriorNode;

        pQBP_QueueEnd->pQBP_PriorNode = pQBP_QueueEnd->pQBP_PriorNode->pQBP_PriorNode;

        pQBP_SongName           = temp->pQBPSongName;
        pQBP_SongScore          = temp->pQBPSongScore;
        pQBP_SongClassification = temp->pQBPSongClassification;

        delete temp;
    }

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
    iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;

    iQBP_QueueSize--;
}

void CQBPPriorityQueue::Remove(CQBPPriorityQueueNode* no)
{
    /*************************************/
    /*Exclude without criteria...        */
    /*Atenção! verificar caso nao exista */
    /*************************************/
    CQBPPriorityQueueNode *temp = pQBP_QueueBegin;
    while (no->pQBPSongName != temp->pQBPSongName)
    {
        temp = temp->pQBP_NextNode;
    }

    temp->pQBP_NextNode->pQBP_PriorNode = temp->pQBP_PriorNode;
    temp->pQBP_PriorNode->pQBP_NextNode = temp->pQBP_NextNode;

    /******************************/
    /*Update the Min/Max Values   */
    /******************************/
    iQBP_Max = (uint)pQBP_QueueBegin->pQBP_NextNode->pQBPSongScore;
    iQBP_Min = (uint)pQBP_QueueEnd->pQBP_PriorNode->pQBPSongScore;

    iQBP_QueueSize--;

    delete temp;
}

/**************************************/
/*check if the node exists            */
/**************************************/
bool CQBPPriorityQueue::Contain(CQBPPriorityQueueNode* no) const
{
    CQBPPriorityQueueNode *temp = pQBP_QueueBegin;

    while (temp != pQBP_QueueEnd)
    {
        if (no->pQBPSongScore == temp->pQBPSongScore)
            return true;
        temp = temp->pQBP_NextNode;
    }
    return false;
}

/**************************************/
/*Clean-Up the Queue                  */
/**************************************/
void CQBPPriorityQueue::QueueClean()
{
    while (!QueueEmpty())
    {
        Dequeue();
    }

    iQBP_Max = 0;
    iQBP_Min = 0;

}

