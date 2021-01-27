#include "QBP_ClassifierSVM.h"


CQBPClassifierSVM::CQBPClassifierSVM()
{
   svm = ml::SVM::create();
   svm->setType(ml::SVM::ONE_CLASS);
   svm->setKernel(ml::SVM::CHI2);
   svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
   svm->setGamma(3);
   svm->setNu(0.5);
}


CQBPClassifierSVM::~CQBPClassifierSVM()
{

}


bool CQBPClassifierSVM::BuildXSpace()
{
    vector<float> trainingData;
    vector<int>   responsesData;

    for(int i=0; i< pQBPClassifierList.pProblemList.size(); i++)
    {
        for(int j=0;j<pQBPClassifierList.pProblemList[i].pFeatureList.size();j++)
        {
            float tFeatVal = pQBPClassifierList.pProblemList[i].pFeatureList[j].pFeatureValue;

            trainingData.push_back(tFeatVal);
        }

        int tClassLabel = pQBPClassifierList.pProblemList[i].pListId;
        responsesData.push_back(tClassLabel);
    }

    pQBPTrainFeatures = Mat(trainingData .size()/22  ,22, CV_32F, &trainingData [0]);
    pQBPTrainLabels   = Mat((int)responsesData.size(), 1, CV_32S, &responsesData[0]);


    //Tudo ocorreu bem!
    return true;
}

bool CQBPClassifierSVM::LoadModel(string pQBPath)
{

    //Ocorreu tudo bem!
    return true;
}

bool CQBPClassifierSVM::SaveModel(string pQBPath)
{

    //Ocorreu tudo bem!
    return true;
}

bool CQBPClassifierSVM::CrossValidation()
{

    return true;
}

bool CQBPClassifierSVM::Train(string  pQBPath)
{
    if(pQBPLoaded)
    {
        BuildXSpace();
        //svm->train(pQBPTrainFeatures,ROW_SAMPLE,pQBPTrainLabels);
        svm->trainAuto(pQBPTrainFeatures,ROW_SAMPLE,pQBPTrainLabels);
        CQBPLogQueue::Push(QString("Aguardando treinamento da Base..."));
        while(!svm->isTrained())
        {
            CQBPLogQueue::Push(QString("."));
        }
        if(svm->isTrained())
        {
           svm->save(pQBPath);
           CQBPLogQueue::Push(QString("Modelo Salvo com sucesso!"));
        }
        svm->clear();
        return true;
    }
    return false;
}

int CQBPClassifierSVM::Predict(ClassifierList *pQBPPredictionBuffer)
{
    return (int)0;
}

bool CQBPClassifierSVM::ShowStatistics()
{
    return true;
}

