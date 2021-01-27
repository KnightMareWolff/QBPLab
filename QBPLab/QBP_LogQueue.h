#ifndef QBP_LOGQUEUE_H
#define QBP_LOGQUEUE_H

#include "QBP_GlobalDef.h"

class CQBPQueueItem
{
public:
    CQBPQueueItem ( )
    {
        pQBP_Color      = QColor(0,0,0);
        pQBP_BackGround = QColor(255,255,255);
        pQBP_Message    = "";
        pQBP_Bold       = false;
        pQBP_Size       = 8;
    }
    CQBPQueueItem ( const CQBPQueueItem &obj)
    {
        pQBP_Color      = obj.pQBP_Color;
        pQBP_BackGround = obj.pQBP_BackGround;
        pQBP_Message    = obj.pQBP_Message;
        pQBP_Bold       = obj.pQBP_Bold;
        pQBP_Size       = obj.pQBP_Size;
    }
    ~CQBPQueueItem(){}

    QColor          pQBP_Color;
    QColor          pQBP_BackGround;
    QString         pQBP_Message;
    bool            pQBP_Bold;
    int             pQBP_Size;
};

class CQBPLogQueue
{
public:
    CQBPLogQueue();

    static void    Push         (QString pQBPLog );
    static void    ColorPush    (QString pQBPLog ,QColor pQBPColor,QColor pQBPBack);

    static CQBPQueueItem Pop    (                );

    static bool    Empty        (                );
    static bool    Locked       (                );
    static void    SetLock      (bool pLockState );

private:
    static QQueue<CQBPQueueItem> pQBP_Log;
    static bool pQBP_Lock;

};

#endif // QBP_LOGQUEUE_H
