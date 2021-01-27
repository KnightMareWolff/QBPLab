/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Máscara - A idéia de se criar uma mascara para o desenvolvimento*/
/*do algoritmo veio dos algoritmos de processamento de imagens, no qual  */
/*constantemente aplicam filtros em matriz e utilizam os pixels vizinhos */
/*para calculos(exatamente como sao calculados os scores deste algoritmo)*/
/*************************************************************************/
#ifndef QBP_MUSSUMMASK_H_
#define QBP_MUSSUMMASK_H_

#include "QBP_Mask.h"

class CQBPMussumMask :	public CQBPMask
{
public:
     CQBPMussumMask();
    ~CQBPMussumMask();

    bool CalculaScores      (                                        );
    int  CalculaSimilaridade(int pIndiceX, int pIndiceY, bool &pMatch);
    bool PreparaMatrix      (                                        );
};

#endif

