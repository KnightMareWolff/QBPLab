/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Máscara - A idéia de se criar uma mascara para o desenvolvimento*/
/*do algoritmo veio dos algoritmos de processamento de imagens, no qual  */
/*constantemente aplicam filtros em matriz e utilizam os pixels vizinhos */
/*para calculos(exatamente como sao calculados os scores deste algoritmo)*/
/*************************************************************************/
#ifndef QBP_MASK_H
#define QBP_MASK_H

#include "QBP_GlobalDef.h"
#include "QBP_Matrix.h"
#include "QBP_LogQueue.h"


class CQBPMask
{
public:
     CQBPMask();
     CQBPMask( const CQBPMask &obj);

     CQBPMask & operator = (const CQBPMask& other);

     /**********************************************************************/
     /*Huhuuuu! Finalmente descobri a causa dos vetores perdendo valores!!!*/
     /*Atenção! Impreterivelmente o construto tem que ser virtual pois     */
     /*Todos os algoritmos são derivados desta classe!!! caso contrario    */
     /*Durante a utilização do software (Principalmente na coleta e exibi  */
     /*Ção de resultados os dados de path acabam sendo perdidos por destru */
     /*ição indevida da classe base ao invés das filhas.                   */
     /**********************************************************************/
     virtual ~CQBPMask();

    //Por enquanto os buffers estao na mascara...
    string SongNameA;
    string SongNameB;
    vector<stQBPMusicBuffer>  vQBP_IBufferA;
    vector<stQBPMusicBuffer>  vQBP_IBufferB;
    vector<stQBPStringBuffer> BufferA;
    vector<stQBPStringBuffer> BufferB;

    vector<CQBPMatrixValue>         vTraceBack;
    vector<vector<CQBPMatrixValue>> vTraceBackList;

    //Métodos para a Convolução
    virtual bool CalculaScores       (                                                );
    virtual bool PreparaMatrix       (                                                );

    //Calculos de Similaridade
    virtual int   CalculaSimilaridade (int         pIndiceX, int pIndiceY,bool &pMatch );
    virtual int   CalculaScoreMaximo  (int        &pDirection                          );

    //Métodos para a montagem dos paths
    virtual bool TraceBack           (                                                );
    virtual bool TraceBackF1         (                                                );
    virtual bool TraceBackB1         (                                                );
    virtual bool TraceBackG1         (                                                );
    virtual bool TraceBackA1         (                                                );

    //Métodos para o Calculo de Score de similaridade
    virtual int  TraceBackScore      (                                                );

    //Recupera o path de busca com os buffers.
    virtual void GetPathSize(int &pQBPPathSize);
    virtual void GetPath(CQBPMatrixValue *pQBPPath);
    virtual void GetPathValue(int pValueID,CQBPMatrixValue *pQBPPath);

    virtual void GetBuffers(vector<stQBPMusicBuffer> &pBufferA, vector<stQBPMusicBuffer> &pBufferB);
    virtual void GetBuffers(vector<stQBPStringBuffer>&pBufferA, vector<stQBPStringBuffer>&pBufferB);

    virtual int  GetBufferType(){return iQBPBufferType;}
    virtual void SetBufferType(int pQBPBufferType){iQBPBufferType = pQBPBufferType;}

    virtual int  GetPProcType(){return iQBPPostProcType;}
    virtual void SetPProcType(int pQBPPProcType){iQBPPostProcType = pQBPPProcType;}

    virtual void CleanUp();

public:
    //Processamento com numaros inteiros
    int iQBPMaskPathSize;
    int iQBPMaskQtdPaths;
    int iQBPTopo;
    int iQBPDiagonal;
    int iQBPLado;
    int iQBPScore;
    int iQBPDirection;
    int iQBPMatch;
    int iQBPMissMatch;
    int iQBPGap;
    int iQBPBufferType;
    int iQBPPostProcType;

};

#endif
