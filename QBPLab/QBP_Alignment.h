#ifndef QBP_ALIGNMENT_H
#define QBP_ALIGNMENT_H

#include "QBP_GlobalDef.h"
#include "QBP_MatrixValue.h"
#include "QBP_LogQueue.h"

//Member of a GraphList
struct  stQBPGraphListMember
{
    int               iQBP_QtdPathNotes;//Number of Notes in the Graph
    CQBPMatrixValue  *pQBPGraphPath    ;//The graph itself
};

class CQBPAlignment
{
public:
    CQBPAlignment(                                        );

    virtual ~CQBPAlignment();

    CQBPAlignment(QString pQBPSearchName,uint pQBPSearchId);
    CQBPAlignment( const CQBPAlignment &obj);

    CQBPAlignment & operator = (const CQBPAlignment& other);

    uint               getId     (){return iQBPSearchID;}
    uint               getType   (){return iQBPSearchType;}
    uint               getBufType(){return iQBPBufferType;}
    QString            getName   (){return sQBPSearchName;}

    vector<stQBPStringBuffer> getUbuf (){return sQBPUserBuffer;}
    vector<stQBPStringBuffer> getSbuf (){return sQBPSystemBuffer;}
    vector<stQBPMusicBuffer>  getUbufv(){return vQBPUserBuffer;}
    vector<stQBPMusicBuffer>  getSbufv(){return vQBPSystemBuffer;}

    bool               getAtd (){return bQBPUseAttitude;}
    bool               getRec (){return bQBPRecordSWMatrix;}

    bool               getGraphPath(QVector<QPointF> &pQBPPath);

    int                getX   (){return iQBPMatrixSizeX;}
    int                getY   (){return iQBPMatrixSizeY;}

    int     getNode (int x, int y, int &pDir      ,bool &pMatch);
    void    getDebug(int x, int y, int &piQBPTopo ,int  &piQBPDiagonal ,int &piQBPLado,int &piQBPMatch,int &piQBPMissMatch,int &piQBPGap);

    bool    setId  (uint    pQBPSearchId      ){iQBPSearchID      =pQBPSearchId      ;return true;}
    bool    setType(uint    pQBPSearchType    ){iQBPSearchType    =pQBPSearchType    ;return true;}
    bool    setName(QString pQBPSearchName    ){sQBPSearchName    =pQBPSearchName    ;return true;}

    bool    setUbuf (vector<stQBPStringBuffer> pQBPUserBuffer                     ){sQBPUserBuffer    =pQBPUserBuffer    ;return true;}
    bool    setSbuf (vector<stQBPStringBuffer> pQBPSystemBuffer                   ){sQBPSystemBuffer  =pQBPSystemBuffer  ;return true;}
    bool    setUbufv(vector<stQBPMusicBuffer>  pQBPUserBuffer    ){vQBPUserBuffer    =pQBPUserBuffer    ;return true;}
    bool    setSbufv(vector<stQBPMusicBuffer>  pQBPSystemBuffer  ){vQBPSystemBuffer  =pQBPSystemBuffer  ;return true;}

    bool    setAtd    (bool    pQBPUseAttitude   ){bQBPUseAttitude   =pQBPUseAttitude   ;return true;}
    bool    setBufType(uint    pQBPBufType       ){iQBPBufferType    =pQBPBufType       ;return true;}
    bool    setRec    (bool    pQBPRecordSWMatrix){bQBPRecordSWMatrix=pQBPRecordSWMatrix;return true;}
    bool    setX      (int     pX                ){iQBPMatrixSizeX   =pX                ;return true;}
    bool    setY      (int     pY                ){iQBPMatrixSizeY   =pY                ;return true;}

public:
    uint    iQBPSearchID;
    uint    iQBPSearchType;
    uint    iQBPComparatorType;
    uint    iQBPSWScore;
    uint    iQBPBufferType;
    bool    bQBPUseAttitude;
    bool    bQBPRecordSWMatrix;

    vector<stQBPStringBuffer> sQBPUserBuffer;
    vector<stQBPStringBuffer> sQBPSystemBuffer;
    vector<stQBPMusicBuffer> vQBPUserBuffer;
    vector<stQBPMusicBuffer> vQBPSystemBuffer;

    QString sQBPUserSongName;
    QString sQBPSystemSongName;
    QString sQBPSearchName;

    //Substitution Matrix
    CQBPMatrixValue **pQBPSearchMatrix;
    int               iQBPMatrixSizeX ,
                      iQBPMatrixSizeY ;

    //Backtracing Path
    int                    iQBPResultPathSize;
    int                    iQBPResultQtdPaths;
    CQBPMatrixValue       *pQBPGraphPath;
    stQBPGraphListMember  *pQBPGraphPathList;
};


#endif // QBP_ALIGNMENT_H
