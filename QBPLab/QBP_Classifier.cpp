#include "QBP_Classifier.h"

CQBPClassifier::CQBPClassifier()
{
   pQBPLoaded = false;
}


CQBPClassifier::~CQBPClassifier()
{

}


bool CQBPClassifier::Clear()
{
    //Limpa a feature list de cada problema
    for (int i = 0; i < pQBPClassifierList.pProblemList.size(); i++)
    {
        pQBPClassifierList.pProblemList[i].pFeatureList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPClassifierList.pProblemList[i].pFeatureList.shrink_to_fit();
    }

    //Limpa os problemas
    pQBPClassifierList.pProblemList.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPClassifierList.pProblemList.shrink_to_fit();

    //atualiza contadores
    pQBPClassifierList.pProblemId = 0;
    iQBPNumFeatures = 0;
    iQBPNumClasses = 0;

    pQBPLoaded = false;

    return true;
}

bool CQBPClassifier::LoadQBPProblem(string pQBPath, bool pQBPClear = true)
{
    int    tFeatureCounter = 0;
    int    tClassCounter   = 0;

    //Abre arquivo para leitura
    std::filebuf fb;
    fb.open(pQBPath, std::ios::in);

    //Grava dados na stream de arquivo
    std::istream is(&fb);

    //Limpa todos os dados do classificador(Modelo , Parametros e Listas), caso solicitado.
    if(pQBPClear)Clear();

    //Carrega o nome e buffer para pesquisa e extração de valores
    while (!is.eof())
    {
        string tFeatures;
        int    tFeatureClass;
        int    tFeatureId;
        double tFeatureValue;

        ClassifierList    tClassList  ;//Lista de classes de treino
        ClassifierFeature tFeature    ;//Lista de features das classes

        getline(is, tFeatures);

        int npos;

        if(tFeatures.empty())continue;
        //Procura pelo registro de classe do problema
        npos = (int)tFeatures.find("|");
        if (npos != -1)
        {
            tFeatureClass = atoi(tFeatures.substr(0, npos).c_str());
            tFeatures.erase(0, tFeatures.substr(0, npos+1).size());

            tClassList.pListId = tFeatureClass;
        }
        //busca as features da classe
        while ((npos = (int)tFeatures.find("|")) != -1)
        {
            int nfold;

            nfold = (int)tFeatures.find(":");

            tFeatureId = atoi(tFeatures.substr(0, nfold).c_str());
            tFeatures.erase(0, tFeatures.substr(0, nfold+1).size());

            nfold = (int)tFeatures.find("|");

            tFeatureValue = atof(tFeatures.substr(0, npos).c_str());
            tFeatures.erase(0, tFeatures.substr(0, nfold+1).size());

            tFeature.pFeatureId = tFeatureId;
            tFeature.pFeatureValue = tFeatureValue;

            tClassList.pFeatureList.push_back(tFeature);

            tFeatureCounter++;
        }

        //inclui a classe do problema na lista
        pQBPClassifierList.pProblemList.push_back(tClassList);
        tClassCounter++;
    }

    //Atualiza contadores
    iQBPNumFeatures = tFeatureCounter;
    iQBPNumClasses  = tClassCounter;

    //fecha arquivo de entrada
    fb.close();

    pQBPLoaded = true;

    return true;
}

bool CQBPClassifier::LoadQBPBuffer(ClassifierList *pQBPPredictionBuffer)
{
    //Caso ocorra algum problema na limpeza de lista de predição
    if(!Clear())return false;

    //Adiciona o Buffer de features no problema
    pQBPClassifierList.pProblemId = 0;
    pQBPClassifierList.pProblemList.push_back(*pQBPPredictionBuffer);

    //repassa o numero de features e classes constantes nas listas agora.(Neste caso apenas 1 classe e lista de features)
    iQBPNumFeatures = (int)pQBPPredictionBuffer->pFeatureList.size();//Numero total de features carregadas
    iQBPNumClasses  = 1;//Numero total de classes no XSpace

    pQBPLoaded = true;
    //Tudo ocorreu bem!
    return true;
}


bool CQBPClassifier::LoadModel(string      pQBPath)
{

    //Ocorreu tudo bem!
    return true;
}

bool CQBPClassifier::SaveModel(string      pQBPath)
{
    //Ocorreu tudo bem!
    return true;
}

bool CQBPClassifier::Train(string  pQBPath)
{
    //Treina um modelo de predição através do problema e parametros carregados
    //pQBPSvmModel = svm_train(&pQBPSvmProblem, &pQBPSvmParameter);

    //if (svm_save_model(pQBPath.c_str(), pQBPSvmModel))
    //{
    //    fprintf(stderr, "can't save model to file %s\n", "svm/qbpsvmtrain.model");
    //    CQBPLogQueue::Push(QString("Não pude salvar arquivo model: ") + QString("svm/qbpSVM.model \n"));
    //    return false;
    //}

    return true;
}

int CQBPClassifier::Predict(ClassifierList *pQBPPredictionBuffer)
{
    return (int)0;
}

bool CQBPClassifier::ShowStatistics()
{
    return true;
}
