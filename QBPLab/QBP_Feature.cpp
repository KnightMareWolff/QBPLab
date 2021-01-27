#include "QBP_Feature.h"



CQBPFeature::CQBPFeature()
{
}

CQBPFeature::CQBPFeature(const CQBPFeature &obj)
{
    pQBP_FeatureTypeId =obj.pQBP_FeatureTypeId;
    pQBP_FeatureName   =obj.pQBP_FeatureName;
    pQBP_FeatureValue  =obj.pQBP_FeatureValue;
}

CQBPFeature::CQBPFeature(double pQBPFeatureTypeId, string pQBPFeatureName, double pQBPFeatureValue)
{
    pQBP_FeatureTypeId = pQBPFeatureTypeId;
    pQBP_FeatureName   = pQBPFeatureName;
    pQBP_FeatureValue  = pQBPFeatureValue;
}

CQBPFeature::~CQBPFeature()
{
}

bool CQBPFeature::GetFeatureData(double &pQBPFeatureTypeId, string &pQBPFeatureName, double &pQBPFeatureValue)
{
    pQBPFeatureTypeId = pQBP_FeatureTypeId;
    pQBPFeatureName   = pQBP_FeatureName;
    pQBPFeatureValue  = pQBP_FeatureValue;
    return true;
}

double CQBPFeature::GetFeatureValue()
{
    return pQBP_FeatureValue;
}

double CQBPFeature::GetFeatureId()
{
    return pQBP_FeatureTypeId;
}
string CQBPFeature::GetFeatureName()
{
    return pQBP_FeatureName;
}
