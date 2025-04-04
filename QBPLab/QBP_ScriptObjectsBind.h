#ifndef QBP_SCRIPTOBJECTSBIND_H
#define QBP_SCRIPTOBJECTSBIND_H

#include "QBP_GlobalDef.h"

//Algorithm Type
#define QBP_ALG_SW     0//Original Smith Waterman Matrix
#define QBP_ALG_MUSSUM 1//Music Substitution Matrix
#define QBP_ALG_MUSSIX 2//New Matrix (Musical Space Matrix)
#define QBP_ALG_MUSSAT 3//Musical Attitude Space.

//Dataset Type
#define QBP_LIST_FULLSET 1//Direciona a carga para o dataset principal
#define QBP_LIST_TESTSET 2//Direciona a carga para o Test Set(Lista de Teste)
#define QBP_LIST_VALISET 3//Direciona a Carga para o Vali Set(Lista de Validação)
#define QBP_LIST_RANDSET 4//Direciona Carga para set Randomico de musicas

//Creation Formulas
#define QBP_FORM_LESS_GENRE 1//Extrai 10% do genero com menor numero de musicas para todos os generos
#define QBP_FORM_PERC_10    2//Extrai 10% do genero para o Set especificado do genero atual
#define QBP_FORM_PERC_15    3//Extrai 15% do genero para o Set especificado do genero atual
#define QBP_FORM_LESS_1015F 4//Extrai 10% do genero para o Set de Teste e 15% para o set de validação

//Post Processing Schemas
#define QBP_PPROC_F1 0//Pega o Primeiro path encontrado
#define QBP_PPROC_B1 1//Pega o Melhor Path Encontrado
#define QBP_PPROC_G1 2//Pega o Maior Path encontrado
#define QBP_PPROC_A1 3//Soma o Score de Todos os Paths


class QBPSearchEngine
{
public:

    QBPSearchEngine();
   ~QBPSearchEngine();

    bool Search(char *SearchName     ,
                char *SongAName      ,
                int   DatasetType    ,
                int   ComparatorType ,
                bool  UseAttitude    );

    bool Search(char *SearchName     ,
                int   SongAId        ,
                int   DatasetType    ,
                int   ComparatorType ,
                bool  UseAttitude    );

    void   SetPrecisionBalance(int Precision);
    void   SetResultSizeBalance(int ResultSize);
    void   SetBufferSize(int BufferSize);
    void   SetPProcType (int PProcType);
    void   CreateList   (int DatasetType , int CreationFormula);
    int    GetListSize  (int DatasetType);

    char*  GetListSongName (int DatasetType, int pQBPMusicId);
    int    GetListSongNotes(int DatasetType, int pQBPMusicId);
    int    GetListSongScore(int DatasetType, int pQBPMusicId);

    void   PushLog      (char* pQBPLogString);

};

#endif // QBP_SCRIPTOBJECTSBIND_H
