#include "QBP_FeatureType.h"



CQBPFeatureType::CQBPFeatureType()
{
}

CQBPFeatureType::CQBPFeatureType(string pQBPFeatureName       ,
                                 string pQBPFeatureDescription,
                                 int pQBPFeatureDimensions    ,
                                 bool pQBPFeatureSequential   ,
                                 bool pQBPFeatureCustom       )
{
    pQBP_FeatureName        = pQBPFeatureName;
    pQBP_FeatureDescription = pQBPFeatureDescription;
    pQBP_FeatureDimensions  = pQBPFeatureDimensions;
    pQBP_FeatureSequential  = pQBPFeatureSequential;
    pQBP_FeatureCustom      = pQBPFeatureCustom;
}

CQBPFeatureType::~CQBPFeatureType()
{
}

bool CQBPFeatureType::GetFeatureTypeData(string &pQBPFeatureName,
                                         string &pQBPFeatureDescription,
                                         int    &pQBPFeatureDimensions,
                                         bool   &pQBPFeatureSequential,
                                         bool   &pQBPFeatureCustom)
{
    pQBPFeatureName        = pQBP_FeatureName;
    pQBPFeatureDescription = pQBP_FeatureDescription;
    pQBPFeatureDimensions  = pQBP_FeatureDimensions;
    pQBPFeatureSequential  = pQBP_FeatureSequential;
    pQBPFeatureCustom      = pQBP_FeatureCustom;
    return true;
}

string CQBPFeatureType::GetFeatureName()
{
    return pQBP_FeatureName;
}

bool CQBPFeatureType::GetDimensions(int &pQBPFeatureDimensions)
{
    pQBPFeatureDimensions = pQBP_FeatureDimensions;
    return pQBP_FeatureSequential;
}
