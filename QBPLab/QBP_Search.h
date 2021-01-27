#ifndef QBP_SEARCH_H
#define QBP_SEARCH_H
#include "QBP_GlobalDef.h"
#include "QBP_MatrixValue.h"
#include "QBP_Song.h"
#include "QBP_Alignment.h"
#include "QBP_LogQueue.h"
#include "QBP_PriorityQueue.h"
#include "QBP_Dataset.h"

class CQBPSearch
{
public:


    virtual ~CQBPSearch();

    CQBPSearch();
    CQBPSearch(QString pQBPSearchName,uint pQBPSearchId);
    CQBPSearch( const CQBPSearch &obj);

    CQBPSearch & operator = (const CQBPSearch& other);

    uint               getId         (){return iQBPSearchID;}
    uint               getType       (){return iQBPSearchType;}
    uint               getDatasetType(){return iQBPDatasetType;}
    QString            getName       (){return sQBPSearchName;}

    bool    setId         (uint    pQBPSearchId      ){iQBPSearchID    = pQBPSearchId   ; return true;}
    bool    setType       (uint    pQBPSearchType    ){iQBPSearchType  = pQBPSearchType ; return true;}
    bool    setName       (QString pQBPSearchName    ){sQBPSearchName  = pQBPSearchName ; return true;}
    bool    setDatasetType(uint    pQBPDatasetType   ){iQBPDatasetType = pQBPDatasetType; return true;}

    bool    CalculateClassifications();
    bool    CalculateEvaluation();
public:
    uint    iQBPSearchID;
    uint    iQBPSearchType;
    uint    iQBPComparatorType;
    uint    iQBPPrecisionBalance;
    uint    iQBPResultSetBalance;
    uint    iQBPDatasetType;

    float   fQBPSearchElapsed   ;//Search Elapsed Time
    float   fQBPSearchElapsedPre;//Search Preprocessing Time
    float   fQBPSearchElapsedPro;//Search Processing Time
    float   fQBPSearchElapsedPos;//Search Pos-Processing Time

    QString sQBPSearchName;

    vector<CQBPAlignment *> pQBPSearchAlignments;
    CQBPSong             *  pQBPSearchSong      ;//Musica Utilizada para Busca

    vector<CQBPPriorityQueueNode> pQBPSearchResultSet ;//Lista de Musicas resultante

    float   fQBPCountTP,fQBPCountFP,fQBPCountTN,fQBPCountFN;
    float   fQBPPrecision,fQBPRecall,fQBPFmeasure,fQBPAccuracy;
    float   fQBPReciprocalRank;
    float   fQBPMeanSimilarityContourDistance;


};

#endif // QBP_SEARCH_H
