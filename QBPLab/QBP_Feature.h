/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Song - O objetivo principal da classe Song é armazenar features */
/*contidas em uma musica, incluindo a lista de notas musicais            */
/*************************************************************************/
#ifndef QBP_FEATURE_H_
#define QBP_FEATURE_H_

#include "QBP_GlobalDef.h"

class CQBPFeature
{
public:
     CQBPFeature();
     CQBPFeature(const CQBPFeature &obj);
     CQBPFeature(double pQBPFeatureTypeId,string pQBPFeatureName,double pQBPFeatureValue);
    ~CQBPFeature();

    bool    GetFeatureData (double &pQBPFeatureTypeId, string &pQBPFeatureName, double &pQBPFeatureValue);
    double  GetFeatureValue(                                                                            );
    double  GetFeatureId   (                                                                            );
    string  GetFeatureName (                                                                            );
private:
    double pQBP_FeatureTypeId;
    string pQBP_FeatureName;
    double pQBP_FeatureValue;
};

#endif
