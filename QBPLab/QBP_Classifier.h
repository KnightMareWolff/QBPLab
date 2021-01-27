/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Classifier - O objetivo principal da classe é realizar   o      */
/*Carregamento,treinamento e Classificação de gêneros musicais através   */
/*da utilização de uma SVM.                                              */
/*Para tal, a engine de busca ira receber as features do snippet do user */
/*e retornar qual é o genero que a mesma mais se encaixa, sendo possivel */
/*a partir disto simplificar o numero de buffers a ser utilizado para o  */
/*calculo de score de similaridade emitido pelo Comparator.              */
/*************************************************************************/
#ifndef QBP_CLASSIFIER_H_
#define QBP_CLASSIFIER_H_

#include "QBP_GlobalDef.h"
#include "QBP_LogQueue.h"

struct ClassifierFeature
{
    int    pFeatureId;
    double pFeatureValue;
};

struct ClassifierList
{
    int    pListId;
    vector<ClassifierFeature> pFeatureList;
};

struct ClassifierProblem
{
    int    pProblemId;
    vector<ClassifierList> pProblemList;
};

class CQBPClassifier
{
public:
             CQBPClassifier();
    virtual ~CQBPClassifier();

    virtual bool LoadQBPProblem    (string          pQBPath             ,bool pQBPClear);
    virtual bool LoadQBPBuffer     (ClassifierList *pQBPPredictionBuffer);
    virtual bool LoadModel         (string          pQBPath             );
    virtual bool SaveModel         (string          pQBPath             );
    virtual bool Train             (string          pQBPath             );
    virtual int  Predict           (ClassifierList *pQBPPredictionBuffer);
    virtual bool Clear             (                                    );
    virtual bool ShowStatistics    (                                    );

    void   SetType   (int pQBPClassifierType){iQBPClassifierType = pQBPClassifierType;}
    int    GetType   (                       ){return iQBPClassifierType;}

protected:
    //Dados para funcionamento do classificador
    ClassifierProblem         pQBPClassifierList;//Lista de Problemas do classificador
    bool                      pQBPLoaded        ;//Problema Carregado?
    int                       iQBPNumFeatures   ;//Numero total de features carregadas
    int                       iQBPNumClasses    ;//Numero total de classes carregadas(cada classe tem n features...)
    int                       iQBPHits          ;//Numero total de acertos da ultima predicao.
    int                       iQBPMistakes      ;//Numero total de erros da ultima predição.
    int                       iQBPClassifierType;//Categoria do problema a ser resolvido(One Class SVM)
    double                    pQBPHitProbability;//Probabilidade de acerto de um problema
    double                   *pQBPSHitProbabiList;//Lista probabilidade de acerto de cada classe
    double                    pQBPSHitProbabClass;//Classe de acerto mais provavel
    double                    pQBPMeanSquaredErr;//Valor quadratico de erro
    double                    pQBPSquaredCorrelt;//Valor de Correlaçao Quadratica
    double                    pQBPAccuracy      ;//Valor de Acuracidade da predição

};

#endif
