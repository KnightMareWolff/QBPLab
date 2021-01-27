#ifndef QBP_CLASSIFIERPOOL_H
#define QBP_CLASSIFIERPOOL_H

#include "QBP_Classifier.h"

class CQBPClassifierPool
{
public:
    CQBPClassifierPool();

    void AddClassifier(uint pQBP_TargetCategory,QString pQBP_TrainPath);
    int  Predict      (ClassifierList *pQBPPredictionBuffer);
    int  Predict      (ClassifierList *pQBPPredictionBuffer,uint pClassifierId);
    void LoadPool     (uint pQBP_PoolType);

private:
    vector<CQBPClassifier *> pQBPClassifierPool;
};

#endif // QBP_CLASSIFIERPOOL_H
