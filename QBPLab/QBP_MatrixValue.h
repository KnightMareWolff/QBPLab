/*****************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR              */
/*Author: William Wolff                                                      */
/*Classe Matrix - Todo o processamento do algoritmo baseia-se na varredura   */
/*retroativa da matriz de substituição, após o calculo dos scores realizados */
/*Pela máscara de processamento.                                             */
/*Todo: Aplicar Design de Singleton para possibilitar programação dinâmica em*/
/*cima da mascara de processamento, possibilitando a criação de grafos de    */
/*caminhamento para o processamento retroativo...(É uma idéia ainda...)      */
/*****************************************************************************/
#ifndef QBP_MATRIXVALUE_H_
#define QBP_MATRIXVALUE_H_

#include "QBP_GlobalDef.h"

class CQBPMatrixValue
{
public:
     CQBPMatrixValue(                           );
     CQBPMatrixValue( const CQBPMatrixValue &obj);
     CQBPMatrixValue(int pQBPValue,int pQBPDirection,bool pQBPMatch);
     CQBPMatrixValue(int pQBPValue, int pQBPDirection, bool pQBPMatch, int pRefX, int pRefY);
    ~CQBPMatrixValue();

     CQBPMatrixValue & operator = (const CQBPMatrixValue& other);

     void RegisterDebugInfo(int    piQBPTopo     ,
                            int    piQBPDiagonal ,
                            int    piQBPLado     ,
                            int    piQBPMatch    ,
                            int    piQBPMissMatch,
                            int    piQBPGap      );

    //Valores utilizados para o Backtracing
    int    iQBPRefX;
    int    iQBPRefY;
    int    iQBPValue;
    int    iQBPDirection;
    bool   bQBPMatch;
    //string cChPair;

    //Valores utilizados para registro do funcionamento passo a passo
    int    iQBPTopo;
    int    iQBPDiagonal;
    int    iQBPLado;
    int    iQBPMatch;
    int    iQBPMissMatch;
    int    iQBPGap;
};

#endif

