/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Song - O objetivo principal da classe Song é armazenar features */
/*contidas em uma musica, incluindo a lista de notas musicais            */
/*************************************************************************/
#ifndef QBP_FEATURETYPE_H_
#define QBP_FEATURETYPE_H_

#include "QBP_GlobalDef.h"

class CQBPFeatureType
{
public:
     CQBPFeatureType();

     CQBPFeatureType(string pQBPFeatureName,
                     string pQBPFeatureDescription,
                     int    pQBPFeatureDimensions,
                     bool   pQBPFeatureSequential,
                     bool   pQBPFeatureCustom);

    ~CQBPFeatureType();

    bool GetFeatureTypeData(string &pQBPFeatureName,
                            string &pQBPFeatureDescription,
                            int    &pQBPFeatureDimensions,
                            bool   &pQBPFeatureSequential,
                            bool   &pQBPFeatureCustom);

    string GetFeatureName();
    bool   GetDimensions (int &pQBPFeatureDimensions);

private:

    string pQBP_FeatureName;
    string pQBP_FeatureDescription;
    int    pQBP_FeatureDimensions;
    bool   pQBP_FeatureSequential;
    bool   pQBP_FeatureCustom;
};

#endif
