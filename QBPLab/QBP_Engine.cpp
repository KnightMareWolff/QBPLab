#include "QBP_Engine.h"

CQBPEngine::CQBPEngine()
{
    //Extrai o dataset de arquivos MIDI
    pQBPDataset = new CQBPDataset();
    if(!pQBPDataset)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPDataset!.");
        msgBox.exec();
    }
    //Cria o classificador de generos musicais
    pQBPClassifier = new CQBPClassifierSVM();
    if(!pQBPClassifier)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPClassifier!.");
        msgBox.exec();
    }

    //Cria o Pool de classificadores musicais
    pQBPClassifierPool = new CQBPClassifierPool();
    if(!pQBPClassifierPool)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPClassifierPool!.");
        msgBox.exec();
    }

    pQBPPredictionBuffer = new ClassifierList();
    if(!pQBPPredictionBuffer)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para ClassifierList(Prediction Buffer)!.");
        msgBox.exec();
    }

    //Cria o comparador de similaridade entre musicas
    pQBPComparator = new CQBPComparator(QBP_MATRIX_TYPE_ORIGIN);
    if(!pQBPComparator)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPComparator!.");
        msgBox.exec();
    }

    //Inicializa o Search Type
    iQBPSearchType             = QBP_SCH_TYPE_SINGLE;
    iQBPPostProcessingType     = QBP_SCH_PPROC_QUEUE;
    iQBPAlgPostProcessingType  = QBP_POSTPROC_TYPE_F1;
    iQBPSearchPrecisionBalance = 50;
    iQBPSearchResultBalance    = 20;
    iQBPBufferSize             = 10;
    bQBPDebbugMode             = false;
    bQBPSetLock                = false;
    iQBPGlobalSearchCounter    = 0;

    SetResultSize(20);
}

CQBPEngine::CQBPEngine(const CQBPEngine &obj)
{
    //Extrai o dataset de arquivos MIDI
    pQBPDataset = obj.pQBPDataset;
    //Cria o classificador de generos musicais
    pQBPClassifier = obj.pQBPClassifier;
    //Pool de Classificadores
    pQBPClassifierPool = obj.pQBPClassifierPool;
    //Buffer de Predição
    pQBPPredictionBuffer = obj.pQBPPredictionBuffer;
    //Cria o comparador de similaridade entre musicas
    pQBPComparator = obj.pQBPComparator;
    //Inicializa o Search Type
    iQBPSearchType = obj.iQBPSearchType;
    //Inicializa Pos-Processamento
    iQBPPostProcessingType = obj.iQBPPostProcessingType;
    //Inicializa a Precisão
    iQBPSearchPrecisionBalance = obj.iQBPSearchPrecisionBalance;
    //Inicializa o Balanço de Resultado
    iQBPSearchResultBalance    = obj.iQBPSearchResultBalance;
    //Inicializa o Buffer Size
    iQBPBufferSize             = obj.iQBPBufferSize;
    //Inicializa maximo de itens da lista final
    iQBPSearchResultMax        = obj.iQBPSearchResultMax;
    //Inicializa Debbug Mode
    bQBPDebbugMode             = obj.bQBPDebbugMode;
    //Inicializa o controle
    bQBPSetLock                = obj.bQBPSetLock;
}


CQBPEngine::~CQBPEngine()
{
}

bool CQBPEngine::LoadChords(string pQBPath)
{
    pQBPDataset->LoadChords(pQBPath);
    return true;
}

bool CQBPEngine::LoadDataset(string pQBPath, int  pQBPDatasetType, int  pQBPTargetList, bool pQBPClearList)
{
    //Limpa o Dataset para garantir lista nova.
    if(pQBPClearList)pQBPDataset->ClearDataset(pQBPTargetList);
    //Carrega base direcionada para lista de teste
    switch(pQBPDatasetType)
    {
    case QBP_LOAD_TYPE_FULL:
    {
        //Fill Search Dimensions
        iQBPSearchDimension = 10198;
        iQBPCompletedSearchs= 0;
    }break;
    case QBP_LOAD_TYPE_GENRE:
    {
        //Fill Search Dimensions
        iQBPSearchDimension = 11;
        iQBPCompletedSearchs= 0;
    }break;
    case QBP_LOAD_TYPE_MIDI:
    {
        //Fill Search Dimensions
        iQBPSearchDimension = 10198;
        iQBPCompletedSearchs= 0;
    }break;
    case QBP_LOAD_TYPE_BUILD:
    {
        //Fill Search Dimensions
        iQBPSearchDimension = 10198;
        iQBPCompletedSearchs= 0;
    }break;
    }

    pQBPDataset->LoadDataset(pQBPath, pQBPDatasetType, pQBPTargetList);
    return true;
}

bool CQBPEngine::BuildDatasets()
{
    //Limpa o Dataset para garantir lista nova.
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_DATASET);
    //Constroi a base MIDI , Converte e grava base Dts e Dts Stripped
    pQBPDataset->LoadDataset("dataset", QBP_LOAD_TYPE_BUILD, QBP_LOAD_TARGET_DATASET);
    pQBPDataset->Print();
    return true;
}

bool CQBPEngine::CreateTestData()
{
    //Constroi a base MIDI , Converte e grava base Dts e Dts Stripped
    LoadDataset("testset", QBP_LOAD_TYPE_MIDI, QBP_LOAD_TARGET_TESTSET, true);//Musicas MIDI de teste

    pQBPDataset->CheckTestSet();

    return true;
}

bool CQBPEngine::ClearEngine()
{
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_DATASET);
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_TESTSET);
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_VALISET);
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_FULLSET);

    return true;
}

bool CQBPEngine::CreateTrainFile(string pQBPath,int pQBPDatasetType,bool pQBPNormalized,bool pQBPUseCategory,int pQBPCategory)
{
    if(pQBPNormalized)
    {
        if(pQBPUseCategory)
        {
           pQBPDataset->WriteSvmCat(pQBPath, pQBPDatasetType,pQBPCategory);
        }
        else
        {
           pQBPDataset->WriteSvmNorm(pQBPath, pQBPDatasetType);
        }
    }
    else
    {
        if(pQBPUseCategory)
        {
           pQBPDataset->WriteSvmCat(pQBPath, pQBPDatasetType,pQBPCategory);
        }
        else
        {
           pQBPDataset->WriteSvm(pQBPath, pQBPDatasetType);
        }
    }
    return true;
}

bool CQBPEngine::BuildTestSet(int  pQBPFormType)
{
    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);
    //Constroi um set SVM para treinamento usando a formula especifica enviada
    pQBPDataset->CreateSet(QBP_LOAD_TARGET_TESTSET, pQBPFormType , iQBPBufferSize);

    //Libera trava
    SetLock(false);
    return true;
}

bool CQBPEngine::BuildValiSet(int  pQBPFormType)
{
    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    //Constroi a base MIDI , Converte e grava base Dts e Dts Stripped
    pQBPDataset->CreateSet(QBP_LOAD_TARGET_VALISET, QBP_FORM_TYPE_LESS_GENRE,iQBPBufferSize);

    //Libera trava
    SetLock(false);

    return true;
}

bool CQBPEngine::BuildFullSet()
{
    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    //Constroi a base MIDI , Converte e grava base Dts e Dts Stripped
    pQBPDataset->CreateSet(QBP_LOAD_TARGET_FULLSET, QBP_FORM_TYPE_LESS_GENRE,iQBPBufferSize);

    //Libera trava
    SetLock(false);

    return true;
}

bool CQBPEngine::BuildRandomSet(int  pQBPFormType)
{
    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    //Constroi a base MIDI , Converte e grava base Dts e Dts Stripped
    pQBPDataset->CreateSet(QBP_LOAD_TARGET_RANDSET, QBP_FORM_TYPE_LESS_GENRE,iQBPBufferSize);

    //Libera trava
    SetLock(false);

    return true;
}

bool CQBPEngine::BuildBuffers(int  pQBPTargetList, bool pQBPMusBuffer, bool pQBPExFeat, bool pQBPExDts)
{
    if(pQBPMusBuffer)pQBPDataset->BuildMusicBuffers(pQBPTargetList);
    if(pQBPExFeat   )pQBPDataset->BuildFeaturesDts (pQBPTargetList);
    if(pQBPExDts    )pQBPDataset->BuildStrippedDts (pQBPTargetList);
    return true;
}

bool CQBPEngine::Print(int pQBPLogComparatorType)
{
    switch(pQBPLogComparatorType)
    {
    case QBP_MATRIX_TYPE_ORIGIN:
    {
        CQBPLogQueue::Push(QString("Experimento: SW")                 +
                           QString("\n")                              );
    }break;
    case QBP_MATRIX_TYPE_MUSSUM:
    {
        CQBPLogQueue::Push(QString("Experimento: MUSSUM")                 +
                           QString("\n")                              );
    }break;
    case QBP_MATRIX_TYPE_MUSSIX:
    {
        CQBPLogQueue::Push(QString("Experimento: MUSSIX")             +
                           QString("\n")                              );
    }break;
    }
    return true;
}

bool CQBPEngine::Print(bool pQBPAttitudeType)
{
    if(pQBPAttitudeType==true)
    {
        CQBPLogQueue::Push(QString("Utiliza Atitude: Sim")            +
                           QString("\n")                              );
    }
    else
    {
        CQBPLogQueue::Push(QString("Utiliza Atitude: Nao")            +
                           QString("\n")                              );
    }
    return true;
}

bool CQBPEngine::FillTestSet(int  pQBPDatasetType)
{
    //Preenche o TestSet
    switch(pQBPDatasetType)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        if(pQBPDataset->pQBPTestList.size()==0)return false;
        else
        {
           //Limpa TestSet
           if(pQBPTestSet.size()>0)
           {
               pQBPTestSet.clear();
               //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
               pQBPTestSet.shrink_to_fit();
           }

           //Preenche TestSet
           for(int i=0;i<(int)pQBPDataset->pQBPTestList.size();i++)
           {
               CQBPSong *tSong = new CQBPSong(pQBPDataset->pQBPTestList[i]);
               pQBPTestSet.push_back(tSong);
           }
           iQBPSearchDimension = (int)pQBPTestSet.size();
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        if(pQBPDataset->pQBPRandomList.size()==0)return false;
        else
        {
           //Limpa TestSet
           if(pQBPTestSet.size()>0)
           {
               pQBPTestSet.clear();
               //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
               pQBPTestSet.shrink_to_fit();
           }

           //Preenche TestSet
           for(int i=0;i<(int)pQBPDataset->pQBPRandomList.size();i++)
           {
               CQBPSong *tSong = new CQBPSong(pQBPDataset->pQBPRandomList[i]);
               pQBPTestSet.push_back(tSong);
           }
           iQBPSearchDimension = (int)pQBPTestSet.size();
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        if(pQBPDataset->pQBPValiList.size()==0)return false;
        else
        {
           //Limpa TestSet
           if(pQBPTestSet.size()>0)
           {
               pQBPTestSet.clear();
               //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
               pQBPTestSet.shrink_to_fit();
           }

           //Preenche TestSet
           for(int i=0;i<(int)pQBPDataset->pQBPValiList.size();i++)
           {
               CQBPSong *tSong = new CQBPSong(pQBPDataset->pQBPValiList[i]);
               pQBPTestSet.push_back(tSong);
           }

           iQBPSearchDimension = (int)pQBPTestSet.size();
        }
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        if(pQBPDataset->pQBPFullList.size()==0)return false;
        else
        {
           //Limpa TestSet
           if(pQBPTestSet.size()>0)
           {
               pQBPTestSet.clear();
               //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
               pQBPTestSet.shrink_to_fit();
           }

           //Preenche TestSet
           for(int i=0;i<(int)pQBPDataset->pQBPFullList.size();i++)
           {
               CQBPSong *tSong = new CQBPSong(pQBPDataset->pQBPFullList[i]);
               pQBPTestSet.push_back(tSong);
           }

           iQBPSearchDimension = (int)pQBPTestSet.size();
        }
    }break;
    }
    return true;
}

bool CQBPEngine::CalculateEvaluation(uint pQBPSearchID)
{
    CQBPSearch *tSearch = GetSearch(pQBPSearchID);

    //Incluido aqui atualização necessaria antes do calculo de avaliação(Ex. DatasetType)
    tSearch->setDatasetType(iQBPDatasetType);
    tSearch->setType(iQBPSearchType);
    tSearch->iQBPComparatorType = iQBPComparatorType;
    tSearch->iQBPPrecisionBalance = iQBPSearchPrecisionBalance;
    tSearch->iQBPResultSetBalance = iQBPSearchResultMax;

    iQBPSearchType     = QBP_SCH_TYPE_SET;

    tSearch->CalculateEvaluation();

    return true;
}

void CQBPEngine::SetSearchTimes(uint pQBPSearchID,
                    float pQBPGlobalSearchTime,
                    float pQBPInitializationSearchTime,
                    float pQBPProcessingSearchTime,
                    float pQBPPostProcessingSearchTime)
{
    CQBPSearch *tSearch = GetSearch(pQBPSearchID);

    //Atualiza os timelapses de busca
    tSearch->fQBPSearchElapsed   =pQBPGlobalSearchTime;
    tSearch->fQBPSearchElapsedPre=pQBPInitializationSearchTime;
    tSearch->fQBPSearchElapsedPro=pQBPProcessingSearchTime;
    tSearch->fQBPSearchElapsedPos=pQBPPostProcessingSearchTime;
}

void CQBPEngine::ClearSearchLists(uint pQBPSearchID)
{
    CQBPSearch *tSearch = GetSearch(pQBPSearchID);

    tSearch->pQBPSearchResultSet.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    tSearch->pQBPSearchResultSet.shrink_to_fit();

    //Colocado aqui temporariamente para testarmos o que consome tanta memoria durante os testes.
    tSearch->pQBPSearchAlignments.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    tSearch->pQBPSearchAlignments.shrink_to_fit();

    delete tSearch->pQBPSearchSong;
    tSearch->pQBPSearchSong=NULL;

}

bool CQBPEngine::FillSearchSets   (uint pQBPSearchID                    ,
                                   CQBPSong *pQBPSearchSong             ,
                                   vector<CQBPPriorityQueueNode>  pQBPSearchResultSet)
{
    CQBPSearch *tSearch = GetSearch(pQBPSearchID);

    //Limpa TestSet
    if(tSearch->pQBPSearchResultSet.size()>0)
    {
        tSearch->pQBPSearchResultSet.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        tSearch->pQBPSearchResultSet.shrink_to_fit();
    }

    tSearch->pQBPSearchSong = new CQBPSong(*pQBPSearchSong);

    //Preenche ResultSet
    for(int j=0;j<(int)pQBPSearchResultSet.size();j++)
    {
        tSearch->pQBPSearchResultSet.push_back(pQBPSearchResultSet[j]);
    }
    return true;
}

bool CQBPEngine::PreProcess (string pQBPSongName, int pQBPDatasetType)
{
    bool iRet;

    iRet=pQBPDataset->GetSongByName(pQBPSongName,pQBPUserSong,pQBPDatasetType);
    if(!iRet)
    {
        return false;//Not Find Any song to be used
    }

    //Preenche o Set de Busca(Limpa o anterior se necessário e somente para as listas de teste)
    //Removido para economizar processamento(Em teoria isto é feito na Construção do Dataset)
    //if(iQBPDatasetType!=QBP_LOAD_TARGET_DATASET)FillTestSet(iQBPDatasetType);

    //Seta Comparador desejado (SW , MUSSUM ou MUSSIX)
    SetComparatorType(iQBPComparatorType,iQBPDatasetType,iQBPAlgPostProcessingType);

    //Limpa o resultset de busca independente de busca
    pQBPResultSet.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPResultSet.shrink_to_fit();

    pQBPTPSet.QueueClean();
    pQBPFPSet.QueueClean();
    pQBPTNSet.QueueClean();
    pQBPFNSet.QueueClean();
    pQBPGLSet.QueueClean();

    return true;
}

bool CQBPEngine::PreProcess (string pQBPSongAName, string pQBPSongBName, int pQBPDatasetType)
{
    bool iRet;

    iRet=pQBPDataset->GetSongByName(pQBPSongAName,pQBPUserSong,pQBPDatasetType);
    if(!iRet)
    {
        return false;//Not Find Any song to be used
    }

    iRet=pQBPDataset->GetSongByName(pQBPSongBName,pQBPSystemSong,QBP_LOAD_TARGET_DATASET);
    if(!iRet)
    {
        return false;//Not Find Any song to be used
    }

    //Preenche o Set de Busca(Limpa o anterior se necessário e somente para as listas de teste)
    //Removido para economizar processamento(Em teoria isto é feito na Construção do Dataset)
    //if(iQBPDatasetType!=QBP_LOAD_TARGET_DATASET)FillTestSet(iQBPDatasetType);

    //Aloca Comparador desejado (SW , MUSSUM ou MUSSIX)
    SetComparatorType(iQBPComparatorType,iQBPDatasetType,iQBPPostProcessingType);

    //Limpa o resultset de busca independente de busca
    pQBPResultSet.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPResultSet.shrink_to_fit();

    pQBPTPSet.QueueClean();
    pQBPFPSet.QueueClean();
    pQBPTNSet.QueueClean();
    pQBPFNSet.QueueClean();
    pQBPGLSet.QueueClean();

    return true;
}

bool CQBPEngine::CompareSet()
{
    //Variaveis de processamento
    int               tQBPSearchScore;
    int               tQBPTotalNumberOfSearch=0;
    int               tQBPAttitudeDistance;

    for(int i=0;i<pQBPDataset->pQBPGenreList.size() ;i++)
    {
        for(int j=0;j<pQBPDataset->pQBPGenreList[i].pQBPSongList.size();j++)
        {
            if(bQBPUseAttitude==true)
            {
                tQBPAttitudeDistance = pQBPUserSong.Distance(pQBPDataset->pQBPGenreList[i].pQBPSongList[j]);
                if(tQBPAttitudeDistance>0)
                {
                    //atribui a score a classificação como TN e nem faz alinhamento...
                    pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification = QBP_SCH_CLASS_TN;
                    //atribui o score -1 na musica do testset
                    pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore = 0;

                    CQBPPriorityQueueNode *no = new CQBPPriorityQueueNode(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str(),
                                                                          pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore,
                                                                          pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification);
                    //Insere na lista de filtro de acordo com o tipo
                    switch(iQBPPostProcessingType)
                    {
                       case QBP_SCH_PPROC_QUEUE:{pQBPGLSet.EnqueueMax(no);}break;
                       case QBP_SCH_PPROC_MULTIQUEUE:{pQBPTNSet.EnqueueMax(no);}break;
                    }

                    continue;
                }
            }

            //Adiciona um Alinhamento para coleta.
            //Isto necessariamente precisa ser feito ANTES de um alinhamento!
            //Importante! foi colocado aqui devido ao attitude Gram recusar o alinhamento em caso de distancia grande.
            if(bQBPDebbugMode)pQBPComparator->AddAlignment();

            if(pQBPComparator->GetBufferType() == QBP_BUFFER_TYPE_STR)
            {
               //Seta o buffer de comparação Mussix...
               pQBPComparator->SetCompBuffer(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer,
                                             pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName);
            }
            else
            {
               //Seta o buffer de comparação Normal...
               pQBPComparator->SetCompBuffer(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer,
                                             pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName);
            }

            //Realiza comparação e retorna o score de similaridade na musica da base
            tQBPSearchScore = pQBPComparator->CompareBuffer();

            //atribui o score na musica do testset
            pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore = tQBPSearchScore;

            //Devido a agora termos a mesma anotação para as metricas, foi retirado o mapeamento
            //De acordo com o algoritmo sendo usado.
            //Agora encontramos o local onde a aprendizagem de maquina pode ser importante, pois
            //de acordo com a categoria criada define se o conteudo é relevante ou não...


            //Verifica a relevancia da musica
            //INCLUIR AQUI ML para realizar o Predict do buffer na SVM

            //Limpa prediction buffer
            //if(pQBPPredictionBuffer->pFeatureList.size()>0)pQBPPredictionBuffer->pFeatureList.clear();

            //Atribui a Categoria do buffer caso queiramos dar um chute também...
            //Atenção!! na pratica quando o sistema estiver rodando com ML não fazemos ideia da
            //Categoria real do buffer e isto é apenas para teste e realização do MRR...
            //pQBPPredictionBuffer->pListId = 0;

            //Preenche as features para Predição.
            //for(uint f=0;f<pQBPUserSong.pQBPNormalFeatures.size();f++)
            //{
            //    ClassifierFeature tFeat;
            //    tFeat.pFeatureId    = f+1;
            //    tFeat.pFeatureValue = pQBPUserSong.pQBPNormalFeatures[f].GetFeatureValue();
            //    pQBPPredictionBuffer->pFeatureList.push_back(tFeat);
            //}

            //Faz a predição da Categoria da musica sendo tocada.
            //pQBPUserSong.pQBPSongCategory = pQBPClassifierPool->Predict(pQBPPredictionBuffer);

            //Se pertence a mesma categoria da musica de comparação é um conteúdo relevante
            if(pQBPUserSong.pQBPSongCategory == pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory)
            {
               //Musica com score acima de 35% de acertos entra na lista
               if(tQBPSearchScore >= ((pQBPUserSong.pQBPSongBuffer.size()*iQBPSearchPrecisionBalance)/100))
               /*if(tQBPSearchScore >= ((pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer.size()*iQBPSearchPrecisionBalance)/100))*/
               {
                  //Relevante que entra na lista é TP - True Positive
                  pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification = QBP_SCH_CLASS_TP;

                  CQBPPriorityQueueNode *no = new CQBPPriorityQueueNode(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str(),
                                                                        pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore,
                                                                        pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification);
                  //Insere na lista de filtro de acordo com o tipo
                  switch(iQBPPostProcessingType)
                  {
                  case QBP_SCH_PPROC_QUEUE:{pQBPGLSet.EnqueueMax(no);}break;
                  case QBP_SCH_PPROC_MULTIQUEUE:{pQBPTPSet.EnqueueMax(no);}break;
                  }

               }
               else
               {
                   //Relevante que Não entra na lista é FN - False Negative
                   pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification = QBP_SCH_CLASS_FN;

                   CQBPPriorityQueueNode *no = new CQBPPriorityQueueNode(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str(),
                                                                         pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore,
                                                                         pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification);

                   //Insere na lista de filtro de acordo com o tipo
                   switch(iQBPPostProcessingType)
                   {
                   case QBP_SCH_PPROC_QUEUE:{pQBPGLSet.EnqueueMax(no);}break;
                   case QBP_SCH_PPROC_MULTIQUEUE:{pQBPFNSet.EnqueueMax(no);}break;
                   }

               }
            }
            else
            {
                //Como não faz parte da mesma categoria é irrelevante...maaasss...
                //Musica com score acima de 35% de acertos entra na lista
                if(tQBPSearchScore >= ((pQBPUserSong.pQBPSongBuffer.size()*iQBPSearchPrecisionBalance)/100))
                /*if(tQBPSearchScore >= ((pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer.size()*iQBPSearchPrecisionBalance)/100))*/
                {
                   //Irrelevante que entra na lista é considerado FP - False Positive
                   pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification = QBP_SCH_CLASS_FP;

                   CQBPPriorityQueueNode *no = new CQBPPriorityQueueNode(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str(),
                                                                         pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore,
                                                                         pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification);

                   //Insere na lista de filtro de acordo com o tipo
                   switch(iQBPPostProcessingType)
                   {
                   case QBP_SCH_PPROC_QUEUE:{pQBPGLSet.EnqueueMax(no);}break;
                   case QBP_SCH_PPROC_MULTIQUEUE:{pQBPFPSet.EnqueueMax(no);}break;
                   }

                }
                else
                {
                    //Irrelevante que não entra na lista é considerado TN - True Negative
                    pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification = QBP_SCH_CLASS_TN;

                    CQBPPriorityQueueNode *no = new CQBPPriorityQueueNode(pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str(),
                                                                          pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongScore,
                                                                          pQBPDataset->pQBPGenreList[i].pQBPSongList[j].pQBPSongClassification);

                    //Insere na lista de filtro de acordo com o tipo
                    switch(iQBPPostProcessingType)
                    {
                    case QBP_SCH_PPROC_QUEUE:{pQBPGLSet.EnqueueMax(no);}break;
                    case QBP_SCH_PPROC_MULTIQUEUE:{pQBPTNSet.EnqueueMax(no);}break;
                    }
                }
            }

            iQBPCompletedSearchs++;
            tQBPTotalNumberOfSearch++;

        }
    }

    return true;
}

bool CQBPEngine::CompareSong()
{
    //Variaveis de processamento
    int  tQBPAttitudeDistance;

    //Adiciona um Alinhamento para coleta.
    //Isto necessariamente precisa ser feito ANTES de um alinhamento!
    pQBPComparator->AddAlignment();

    //Realiza o Loop de Busca
    if(bQBPUseAttitude==true)
    {
        tQBPAttitudeDistance = pQBPUserSong.Distance(pQBPSystemSong);
        if(tQBPAttitudeDistance>0)return false;
    }

    //Realiza comparação e retorna o score de similaridade na musica da base
    pQBPSystemSong.pQBPSongScore = pQBPComparator->CompareBuffer();

    return true;
}

bool CQBPEngine::Process()
{
    if(iQBPSearchType==QBP_SCH_TYPE_SET)
    {
        //Seta o Buffer de Busca vindo da musica do usuario
        if(pQBPComparator->GetBufferType() == QBP_BUFFER_TYPE_STR)
        {
            pQBPComparator->SetUserBuffer(pQBPUserSong.pQBPMusixBuffer,pQBPUserSong.pQBPSongName);
        }
        else
        {
            pQBPComparator->SetUserBuffer(pQBPUserSong.pQBPSongBuffer,pQBPUserSong.pQBPSongName);
        }

        CompareSet();
    }

    if(iQBPSearchType==QBP_SCH_TYPE_SINGLE)
    {
        //Seta o Buffer de Busca vindo da musica do usuario
        if(pQBPComparator->GetBufferType() == QBP_BUFFER_TYPE_STR)
        {
            //Seta o Buffer MultiSpacial(Features de Nota)
            pQBPComparator->SetUserBuffer(pQBPUserSong.pQBPMusixBuffer,pQBPUserSong.pQBPSongName);
            pQBPComparator->SetCompBuffer(pQBPSystemSong.pQBPMusixBuffer,pQBPSystemSong.pQBPSongName);
        }
        else
        {
            //Seta o Buffer em String de Busca vindo da musica do usuario
            pQBPComparator->SetUserBuffer(pQBPUserSong.pQBPSongBuffer,pQBPUserSong.pQBPSongName);
            pQBPComparator->SetCompBuffer(pQBPSystemSong.pQBPSongBuffer,pQBPSystemSong.pQBPSongName);
        }

        CompareSong();
    }

    return true;
}

// sort pelo Score de Similaridade
struct {
    bool operator()(CQBPPriorityQueueNode a, CQBPPriorityQueueNode b) const
    {
        return a.pQBPSongScore > b.pQBPSongScore;
    }
} QBPRScoreGreater;

bool CQBPEngine::PosProcess()
{
    //faz o sort de scores de Similaridade
    //std::sort(pQBPResultSet.begin(), pQBPResultSet.end(), QBPRScoreGreater);

    //Pos-processamento utilizando 4 Slots
    //Incluidos na ordem de Relevantes(t/p) -> irrelevantes(t/p)
    if(iQBPPostProcessingType == QBP_SCH_PPROC_MULTIQUEUE)
    {
       while(!pQBPTPSet.QueueEmpty())
       {
           CQBPPriorityQueueNode tSong;

           pQBPTPSet.Dequeue(tSong.pQBPSongName,tSong.pQBPSongScore,tSong.pQBPSongClassification);

           pQBPResultSet.push_back(tSong);
       }

       while(!pQBPFNSet.QueueEmpty())
       {
           CQBPPriorityQueueNode tSong;

           pQBPFNSet.Dequeue(tSong.pQBPSongName,tSong.pQBPSongScore,tSong.pQBPSongClassification);

           pQBPResultSet.push_back(tSong);
       }

       while(!pQBPFPSet.QueueEmpty())
       {
           CQBPPriorityQueueNode tSong;

           pQBPFPSet.Dequeue(tSong.pQBPSongName,tSong.pQBPSongScore,tSong.pQBPSongClassification);

           pQBPResultSet.push_back(tSong);
       }

       while(!pQBPTNSet.QueueEmpty() && (pQBPResultSet.size()<=iQBPSearchResultMax))
       {
           CQBPPriorityQueueNode tSong;

           pQBPTNSet.Dequeue(tSong.pQBPSongName,tSong.pQBPSongScore,tSong.pQBPSongClassification);

           pQBPResultSet.push_back(tSong);
       }

       //No final faz um sort por escore de similaridade
       std::sort(pQBPResultSet.begin(), pQBPResultSet.end(), QBPRScoreGreater);
    }

    //PosProcessamento utilizando Fila Unica
    if(iQBPPostProcessingType == QBP_SCH_PPROC_QUEUE)
    {
       while(!pQBPGLSet.QueueEmpty())
       {
           CQBPPriorityQueueNode tSong;

           pQBPGLSet.Dequeue(tSong.pQBPSongName,tSong.pQBPSongScore,tSong.pQBPSongClassification);

           pQBPResultSet.push_back(tSong);
       }

       //No final faz um sort por escore de similaridade apenas para garantir....
       std::sort(pQBPResultSet.begin(), pQBPResultSet.end(), QBPRScoreGreater);
    }


    return true;
}
bool CQBPEngine::Search(string pQBPSearchName, string pQBPSongName, int  pQBPDatasetType, int pQBPComparatorType , bool pQBPUseAttitude)
{
    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    //CQBPLogQueue::Push(QString("*****************************************\n"));
    //CQBPLogQueue::Push(QString("*Inicio Busca                           *\n"));
    //CQBPLogQueue::Push(QString("*****************************************\n"));

    int tSearchID;

    //Cria arquivo
    std::filebuf fb;
    fb.open(QString("buscas/Busca%1.txt").arg(1).toStdString(), std::ofstream::app);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    pQBPSearchTimer.start();

    //Inicializa Parametros de Busca
    iQBPDatasetType    = pQBPDatasetType;
    iQBPComparatorType = pQBPComparatorType ;
    bQBPUseAttitude    = pQBPUseAttitude;
    iQBPSearchType     = QBP_SCH_TYPE_SET;

    pQBPActualTime = time(0);
    pQBPStartSTime = localtime(&pQBPActualTime);

    //CQBPLogQueue::Push(QString("Tempo Inicial : %1:%2:%3 \n").arg(pQBPStartSTime->tm_hour).arg(pQBPStartSTime->tm_min ).arg(pQBPStartSTime->tm_sec));

    //trava a log
    CQBPLogQueue::SetLock(true);

    //Adiciona esta busca na base de comparações
    //Precisa ser feito impreterivelmente ANTES de uma busca ser realizada!
    pQBPComparator->AddSearch(pQBPSearchName.c_str());

    //Realiza as tres etapas de uma Query MIR
    PreProcess(pQBPSongName,pQBPDatasetType);
    pQBPSearchElapsedPre = (float)pQBPSearchTimer.elapsed()/1000;
    pQBPSearchTimer.start();

    Process   (            );
    pQBPSearchElapsedPro = (float)pQBPSearchTimer.elapsed()/1000;
    pQBPSearchTimer.start();

    PosProcess(            );

    //Recupera o ID da busca
    tSearchID = pQBPComparator->GetCurrentSearch();

    //Preenche as listas de resultado
    FillSearchSets(tSearchID    ,
                   &pQBPUserSong,
                   pQBPResultSet);

    //Calcula Precision,Recall & FMeasure
    CalculateEvaluation(tSearchID);

    pQBPSearchElapsedPos = (float)pQBPSearchTimer.elapsed()/1000;
    pQBPSearchElapsed    = (float)(pQBPSearchElapsedPre + pQBPSearchElapsedPro + pQBPSearchElapsedPos);

    //Atualiza Timers de Processamento.
    SetSearchTimes(tSearchID,
                   pQBPSearchElapsed,
                   pQBPSearchElapsedPre,
                   pQBPSearchElapsedPro,
                   pQBPSearchElapsedPos);

    //Incrementa contador global
    iQBPGlobalSearchCounter++;

    //Imprime Consulta para limpar listas resultantes.
    //CQBPLogQueue::Push(QString("Musica Consultada : ") +
    //                   QString(pQBPUserSong.pQBPSongName.c_str()) +
    //                   QString("\n") );

    //CQBPLogQueue::Push(QString("Result List : \n"));
    //for(uint i=0;i<pQBPResultSet.size();i++)
    //{
    //    CQBPLogQueue::Push(QString(pQBPResultSet[i].pQBPSongName));
    //    CQBPLogQueue::Push(QString(" "));
    //    CQBPLogQueue::Push(QString("%1 ").arg(pQBPResultSet[i].pQBPSongScore));
    //
    //    switch(pQBPResultSet[i].pQBPSongClassification)
    //    {
    //    case QBP_SCH_CLASS_TP:{CQBPLogQueue::Push(QString("TP - True  Positive \n"));}break;
    //    case QBP_SCH_CLASS_FP:{CQBPLogQueue::Push(QString("FP - False Positive \n"));}break;
    //    case QBP_SCH_CLASS_TN:{CQBPLogQueue::Push(QString("TN - True  Negative \n"));}break;
    //    case QBP_SCH_CLASS_FN:{CQBPLogQueue::Push(QString("FN - False Negative \n"));}break;
    //    }
    //}

    CQBPSearch *tSearch = GetSearch(tSearchID);

    os  << fixed << setfill('0') << setw(5) << iQBPGlobalSearchCounter              << " ; " //identificador da busca

        << tSearch->sQBPSearchName.toStdString()                           << " ; " //Nome da Busca
        << tSearch->pQBPSearchSong->pQBPSongName                           << " ; " //Nome da Musica de Consulta

        << setfill('0') << setw(5) << tSearch->pQBPSearchAlignments.size() << " ; " //Numero de alinhamentos realizados(Obs:. apenas para Debbug)
        << setfill('0') << setw(5) << tSearch->iQBPPrecisionBalance        << " ; " //Balanço de Precisão Utilizado
        << setfill('0') << setw(5) << tSearch->iQBPResultSetBalance        << " ; " //Numero de Musicas no result set
        << setfill('0') << setw(5) << iQBPBufferSize                       << " ; " //Tamanho do Buffer(por enquanto pega daqui sem atualizar na busca...)
        << setfill('0') << setw(5) << tSearch->iQBPComparatorType          << " ; " //Algoritmo usado

        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPPrecision                       << " ; " //Precisão da busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPRecall                          << " ; " //Cobertura da Busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPFmeasure                        << " ; " //Media harmonica da busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPAccuracy                        << " ; " //acuracia da busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPReciprocalRank                  << " ; " //MRR  da busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPMeanSimilarityContourDistance   << " ; " //MSCD da busca
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPSearchElapsed                   << " ; " //Tempo total
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPSearchElapsedPre                << " ; " //Tempo pre-processamento
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPSearchElapsedPro                << " ; " //Tempo Processamento
        << setfill('0') << setw(7) << setprecision(4) << tSearch->fQBPSearchElapsedPos                << " \n";//Tempo Pos-Processamento

    //fecha o arquivo para evitar limpeza de valores.
    fb.close();

    if(!bQBPDebbugMode)
    {
       ClearSearchLists(tSearchID);
       pQBPComparator->CleanUp();
    }

    //libera a log
    CQBPLogQueue::SetLock(false);

    pQBPActualTime = time(0);
    pQBPFinishTime = localtime(&pQBPActualTime);
    //CQBPLogQueue::Push(QString("Tempo Final : %1:%2:%3 \n").arg(pQBPFinishTime->tm_hour).arg(pQBPFinishTime->tm_min ).arg(pQBPFinishTime->tm_sec));

    //CQBPLogQueue::Push(QString("*****************************************\n"));
    //CQBPLogQueue::Push(QString("*Fim busca                              *\n"));
    //CQBPLogQueue::Push(QString("*****************************************\n"));

    //libera a engine para novas consultas
    SetLock(false);

    return true;
}

bool CQBPEngine::Search(string pQBPSearchName, string pQBPSongAName, string pQBPSongBName, int  pQBPDatasetType, int pQBPComparatorType , bool pQBPUseAttitude)
{
    uint tSearchID=0;

    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Inicio Busca                           *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));

    //Inicializa Parametros de Busca
    iQBPDatasetType    = pQBPDatasetType;
    iQBPComparatorType = pQBPComparatorType ;
    bQBPUseAttitude    = pQBPUseAttitude;
    iQBPSearchType     = QBP_SCH_TYPE_SINGLE;

    pQBPActualTime = time(0);
    pQBPStartSTime = localtime(&pQBPActualTime);

    CQBPLogQueue::Push(QString("Tempo Inicial : %1:%2:%3 \n").arg(pQBPStartSTime->tm_hour).arg(pQBPStartSTime->tm_min ).arg(pQBPStartSTime->tm_sec));

    //trava a log
    CQBPLogQueue::SetLock(true);

    //Adiciona esta busca na base de comparações
    //Precisa ser feito impreterivelmente ANTES de uma busca ser realizada!
    pQBPComparator->AddSearch(pQBPSearchName.c_str());

    //Realiza as tres etapas de uma Query MIR
    PreProcess(pQBPSongAName,pQBPSongBName,pQBPDatasetType);
    Process   (                           );
    PosProcess(                           );

    //libera a log
    CQBPLogQueue::SetLock(false);

    pQBPFinishTime = localtime(&pQBPActualTime);

    CQBPLogQueue::Push(QString("Tempo Final : %1:%2:%3 \n").arg(pQBPFinishTime->tm_hour).arg(pQBPFinishTime->tm_min ).arg(pQBPFinishTime->tm_sec));
    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Fim busca                              *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));

    //libera a engine para novas consultas
    SetLock(false);

    return true;
}

bool CQBPEngine::CreateDefaultPool()
{
    for(int i=0;i<GenresLoaded();i++)
    {
        QString tCategoryName;
        int     tQtdSongs;

        GetGenreData(i,tCategoryName,tQtdSongs);

        AddClassifier(i,QBP_SVM_TRAIN_DATASET,true);
    }
    return true;
}

bool CQBPEngine::LoadPool()
{
    pQBPClassifierPool->LoadPool(1);
    return true;
}

bool CQBPEngine::AddClassifier  (uint pQBP_TargetCategory,int pQBPDatasetType,bool pQBPNormalize)
{
    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Adicionando Classificador no Pool      *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));

    string pQBPath = QString("svm/qbpSVMCategory%1.train").arg(pQBP_TargetCategory).toStdString();

    switch(pQBPDatasetType)
    {
    case QBP_SVM_TRAIN_TESTLIST:
    {
        CQBPLogQueue::Push(QString("Construindo Dataset de Teste... \n"));
        BuildTestSet(QBP_FORM_TYPE_PERC_15);

        if(pQBPNormalize)
        {
            CQBPLogQueue::Push(QString("Normalizando Dataset de Teste... \n"));
            pQBPDataset->BuildNormalFeatures(QBP_LOAD_TARGET_TESTSET);
        }
    }break;
    case QBP_SVM_TRAIN_VALILIST:
    {
        CQBPLogQueue::Push(QString("Construindo Dataset de Validação... \n"));
        BuildValiSet(QBP_FORM_TYPE_PERC_15);

        if(pQBPNormalize)
        {
            CQBPLogQueue::Push(QString("Normalizando Dataset de Validação... \n"));
            pQBPDataset->BuildNormalFeatures(QBP_LOAD_TARGET_VALISET);
        }
    }break;
    }


    CQBPLogQueue::Push(QString("Gravando Dataset no Disco para Futura Consulta... \n"));
    CreateTrainFile(pQBPath,pQBPDatasetType,pQBPNormalize,true,pQBP_TargetCategory);

    pQBPClassifierPool->AddClassifier(pQBP_TargetCategory,QString(pQBPath.c_str()));

    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Fim Treinamento SVM                    *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));
    return true;
}

bool CQBPEngine::TrainSVM(string pQBPath,int pQBPDatasetType,bool pQBPNormalize,bool pQBPUseCategory, int pQBPCategory)
{
    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Treinamento SVM                        *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));
    switch(pQBPDatasetType)
    {
    case QBP_SVM_TRAIN_TESTLIST:
    {
        CQBPLogQueue::Push(QString("Construindo Dataset de Teste... \n"));
        BuildTestSet(QBP_FORM_TYPE_PERC_15);

        if(pQBPNormalize)
        {
            CQBPLogQueue::Push(QString("Normalizando Dataset de Teste... \n"));
            pQBPDataset->BuildNormalFeatures(QBP_LOAD_TARGET_TESTSET);
        }
    }break;
    case QBP_SVM_TRAIN_VALILIST:
    {
        CQBPLogQueue::Push(QString("Construindo Dataset de Validação... \n"));
        BuildValiSet(QBP_FORM_TYPE_PERC_15);

        if(pQBPNormalize)
        {
            CQBPLogQueue::Push(QString("Normalizando Dataset de Validação... \n"));
            pQBPDataset->BuildNormalFeatures(QBP_LOAD_TARGET_VALISET);
        }
    }break;
    }


    CQBPLogQueue::Push(QString("Gravando Dataset no Disco para Futura Consulta... \n"));
    CreateTrainFile(pQBPath,pQBPDatasetType,pQBPNormalize,pQBPUseCategory,pQBPCategory);

    CQBPLogQueue::Push(QString("Carregando Problema de Treinamento... \n"));
    pQBPClassifier->LoadQBPProblem(pQBPath,true);

    CQBPLogQueue::Push(QString("Realizando Treinamento... \n"));
    int npos = (int)pQBPath.find(".train");
    if (npos != -1)
    {
        pQBPath.erase(npos, 6);
    }

    pQBPClassifier->Train(QString(QString(pQBPath.c_str()) + QString(".model")).toStdString());

    CQBPLogQueue::Push(QString("Realizando Crossvalidation de Treinamento... \n"));
    pQBPClassifier->CrossValidation();

    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Fim Treinamento SVM                    *\n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));
    return true;
}

bool CQBPEngine::LoadSVMModel(string pQBPath)
{
    //procedimentos para testar a predição
    pQBPClassifier->LoadModel(pQBPath);
    return true;
}

bool CQBPEngine::MusicPlayer()
{
    CQBPLogQueue::Push(QString("*****************************************\n"));
    CQBPLogQueue::Push(QString("*Carregando todas as musicas da base...  \n"));
    CQBPLogQueue::Push(QString("*****************************************\n"));

    //Limpa o Dataset para garantir lista nova.
    pQBPDataset->ClearDataset(QBP_LOAD_TARGET_DATASET);

    //Carrega base full construida
    pQBPDataset->LoadDataset("playlist", QBP_LOAD_TYPE_MIDI, QBP_LOAD_TARGET_MUSPLAY);

    //pQBPEngineOutputLog.append("Tocando as Musicas do Dataset...  \n");
    for (int i = 0; i < (int)pQBPDataset->pQBPMusicPlayer.size(); i++)
    {
        CQBPLogQueue::Push(QString("*****************************************\n"));
        CQBPLogQueue::Push(QString("Musica Atual: "));
        CQBPLogQueue::Push(QString(pQBPDataset->pQBPMusicPlayer[i].pQBPSongName.c_str()));


        //Toca a musica nota por nota.
        CQBPLogQueue::Push(QString("Toca a musica nota por nota.\n"));
        pQBPDataset->pQBPKeyboard.Play(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes);


        CQBPLogQueue::Push(QString("Tocando ela 24 semi-tons abaixo(2 Oitavas)...\n"));
        pQBPDataset->pQBPKeyboard.TuneDown(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes, 24);
        pQBPDataset->pQBPKeyboard.Play(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes);

        CQBPLogQueue::Push(QString("Tocando ela 1 semi-ton acima...\n"));
        pQBPDataset->pQBPKeyboard.TuneUp(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes, 10);
        pQBPDataset->pQBPKeyboard.Play(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes);

        CQBPLogQueue::Push(QString("Agora com todas as notas na oitava 5! \n"));
        pQBPDataset->pQBPKeyboard.Transpose(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes, 5);
        pQBPDataset->pQBPKeyboard.Play(pQBPDataset->pQBPMusicPlayer[i].pQBPNotes);

    }

    return true;
}

int CQBPEngine::SongsLoaded()
{
    return pQBPDataset->pQBPQtdSongs;
}

int CQBPEngine::GenresLoaded()
{
    int tQtdGenres = (int)pQBPDataset->pQBPGenreList.size();
    return tQtdGenres;
}

int CQBPEngine::ChordsLoaded()
{
    int tQtdChords = (int)pQBPDataset->pQBPChords.size();
    return tQtdChords;
}

int CQBPEngine::EvaluationsLoaded()
{
    int tQtdSearchs = pQBPComparator->pQBPSearchResults->getQtdSearchs();
    return tQtdSearchs;
}

bool CQBPEngine::GetGenreData(int pQBPGenreId,QString &pQBPName,int &pQBPNumberSongs)
{
   pQBPName        = pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPGenreName.c_str();
   pQBPNumberSongs = (int)pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPSongList.size();
   return true;
}

bool CQBPEngine::GetChordData(int pQBPChordId , QString &pQBPChordName , int &pQBPNote01, int &pQBPNote02, int &pQBPNote03, int &pQBPNote04, int &pQBPNote05, int &pQBPNote06)
{
   pQBPChordName =      pQBPDataset->pQBPChords[pQBPChordId].sQBPChordName;
   pQBPNote01    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[0].iQBP_Pitch;
   pQBPNote02    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[1].iQBP_Pitch;
   pQBPNote03    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[2].iQBP_Pitch;
   pQBPNote04    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[3].iQBP_Pitch;
   pQBPNote05    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[4].iQBP_Pitch;
   pQBPNote06    = (int)pQBPDataset->pQBPChords[pQBPChordId].pQBPChordBuffer[5].iQBP_Pitch;
   return true;
}

bool CQBPEngine::GetSongData (int pQBPGenreId,int pQBPMusicId,QString &pQBPName,int &pQBPNumberOfNotes,int &pQBPNumberOfFeatures,int &pQBPNumberOfCustomFeatures)
{
   pQBPName                   =      pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPSongList[pQBPMusicId].pQBPSongName.c_str();
   pQBPNumberOfNotes          = (int)pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPSongList[pQBPMusicId].pQBPMusixBuffer.size();
   pQBPNumberOfFeatures       = (int)pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPSongList[pQBPMusicId].pQBPJSymboFeatures.size();
   pQBPNumberOfCustomFeatures = (int)pQBPDataset->pQBPGenreList[pQBPGenreId].pQBPSongList[pQBPMusicId].pQBPCustomFeatures.size();
   return true;
}

bool CQBPEngine::GetFeatureData(int pQBPGenreId ,int pQBPMusicId,int pQBPFeatureId,QString &pQBPFeatureName,int &pQBPFeatureType,double &pQBPFeatureValue)
{
   pQBPFeatureName          = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureName().c_str();

   pQBPFeatureType          = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureId();

   pQBPFeatureValue         = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureValue();

   return true;
}

bool CQBPEngine::GetCustomFeatureData(int pQBPGenreId ,int pQBPMusicId,int pQBPFeatureId,QString &pQBPFeatureName,int &pQBPFeatureType,double &pQBPFeatureValue)
{
   pQBPFeatureName          = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureName().c_str();

   pQBPFeatureType          = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureId();

   pQBPFeatureValue         = pQBPDataset->pQBPGenreList     [pQBPGenreId].
                                           pQBPSongList      [pQBPMusicId].
                                           pQBPCustomFeatures[pQBPFeatureId].GetFeatureValue();

   return true;
}

bool CQBPEngine::GetSearchData(int &iQBP_SearchDimension, int &iQBP_CompletedSearchs)
{
   iQBP_SearchDimension  = iQBPSearchDimension;
   iQBP_CompletedSearchs = iQBPCompletedSearchs;
   return true;
}

CQBPSearch * CQBPEngine::GetSearch(int pQBPSearchID)
{
    return pQBPComparator->pQBPSearchResults->getSearch(pQBPSearchID);
}

bool CQBPEngine::GetListData (int pQBPListType,int pQBPMusicId,QString &pQBPName,int &pQBPNumberOfNotes,int &pQBPSearchScore)
{
    switch(pQBPListType)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        pQBPName          = pQBPDataset->pQBPTestList[pQBPMusicId].pQBPSongName.c_str();
        pQBPNumberOfNotes = (int)pQBPDataset->pQBPTestList[pQBPMusicId].pQBPMusixBuffer.size();
        pQBPSearchScore   = pQBPDataset->pQBPTestList[pQBPMusicId].pQBPSongScore;
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        pQBPName          = pQBPDataset->pQBPValiList[pQBPMusicId].pQBPSongName.c_str();
        pQBPNumberOfNotes = (int)pQBPDataset->pQBPValiList[pQBPMusicId].pQBPMusixBuffer.size();
        pQBPSearchScore   = pQBPDataset->pQBPValiList[pQBPMusicId].pQBPSongScore;
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        pQBPName          = pQBPDataset->pQBPFullList[pQBPMusicId].pQBPSongName.c_str();
        pQBPNumberOfNotes = (int)pQBPDataset->pQBPFullList[pQBPMusicId].pQBPMusixBuffer.size();
        pQBPSearchScore   = pQBPDataset->pQBPFullList[pQBPMusicId].pQBPSongScore;
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        pQBPName          = pQBPDataset->pQBPRandomList[pQBPMusicId].pQBPSongName.c_str();
        pQBPNumberOfNotes = (int)pQBPDataset->pQBPRandomList[pQBPMusicId].pQBPMusixBuffer.size();
        pQBPSearchScore   = pQBPDataset->pQBPRandomList[pQBPMusicId].pQBPSongScore;
    }break;
    }

   return true;
}


bool CQBPEngine::GetTestData(int pQBPMusicId, QString &pQBPName, int &pQBPNumberOfNotes, int &pQBPSearchScore, int &pQBPSearchClassification)
{
    pQBPName                   = pQBPTestSet[pQBPMusicId]->pQBPSongName.c_str();
    pQBPNumberOfNotes          = (int)pQBPTestSet[pQBPMusicId]->pQBPMusixBuffer.size();
    pQBPSearchScore            = pQBPTestSet[pQBPMusicId]->pQBPSongScore;
    pQBPSearchClassification   = pQBPTestSet[pQBPMusicId]->pQBPSongClassification;
   return true;
}

int  CQBPEngine::ListGetSize (int pQBPListType)
{
    switch(pQBPListType)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        return (int)pQBPDataset->pQBPTestList.size();
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        return (int)pQBPDataset->pQBPValiList.size();
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        return (int)pQBPDataset->pQBPFullList.size();
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        return (int)pQBPDataset->pQBPRandomList.size();
    }break;
    }
    return 0;
}

int  CQBPEngine::TestGetSize ()
{
    return (int)pQBPTestSet.size();
}

bool CQBPEngine::PlaySongByName(QString pQBPName)
{
   CQBPSong tSong;
   CQBPLogQueue::Push(QString("Tocando a Musica: ")+ pQBPName + QString("\n"));
   pQBPDataset->GetSongByName(pQBPName.toStdString(),tSong,QBP_LOAD_TARGET_DATASET);
   pQBPDataset->PlaySong(tSong);
   return true;
}

bool CQBPEngine::SetComparatorType(int pQBPComparatorType, uint pQBPDatasetType , uint pQBPProcType)
{
   //Cria o comparador de similaridade entre musicas
   pQBPComparator->SetCompType(pQBPComparatorType,pQBPProcType);
   pQBPComparator->SetDatasetType(pQBPDatasetType);
   return true;
}
