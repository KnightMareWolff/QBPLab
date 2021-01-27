#include "QBP_LogQueue.h"

QQueue<CQBPQueueItem> CQBPLogQueue::pQBP_Log;
bool CQBPLogQueue::pQBP_Lock = false;


CQBPLogQueue::CQBPLogQueue()
{

}

void CQBPLogQueue::Push(QString pQBPLog)
{
    CQBPQueueItem Item;

    //pQBP_Lock =true;
    Item.pQBP_Color=QColor(0,0,0);
    Item.pQBP_BackGround=QColor(255,255,255);
    Item.pQBP_Message = pQBPLog;
    Item.pQBP_Bold    = false;
    Item.pQBP_Size    = 8;
    pQBP_Log.enqueue(Item);
    //pQBP_Lock = false;

}

void CQBPLogQueue::ColorPush(QString pQBPLog ,QColor pQBPColor,QColor pQBPBack)
{
    CQBPQueueItem Item;

    //pQBP_Lock =true;
    Item.pQBP_Color=pQBPColor;
    Item.pQBP_BackGround=pQBPBack;
    Item.pQBP_Message = pQBPLog;
    Item.pQBP_Bold    = true;
    Item.pQBP_Size    = 15;
    pQBP_Log.enqueue(Item);
    //pQBP_Lock =false;
}

CQBPQueueItem CQBPLogQueue::Pop()
{
    return pQBP_Log.dequeue();
}


bool    CQBPLogQueue::Empty()
{
    return pQBP_Log.isEmpty();
}

bool    CQBPLogQueue::Locked()
{
    return pQBP_Lock;
}

void    CQBPLogQueue::SetLock(bool pLockState )
{
    pQBP_Lock=pLockState;
}
