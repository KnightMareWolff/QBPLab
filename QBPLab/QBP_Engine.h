/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe eNGINE - O objetivo principal da classe é ORQUESTRAR todo o     */
/*funcionamento de uma busca query-by-playing.                           */
/*Isto significa que esta sera a classe principal usada nas buscas de    */
/*musica, e que utilizara o classificador e comparador para tal , sendo  */
/*Estimulada pelo Keyboard (MIDI).                                       */
/*************************************************************************/
#ifndef QBP_ENGINE_H_
#define QBP_ENGINE_H_

#include "QBP_GlobalDef.h"
#include "QBP_Dataset.h"
#include "QBP_ClassifierSVM.h"
#include "QBP_ClassifierPool.h"
#include "QBP_Comparator.h"
#include "QBP_LogQueue.h"
#include "QBP_PriorityQueue.h"

class CQBPEngine
{
public:
     CQBPEngine(                      );
     CQBPEngine( const CQBPEngine &obj);
    ~CQBPEngine();

    //Dataset Building Functions
    bool BuildDatasets  (                 );
    bool BuildTestSet   (int  pQBPFormType);
    bool BuildValiSet   (int  pQBPFormType);
    bool BuildFullSet   (                 );
    bool BuildRandomSet (int  pQBPFormType);

    bool BuildBuffers (int  pQBPTargetList,
                       bool pQBPMusBuffer ,
                       bool pQBPExFeat    ,
                       bool pQBPExDts     );

    bool LoadDataset  (string pQBPath        ,
                       int    pQBPDatasetType,
                       int    pQBPTargetList ,
                       bool   pQBPClearList  );

    bool LoadChords   (string pQBPath);

    //Machine Learning Functions
    bool ClearEngine      (                                   );
    bool CreateTestData   (                                   );
    bool CreateTrainFile  (string pQBPath, int pQBPDatasetType , bool pQBPNormalized, bool pQBPUseCategory, int pQBPCategory);
    bool LoadSVMModel     (string pQBPath                     );
    bool TrainSVM         (string pQBPath, int pQBPDatasetType , bool pQBPNormalize, bool pQBPUseCategory, int pQBPCategory);
    bool AddClassifier    (uint pQBP_TargetCategory,int pQBPDatasetType,bool pQBPNormalize);
    bool CreateDefaultPool();
    bool LoadPool         ();


    //Search Functions(MIR)
    bool Search         (string pQBPSearchName              ,
                         string pQBPSongName                ,
                         int pQBPDatasetType                ,
                         int pQBPComparatorType             ,
                         bool pQBPUseAttitude               );

    bool Search         (string pQBPSearchName              ,
                         string pQBPSongAName               ,
                         string pQBPSongBName               ,
                         int pQBPDatasetType                ,
                         int pQBPComparatorType             ,
                         bool pQBPUseAttitude               );

    bool PreProcess    (string pQBPSongName , int pQBPDatasetType);
    bool PreProcess    (string pQBPSongAName,string pQBPSongBName,int pQBPDatasetType);
    bool Process       ();
    bool PosProcess    ();
    bool CompareSet    ();
    bool CompareSong   ();
    bool SetComparatorType(int pQBPComparatorType, uint pQBPDatasetType, uint pQBPProcType);

    //Statistic Functions
    int  SongsLoaded ();//Return the actual number of songs in memory
    int  GenresLoaded();//Return the actual number of genres in memory
    int  ChordsLoaded();//Return the actual number of chords in memory
    int  EvaluationsLoaded();
    int  ListGetSize (int pQBPListType);

    //Dataset Retrieve functions
    bool GetGenreData        (int pQBPGenreId,QString &pQBPName,int &pQBPNumberSongs);
    bool GetSongData         (int pQBPGenreId , int pQBPMusicId, QString &pQBPName, int &pQBPNumberOfNotes, int &pQBPNumberOfFeatures, int &pQBPNumberOfCustomFeatures);
    bool GetFeatureData      (int pQBPGenreId ,int pQBPMusicId,int pQBPFeatureId,QString &pQBPFeatureName,int &pQBPFeatureType,double &pQBPFeatureValue);
    bool GetCustomFeatureData(int pQBPGenreId ,int pQBPMusicId,int pQBPFeatureId,QString &pQBPFeatureName,int &pQBPFeatureType,double &pQBPFeatureValue);
    bool GetListData         (int pQBPListType, int pQBPMusicId, QString &pQBPName, int &pQBPNumberOfNotes, int &pQBPSearchScore);
    bool GetSearchData       (int &iQBP_SearchDimension, int &iQBP_CompletedSearchs);
    bool GetChordData        (int pQBPChordId , QString &pQBPChordName , int &pQBPNote01, int &pQBPNote02, int &pQBPNote03, int &pQBPNote04, int &pQBPNote05, int &pQBPNote06);

    //Testset Retrieve functions
    bool GetTestData(int pQBPMusicId, QString &pQBPName, int &pQBPNumberOfNotes, int &pQBPSearchScore, int &pQBPSearchClassification);
    int  TestGetSize(                                                                                );

    //Função temporaria para recuperar path de busca...
    CQBPSearch * GetSearch     (int pQBPSearchID);

    //Metrics Evaluation Functions
    bool CalculateEvaluation(uint pQBPSearchID);

    int  GetPrecision(){return iQBPSearchPrecisionBalance;}
    void SetPrecision(int pQBPSearchPrecision){iQBPSearchPrecisionBalance = pQBPSearchPrecision;}
    void SetResultSize(int pQBPSearchResult)
    {
        iQBPSearchResultBalance = abs(pQBPSearchResult/4);
        iQBPSearchResultMax     = pQBPSearchResult;
        pQBPTPSet.SetMaxSize(iQBPSearchResultBalance);//Lista de Prioridade de Musicas Relevantes
        pQBPFPSet.SetMaxSize(iQBPSearchResultBalance);//Lista de Prioridade de Musicas Irrelevantes
        pQBPFNSet.SetMaxSize(iQBPSearchResultBalance);//Lista de Prioridade de Musicas Irrelevantes
        pQBPTNSet.SetMaxSize(iQBPSearchResultMax);//Lista de Prioridade de Musicas Irrelevantes
        pQBPGLSet.SetMaxSize(iQBPSearchResultMax);
    }
    void SetDebbugMode(bool pQBPDebbugMode)
    {
        bQBPDebbugMode = pQBPDebbugMode;
        if(pQBPComparator)pQBPComparator->SetDebbugMode(pQBPDebbugMode);
    }

    void SetLock(bool pQBPLock){bQBPSetLock = pQBPLock;}
    bool GetLock(             ){return     bQBPSetLock;}

    void SetPosProc(int pQBPPostProcessingType){iQBPPostProcessingType=pQBPPostProcessingType;}
    int  GetPosProc(                          ){return iQBPPostProcessingType;}

    void SetAlgPosProc(int pQBPAlgPostProcessingType){iQBPAlgPostProcessingType=pQBPAlgPostProcessingType;}
    int  GetAlgPosProc(                             ){return iQBPAlgPostProcessingType;}

    void SetBufferSize(int pQBPBufferSize){iQBPBufferSize=pQBPBufferSize;}
    int  GetBufferSize(                  ){return iQBPBufferSize;}

    void SetSearchTimes(uint pQBPSearchID,
                        float pQBPGlobalSearchTime,
                        float pQBPInitializationSearchTime,
                        float pQBPProcessingSearchTime,
                        float pQBPPostProcessingSearchTime);

    void ClearSearchLists(uint pQBPSearchID);

    //Misc Functions
    bool PlaySongByName   (QString pQBPName          );
    bool MusicPlayer      (                          );
    bool FillTestSet      (int     pQBPDatasetType   );

    bool FillSearchSets   (uint pQBPSearchID                    ,
                           CQBPSong         *pQBPSearchSong     ,
                           vector<CQBPPriorityQueueNode> pQBPSearchResultSet);

    //Print Functions
    bool Print(int pQBPLogComparatorType);
    bool Print(bool pQBPAttitudeType);

    //Public Processing Members
    int  iQBPSearchDimension        ;//Number of Searchs Being Made...
    int  iQBPCompletedSearchs       ;//How Much Searchs was completed(Verificar remoção...)
    int  iQBPGlobalSearchCounter    ;//Contador Global de buscas efetuadas
    int  iQBPSearchType             ;//The Search Type defines the Lists being Used.
    int  iQBPDatasetType            ;//Tipo de Dataset de Busca(Teste,Validação ou Full)
    int  iQBPPostProcessingType     ;//Tipo de Pos-Processamento
    int  iQBPAlgPostProcessingType  ;//Tipo de Pos-Processamento do Algoritmo sendo usado
    int  iQBPBufferSize             ;//Tamanho do Buffer de Consulta
    int  iQBPComparatorType         ;//Tipo de Comparador
    int  iQBPSearchPrecisionBalance ;//Percentual de Balanceamento de Precisão
    int  iQBPSearchResultBalance    ;//Numero de itens de retorno por lista
    int  iQBPSearchResultMax        ;//Numero maximo de itens de retorno
    bool bQBPUseAttitude            ;//Utiliza o Attitude-Gram ?
    bool bQBPDebbugMode             ;//Utiliza Gravação Debbug ?

public:

    //Componentes de busca da Engine
    CQBPDataset        *pQBPDataset;
    CQBPClassifierSVM  *pQBPClassifier;
    CQBPClassifierPool *pQBPClassifierPool;
    ClassifierList     *pQBPPredictionBuffer;
    CQBPComparator     *pQBPComparator;

    //Itens para Busca
    CQBPSong                      pQBPUserSong     ;//musica escolhida pelo usuario
    CQBPSong                      pQBPSystemSong   ;//musica escolhida para comparação(alinhamento unico)
    vector<CQBPSong *>            pQBPTestSet      ;//Lista de Musicas para a busca
    vector<CQBPPriorityQueueNode> pQBPResultSet    ;//Lista de Musicas resultante

    CQBPPriorityQueue  pQBPTPSet  ;//Lista de Prioridade de Musicas True Positives(TP)
    CQBPPriorityQueue  pQBPFPSet  ;//Lista de Prioridade de Musicas FalsePositives(FP)
    CQBPPriorityQueue  pQBPFNSet  ;//Lista de Prioridade de Musicas FalseNegatives(FN)
    CQBPPriorityQueue  pQBPTNSet  ;//Lista de Prioridade de Musicas True Negatives(TN)
    CQBPPriorityQueue  pQBPGLSet  ;//Lista de Prioridade de Musicas Geral(GL)

    //Contadores de Tempo
    QElapsedTimer      pQBPSearchTimer     ;
    float              pQBPSearchElapsed   ;//Search Elapsed Time
    float              pQBPSearchElapsedPre;//Search Preprocessing Time
    float              pQBPSearchElapsedPro;//Search Processing Time
    float              pQBPSearchElapsedPos;//Search Pos-Processing Time
    //Para calculos de tempo
    time_t             pQBPActualTime;
    struct tm         *pQBPStartSTime;
    struct tm         *pQBPFinishTime;

    //Controladores de Processo
    bool               bQBPSetLock;//Pseudo-Semáforo de processamento
};

#endif

