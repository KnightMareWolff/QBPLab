#include "QBP_Search.h"

CQBPSearch::~CQBPSearch()
{

}

CQBPSearch::CQBPSearch()
{
    iQBPSearchID      =0;
    iQBPSearchType    =QBP_SCH_TYPE_SINGLE;
    iQBPComparatorType=QBP_MATRIX_TYPE_ORIGIN;
    sQBPSearchName    ="";
}

CQBPSearch::CQBPSearch(QString pQBPSearchName, uint pQBPSearchId)
{
   iQBPSearchID       = pQBPSearchId;
   sQBPSearchName     = pQBPSearchName;
   iQBPSearchType     = QBP_SCH_TYPE_SINGLE;
   iQBPComparatorType = QBP_MATRIX_TYPE_ORIGIN;
}

CQBPSearch::CQBPSearch(const CQBPSearch &obj)
{

   sQBPSearchName     = obj.sQBPSearchName;
   iQBPSearchID       = obj.iQBPSearchID;
   iQBPSearchType     = obj.iQBPSearchType;
   iQBPComparatorType = obj.iQBPComparatorType;

   uint iTam = obj.pQBPSearchAlignments.size();

   pQBPSearchAlignments.resize(iTam);

   for (uint i=0 ; i< iTam ; i++)
   {
       pQBPSearchAlignments[i] = obj.pQBPSearchAlignments[i];
   }

   pQBPSearchSong = new CQBPSong();
   pQBPSearchSong = obj.pQBPSearchSong;

}

CQBPSearch & CQBPSearch::operator = (const CQBPSearch& other)
{

    sQBPSearchName     = other.sQBPSearchName;
    iQBPSearchID       = other.iQBPSearchID;
    iQBPSearchType     = other.iQBPSearchType;
    iQBPComparatorType = other.iQBPComparatorType;

    uint iTam = other.pQBPSearchAlignments.size();

    pQBPSearchAlignments.resize(iTam);

    for (uint i=0 ; i< iTam ; i++)
    {
        pQBPSearchAlignments[i] = other.pQBPSearchAlignments[i];
    }

    pQBPSearchSong = new CQBPSong();
    pQBPSearchSong = other.pQBPSearchSong;

    return *this;
}

bool CQBPSearch::CalculateClassifications()
{
    fQBPCountTP=0;
    fQBPCountFP=0;
    fQBPCountTN=0;
    fQBPCountFN=0;
    fQBPReciprocalRank = 0.0f;
    fQBPMeanSimilarityContourDistance = 0.0f;

    vector<int>   ScoreContour;
    int           ContourValue   =0;

    //Calcula Contadores Globais(Para Acuracia e Ranking)
    for(int i=0;i<(uint)pQBPSearchResultSet.size();i++)
    {
        switch(pQBPSearchResultSet[i].pQBPSongClassification)
        {
        case QBP_SCH_CLASS_TP :{fQBPCountTP++;}break;
        case QBP_SCH_CLASS_FP :{fQBPCountFP++;}break;
        case QBP_SCH_CLASS_TN :{fQBPCountTN++;}break;
        case QBP_SCH_CLASS_FN :{fQBPCountFN++;}break;
        }

        if(pQBPSearchSong->pQBPSongName     == pQBPSearchResultSet[i].pQBPSongName.toStdString() ||
           pQBPSearchSong->pQBPOriginalName == pQBPSearchResultSet[i].pQBPSongName.toStdString() )
        {
            float position = i+1;
            fQBPReciprocalRank = 1/position;
        }

        if((i+1)>=(uint)pQBPSearchResultSet.size())
        {
           ScoreContour.push_back(0);
        }
        else
        {
            ScoreContour.push_back(abs(pQBPSearchResultSet[i].pQBPSongScore - pQBPSearchResultSet[i+1].pQBPSongScore));
        }
    }


    ContourValue = 0;
    //Está sendo testado a metrica apenas com os tres primeiros valores e ver se temos resultados melhores.
    for(int i=0;i< /*ScoreContour.size()*/ 3;i++)
    {
        ContourValue += ScoreContour[i];
    }

    fQBPMeanSimilarityContourDistance = (float)ContourValue/3;

    //Normaliza de 0 a 1 o percentual MSCD - Mean Similarity Contour Distance
    //fQBPMeanSimilarityContourDistance = (float)(MeanValue - ContourMinValue)/(ContourMaxValue - ContourMinValue);


    //Limpa Vetores locais
    ScoreContour.clear();
    ScoreContour.shrink_to_fit();

    return true;
}

bool CQBPSearch::CalculateEvaluation()
{
    fQBPPrecision=0;
    fQBPRecall   =0;
    fQBPFmeasure =0;

    //Calculate the Counters TP,FP,TN,FN
    CalculateClassifications();

    //Calculate the Precision , Recall and FMeasure Metrics
    if((fQBPCountTP + fQBPCountFP)==0)
    {
       fQBPPrecision = 0.0f;
    }
    else
    {
       fQBPPrecision = ((fQBPCountTP / (fQBPCountTP + fQBPCountFP)));
    }

    if((fQBPCountTP + fQBPCountFN)==0)
    {
       fQBPRecall = 0.0f;
    }
    else
    {
       fQBPRecall    = ((fQBPCountTP / (fQBPCountTP + fQBPCountFN)));
    }

    if(fQBPPrecision == 0 && fQBPRecall==0)
    {
        fQBPFmeasure = 0.0f;
    }
    else
    {
       fQBPFmeasure  = 2 * (fQBPPrecision*fQBPRecall)/(fQBPPrecision + fQBPRecall);
    }

    //Acuracia pode usar contadores Globais
    fQBPAccuracy  = (fQBPCountTP + fQBPCountFP) / (fQBPCountTP+fQBPCountFP+fQBPCountTN+fQBPCountFN);

    return true;
}



