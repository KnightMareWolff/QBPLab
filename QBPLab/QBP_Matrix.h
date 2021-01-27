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
#ifndef QBP_MATRIX_H_
#define QBP_MATRIX_H_

#include "QBP_GlobalDef.h"
#include "QBP_MatrixValue.h"
#include "QBP_LogQueue.h"

struct path
{
    int Px;
    int Py;
};

class CQBPMatrix
{
public:
     CQBPMatrix(                            );
     CQBPMatrix( const  CQBPMatrix  &obj    );
     CQBPMatrix(int pQBPSizeX, int pQBPSizeY);
    ~CQBPMatrix(                            );

     CQBPMatrix & operator = (const CQBPMatrix& other);

    static int  GetSizeX  (                             );
    static int  GetSizeY  (                             );
    static bool Reset     (                             );

    //Extract the entire SWMatrix
    static bool Extract   (CQBPMatrixValue **pQBPSearchMatrix);

    static bool Clear     (                             );
    static int  GetMax    (int   &x, int &y , int &score);

    static vector<path> GetMax(int score);

    static bool Dimensiona(int  pQBPSizeX, int pQBPSizeY);
    static int  GetVal    (int  x        , int  y       , int &pDir, bool &pMatch);
    static bool SetVal    (int  x        , int  y       , int  pVal, int   pDir  , bool pMatch);

    static bool Debbug    (int  x        , int  y       , int  piQBPTopo  ,int  piQBPDiagonal ,int  piQBPLado,int  piQBPMatch,int  piQBPMissMatch,int  piQBPGap);
    static bool GetDebbug (int  x        , int  y       , int  &piQBPTopo ,int &piQBPDiagonal ,int &piQBPLado,int &piQBPMatch,int &piQBPMissMatch,int &piQBPGap);

    static void Print     (                             );

private:
    //static CQBPMatrixValue **pQBPMatrix;
    static vector<vector<CQBPMatrixValue> > pQBPMatrix;
    static int               iQBPSizeX ,
                             iQBPSizeY ;
};

#endif

