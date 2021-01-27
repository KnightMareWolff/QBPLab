/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Song - O objetivo principal da classe Song é armazenar features */
/*contidas em uma musica, incluindo a lista de notas musicais            */
/*************************************************************************/
#ifndef QBP_JSYMBOLICFILE_H_
#define QBP_JSYMBOLICFILE_H_

#include "QBP_GlobalDef.h"
#include "QBP_LogQueue.h"
#include "QBP_Genre.h"
#include "QBP_Feature.h"
#include "QBP_FeatureType.h"

class CQBPJSymboFeatureDefinition
{
public:
    CQBPJSymboFeatureDefinition(QString pFeatureName,
                                QString pDescription,
                                QString pDimensions,
                                QString pSequencial)
    {
        sFeatureName=pFeatureName;
        sDescription=pDescription;
        sDimensions =pDimensions;
        sSequencial =pSequencial;
    }

    QString sFeatureName;
    QString sDescription;
    QString sDimensions;
    QString sSequencial;
};

class CQBPJSymboFeature
{
public:
    CQBPJSymboFeature(int     pFeatureType,
                      bool    pMultidimensional,
                      QString pFeatureName,
                      QString pFeatureValue)
    {
        iFeatureType      = pFeatureType;
        bMultidimensional = pMultidimensional;
        sFeatureName      =pFeatureName;
        sFeatureValue     =pFeatureValue;
    }

    int     iFeatureType;
    bool    bMultidimensional;
    QString sFeatureName;
    QString sFeatureValue;
};

class CQBPJSymboDataset
{
public:
    CQBPJSymboDataset(QString pDatasetID,
                      vector<CQBPJSymboFeature> pFeatures)
    {
        sDatasetID      = pDatasetID;

        for(int i=0;i<pFeatures.size();i++)
        {
            vFeatures.push_back(CQBPJSymboFeature(pFeatures[i].iFeatureType,
                                                  pFeatures[i].bMultidimensional,
                                                  pFeatures[i].sFeatureName,
                                                  pFeatures[i].sFeatureValue));
        }

    }

    QString sDatasetID;
    vector<CQBPJSymboFeature> vFeatures;
};

class CQBPJSymbolicFile
{
public:
     CQBPJSymbolicFile();
    ~CQBPJSymbolicFile();

    bool ParseFeatures          (vector<CQBPGenre>       &pQBP_GenreList,
                                 vector<CQBPFeatureType> &pQBPFeatureTypeList);

    bool ParseFeatures          (vector<CQBPSong>        &pQBP_SongList,
                                 vector<CQBPFeatureType> &pQBPFeatureTypeList);

    bool ParseFeatureDefinitions(vector<CQBPFeatureType> *pQBPFeatureTypeList);

    bool GetParseIds            (string pQBPDatasetName,vector<CQBPGenre> pQBP_GenreList,int &pGenreId,int &pSongId);
    bool GetParseIds            (string pQBPDatasetName,vector<CQBPSong > pQBP_SongList ,int &pGenreId, int &pSongId);


    /*Funções Para retirada de rapidXML para QtXML*/

    bool    LoadJSymbolicDatabase   (                                      );
    bool    LoadJSymbolicDefinitions(                                      );
    bool    GetFeatureTypeId        (QString pQBPFeatureName, int &pFTypeId);

private:
    QXmlStreamReader *pQBP_FeaturesDoc;
    QXmlStreamReader *pQBP_FeaturesDef;

    vector<CQBPJSymboFeatureDefinition> vFeatureDefifitions;
    vector<CQBPJSymboFeature>           vFeatureDatasets;
};

#endif
