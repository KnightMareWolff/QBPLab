#ifndef QBP_CLASSIFIERSVM_H
#define QBP_CLASSIFIERSVM_H

#include "QBP_GlobalDef.h"
#include "QBP_LogQueue.h"
#include "QBP_Classifier.h"

class CQBPClassifierSVM : public CQBPClassifier
{
public:
     CQBPClassifierSVM();
    ~CQBPClassifierSVM();

    //Hinherited Functions
    bool LoadModel(string  pQBPath);
    bool SaveModel(string  pQBPath);
    bool Train    (string  pQBPath);
    int  Predict(ClassifierList *pQBPPredictionBuffer);
    bool ShowStatistics();

    bool BuildXSpace();
    bool CrossValidation();

    void   SetType    (int    pQBPSVMTp       ){svm->setType(pQBPSVMTp);}
    double GetType    (                       ){return svm->getType();}
    void   SetKernel  (int    pQBPKernel      ){svm->setKernel(pQBPKernel);}
    double GetKernel  (                       ){return svm->getKernelType();}
    void   SetGamma   (double pQBPGamma       ){svm->setGamma(pQBPGamma);}
    double GetGamma   (                       ){return svm->getGamma();}
    void   SetDegree  (int    pQBPDegree      ){svm->setDegree(pQBPDegree);}
    double GetDegree  (                       ){return svm->getDegree();}
    void   SetCoef0   (double pQBPCoef0       ){svm->setCoef0(pQBPCoef0);}
    double GetCoef0   (                       ){return svm->getCoef0();}
    void   SetC       (double pQBPC           ){svm->setC(pQBPC);}
    double GetC       (                       ){return svm->getC();}
    void   SetFolds   (int pQBPFolds          ){iQBPQtdFoldValidation = pQBPFolds;}
    int    GetFolds   (                       ){return iQBPQtdFoldValidation;}
    void   SetCategory(int pQBPCategory       ){iQBPClassifierCategory = pQBPCategory;}
    int    GetCategory(                       ){return iQBPClassifierCategory;}

private:
    //Dados para funcionamento da SVM
    Ptr<SVM> svm;

    Mat pQBPTrainFeatures;
    Mat pQBPTrainLabels;

    Mat pQBPTestFeatures;
    Mat pQBPTestLabels;

    Mat pQBPPredictBuffer;

    //Crossvalidation
    int iQBPQtdFoldValidation;
    int iQBPClassifierCategory;

};

#endif // QBP_CLASSIFIERSVM_H
