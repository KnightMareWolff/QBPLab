/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Comparator - O objetivo principal da classe é realizar   a      */
/*verificação de similaridade entre musicas através do algoritmo de      */
/*alinhamento local Smith Waterman.                                      */
/*************************************************************************/
#ifndef QBP_COMPARATOR_H_
#define QBP_COMPARATOR_H_

#include "QBP_GlobalDef.h"
#include "QBP_LogQueue.h"
#include "QBP_Mask.h"
#include "QBP_MussumMask.h"
#include "QBP_MussixMask.h"
#include "QBP_AttitudeMask.h"
#include "QBP_SearchResults.h"

class CQBPComparator
{
public:
     CQBPComparator(                          );
     CQBPComparator( const CQBPComparator &obj);
     CQBPComparator(int pQBP_MatrixType       );
    ~CQBPComparator(                          );

    bool SetUserBuffer(vector<stQBPStringBuffer> pQBPBufferB, string pQBPSongNameB);
    bool SetCompBuffer(vector<stQBPStringBuffer> pQBPBufferA, string pQBPSongNameA);
    bool SetUserBuffer(vector<stQBPMusicBuffer> vQBP_IBufferB, string pQBPSongNameB);
    bool SetCompBuffer(vector<stQBPMusicBuffer> vQBP_IBufferA, string pQBPSongNameA);
    bool SetCompType  (int pQBP_MatrixType , int pQBP_PProcType);
    bool SetDatasetType(uint pQBP_DatasetType);
    void SetDebbugMode(bool pQBPDebbugMode){bQBPDebbugMode = pQBPDebbugMode;}

    uint GetCurrentSearch(){return iQBPCurrentSearch;}
    uint GetBufferType(){return iQBPBufferType;}

    int  CompareBuffer   (                                     );
    bool CollectAlignment(                                     );
    bool ExtractAlignment(CQBPSearch *tSearch,uint pAlignmentID);

    bool AddSearch();
    bool AddSearch(QString pQBPSearchName);
    bool AddAlignment();

    void CleanUp();

    CQBPMask          *pQBPMask;
    CQBPSearchResults *pQBPSearchResults;

private:

    CQBPMatrix  *pQBPSubstMatrix;
    uint iQBPCurrentSearch;
    uint iQBPCurrentAlignment;
    uint iQBPBufferType;
    uint iQBPPostProcessingType;
    uint iQBPDatasetType;
    bool bQBPDebbugMode;
};

#endif
