#include "QBP_SearchResults.h"

CQBPSearchResults::CQBPSearchResults()
{

}

CQBPSearchResults::~CQBPSearchResults()
{

}

CQBPSearchResults::CQBPSearchResults(const CQBPSearchResults   &obj)
{
    int Idx;
    //if the container was not properly allocated...
    if(vQBPSearchs.size()>0)
    {
        vQBPSearchs.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        vQBPSearchs.shrink_to_fit();
    }

    for (Idx = 0; Idx < (int)obj.vQBPSearchs.size(); Idx++)
    {
        vQBPSearchs.push_back(CQBPSearch(obj.vQBPSearchs[Idx]));
    }
}

CQBPSearchResults & CQBPSearchResults::operator = (const CQBPSearchResults& other)
{
    int Idx;
    //if the container was not properly allocated...
    if(vQBPSearchs.size()>0)
    {
        vQBPSearchs.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        vQBPSearchs.shrink_to_fit();
    }

    for (Idx = 0; Idx < (int)other.vQBPSearchs.size(); Idx++)
    {
        vQBPSearchs.push_back(CQBPSearch(other.vQBPSearchs[Idx]));
    }

    return *this;
}

bool CQBPSearchResults::addSearch(uint &pQBPSearchID)
{
    uint tSearchId = (uint)vQBPSearchs.size();

    vQBPSearchs.push_back(CQBPSearch(QString("Search %1").arg(tSearchId),tSearchId));

    pQBPSearchID     = tSearchId;

    //usamos o indice atual para controlar a busca que recebera o novo alinhamento
    iQBPActualSearch = pQBPSearchID;

    //quando adicionamos nova busca reseta o alinhamento atual
    iQBPActualAlignment = 0;

    return true;
}

bool CQBPSearchResults::addSearch(uint &pQBPSearchID,QString pQBPSearchName)
{
    uint tSearchId = (uint)vQBPSearchs.size();

    vQBPSearchs.push_back(CQBPSearch(pQBPSearchName,tSearchId));

    pQBPSearchID     = tSearchId;

    //usamos o indice atual para controlar a busca que recebera o novo alinhamento
    iQBPActualSearch = pQBPSearchID;

    //quando adicionamos nova busca reseta o alinhamento atual
    iQBPActualAlignment = 0;

    return true;
}

bool CQBPSearchResults::addAlignment(uint &pQBPAlignmentID)
{
    uint AlignmentId = (uint)vQBPSearchs[iQBPActualSearch].pQBPSearchAlignments.size();

    CQBPAlignment *tAlign = new CQBPAlignment("",AlignmentId);

    vQBPSearchs[iQBPActualSearch].pQBPSearchAlignments.push_back(tAlign);

    pQBPAlignmentID  = AlignmentId;

    iQBPActualAlignment = pQBPAlignmentID;

    return true;
}

CQBPSearch * CQBPSearchResults::getSearch(uint    pQBPSearchID  )
{
    //Atenção!!! returna o Ponteiro da Busca!
    return &vQBPSearchs[pQBPSearchID];
}



bool CQBPSearchResults::getSearchList(QVector<CQBPSearch> &pQBPSearchList)
{
    if(pQBPSearchList.size()>0)
    {
        pQBPSearchList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPSearchList.shrink_to_fit();
    }

    for(uint i=0;i<(uint)vQBPSearchs.size();i++)
    {
        pQBPSearchList.push_back(CQBPSearch(vQBPSearchs[i]));
    }
    return true;
}
