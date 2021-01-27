/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Máscara - A idéia de se criar uma mascara para o desenvolvimento*/
/*do algoritmo veio dos algoritmos de processamento de imagens, no qual  */
/*constantemente aplicam filtros em matriz e utilizam os pixels vizinhos */
/*para calculos(exatamente como sao calculados os scores deste algoritmo)*/
/*************************************************************************/
#ifndef QBP_MUSSIXMASK_H
#define QBP_MUSSIXMASK_H

#include "QBP_Mask.h"

class CQBPMussixMask :	public CQBPMask
{
public:
     CQBPMussixMask();
    ~CQBPMussixMask();

    bool  CalculaScores       (                                        );
    int   CalculaSimilaridade (int pIndiceX, int pIndiceY, bool &pMatch);
    bool  PreparaMatrix       (                                        );

    //Calcula distancia para definir a similaridade
    int  CalculaDistancia   (stQBPMusicBuffer  pSinalA , stQBPMusicBuffer pSinalB);

protected:
    int iQBPOctave;
};

#endif
