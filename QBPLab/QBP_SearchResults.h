/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Comparator - O objetivo principal da classe é realizar   a      */
/*verificação de similaridade entre musicas através do algoritmo de      */
/*alinhamento local Smith Waterman.                                      */
/*************************************************************************/
#ifndef QBP_SEARCHRESULTS_H
#define QBP_SEARCHRESULTS_H

#include "QBP_GlobalDef.h"
#include "QBP_Search.h"
#include "QBP_LogQueue.h"

class CQBPSearchResults
{
public:

    ~CQBPSearchResults();

    CQBPSearchResults();
    CQBPSearchResults( const CQBPSearchResults   &obj);

    CQBPSearchResults & operator = (const CQBPSearchResults& other);

    bool addSearch   (uint &pQBPSearchID);
    bool addSearch   (uint &pQBPSearchID,QString pQBPSearchName);
    bool addAlignment(uint &pQBPAlignmentID);

    uint  getQtdSearchs(){return (uint)vQBPSearchs.size();}

    CQBPSearch *getSearch(uint    pQBPSearchID);
    bool getSearchList(QVector<CQBPSearch> &pQBPSearchList);

    void clearResults()
    {
        vQBPSearchs.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        vQBPSearchs.shrink_to_fit();


        iQBPActualSearch=0;
        iQBPActualAlignment=0;
    }

private:
    vector<CQBPSearch>  vQBPSearchs;
    uint iQBPActualSearch;
    uint iQBPActualAlignment;
};

#endif // QBP_SEARCHRESULTS_H
