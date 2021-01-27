#include "QBP_ClassifierPool.h"
#include "QBP_ClassifierSVM.h"

CQBPClassifierPool::CQBPClassifierPool()
{

}

void CQBPClassifierPool::AddClassifier(uint pQBP_TargetCategory, QString pQBP_TrainPath)
{
    CQBPClassifierSVM *tClass;

    tClass = new CQBPClassifierSVM();

    CQBPLogQueue::Push(QString("Carregando Problema de Treinamento - Categoria %1  \n").arg(pQBP_TargetCategory));
    tClass->LoadQBPProblem(pQBP_TrainPath.toStdString(),true);
    CQBPLogQueue::Push(QString("Realizando Treinamento... \n"));
    tClass->Train(pQBP_TrainPath.toStdString());
    CQBPLogQueue::Push(QString("Realizando Crossvalidation de Treinamento - Categoria %1 \n").arg(pQBP_TargetCategory));
    tClass->CrossValidation();

    pQBPClassifierPool.push_back(tClass);
}

int CQBPClassifierPool::Predict(ClassifierList *pQBPPredictionBuffer)
{
    int tPredictedCategory=11;
    int tValidPrediction;
    for(uint i=0;i<pQBPClassifierPool.size();i++)
    {
        tValidPrediction = pQBPClassifierPool[i]->Predict(pQBPPredictionBuffer);

        CQBPLogQueue::Push(QString("Predição Classificador %1 Genero Enviado %2 Resultado %3 \n").arg(i).arg(pQBPPredictionBuffer->pListId).arg(tValidPrediction));

        tPredictedCategory = tValidPrediction;

    }

    return tPredictedCategory;
}

int CQBPClassifierPool::Predict(ClassifierList *pQBPPredictionBuffer,uint pClassifierId)
{
    int tPredictedCategory=11;
    int tValidPrediction;

    tValidPrediction = pQBPClassifierPool[pClassifierId]->Predict(pQBPPredictionBuffer);

    CQBPLogQueue::Push(QString("Predição Classificador %1 Genero Enviado %2 Resultado %3 \n").arg(pClassifierId).arg(pQBPPredictionBuffer->pListId).arg(tValidPrediction));

    tPredictedCategory = tValidPrediction;

    return tPredictedCategory;
}

void CQBPClassifierPool::LoadPool(uint pQBP_PoolType)
{
    switch(pQBP_PoolType)
    {
    case 0://Pool
    {
        for(int i=0;i<11;i++)
        {
            CQBPClassifierSVM *tClass;

            tClass = new CQBPClassifierSVM();

            tClass->LoadModel(QString("svm/qbpSVMCategory%1.model").arg(i).toStdString());

            pQBPClassifierPool.push_back(tClass);
        }
    }break;
    case 1://Monolitico
    {
        CQBPClassifierSVM *tClass;

        tClass = new CQBPClassifierSVM();

        tClass->LoadModel(QString("svm/qbpSVM.model").toStdString());

        pQBPClassifierPool.push_back(tClass);
    }
    }

}
