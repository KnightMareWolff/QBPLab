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
#include "QBP_Matrix.h"

//CQBPMatrixValue** CQBPMatrix::pQBPMatrix = nullptr;
vector<vector<CQBPMatrixValue> > CQBPMatrix::pQBPMatrix;
int CQBPMatrix::iQBPSizeX = 0;
int CQBPMatrix::iQBPSizeY = 0;

CQBPMatrix::CQBPMatrix()
{
}

CQBPMatrix::CQBPMatrix(const  CQBPMatrix  &obj)
{
    int Idx;
    int Idxi, Idxj;

    //if the container was not properly allocated...
    if(pQBPMatrix.size()>0)Clear();

    if(obj.iQBPSizeX >0 && obj.iQBPSizeY > 0)
    {
       iQBPSizeY = obj.iQBPSizeY;
       iQBPSizeX = obj.iQBPSizeX;

       pQBPMatrix = vector< vector<CQBPMatrixValue> >(iQBPSizeY, vector<CQBPMatrixValue>(iQBPSizeX,CQBPMatrixValue()));

       for (Idxj = 0; Idxj < iQBPSizeY; Idxj++)
       {
           for (Idxi = 0; Idxi < iQBPSizeX; Idxi++)
           {
               pQBPMatrix[Idxj][Idxi].iQBPRefX     =obj.pQBPMatrix[Idxj][Idxi].iQBPRefX;
               pQBPMatrix[Idxj][Idxi].iQBPRefY     =obj.pQBPMatrix[Idxj][Idxi].iQBPRefY;
               pQBPMatrix[Idxj][Idxi].iQBPValue    =obj.pQBPMatrix[Idxj][Idxi].iQBPValue;
               pQBPMatrix[Idxj][Idxi].iQBPDirection=obj.pQBPMatrix[Idxj][Idxi].iQBPDirection;
               pQBPMatrix[Idxj][Idxi].bQBPMatch    =obj.pQBPMatrix[Idxj][Idxi].bQBPMatch;

               //debug info
               pQBPMatrix[Idxj][Idxi].iQBPTopo      =obj.pQBPMatrix[Idxj][Idxi].iQBPTopo;
               pQBPMatrix[Idxj][Idxi].iQBPDiagonal  =obj.pQBPMatrix[Idxj][Idxi].iQBPDiagonal;
               pQBPMatrix[Idxj][Idxi].iQBPLado      =obj.pQBPMatrix[Idxj][Idxi].iQBPLado;
               pQBPMatrix[Idxj][Idxi].iQBPMatch     =obj.pQBPMatrix[Idxj][Idxi].iQBPMatch;
               pQBPMatrix[Idxj][Idxi].iQBPMissMatch =obj.pQBPMatrix[Idxj][Idxi].iQBPMissMatch;
               pQBPMatrix[Idxj][Idxi].iQBPGap       =obj.pQBPMatrix[Idxj][Idxi].iQBPGap;
           }
       }
    }
}

CQBPMatrix & CQBPMatrix::operator = (const CQBPMatrix& other)
{
    int Idx;
    int Idxi, Idxj;

    //if the container was not properly allocated...
    if(pQBPMatrix.size()>0)Clear();

    if(other.iQBPSizeX >0 && other.iQBPSizeY > 0)
    {
       iQBPSizeY = other.iQBPSizeY;
       iQBPSizeX = other.iQBPSizeX;

       pQBPMatrix = vector< vector<CQBPMatrixValue> >(iQBPSizeY, vector<CQBPMatrixValue>(iQBPSizeX,CQBPMatrixValue()));

       for (Idxj = 0; Idxj < iQBPSizeY; Idxj++)
       {
           for (Idxi = 0; Idxi < iQBPSizeX; Idxi++)
           {
               pQBPMatrix[Idxj][Idxi].iQBPRefX     =other.pQBPMatrix[Idxj][Idxi].iQBPRefX;
               pQBPMatrix[Idxj][Idxi].iQBPRefY     =other.pQBPMatrix[Idxj][Idxi].iQBPRefY;
               pQBPMatrix[Idxj][Idxi].iQBPValue    =other.pQBPMatrix[Idxj][Idxi].iQBPValue;
               pQBPMatrix[Idxj][Idxi].iQBPDirection=other.pQBPMatrix[Idxj][Idxi].iQBPDirection;
               pQBPMatrix[Idxj][Idxi].bQBPMatch    =other.pQBPMatrix[Idxj][Idxi].bQBPMatch;

               //debug info
               pQBPMatrix[Idxj][Idxi].iQBPTopo      =other.pQBPMatrix[Idxj][Idxi].iQBPTopo;
               pQBPMatrix[Idxj][Idxi].iQBPDiagonal  =other.pQBPMatrix[Idxj][Idxi].iQBPDiagonal;
               pQBPMatrix[Idxj][Idxi].iQBPLado      =other.pQBPMatrix[Idxj][Idxi].iQBPLado;
               pQBPMatrix[Idxj][Idxi].iQBPMatch     =other.pQBPMatrix[Idxj][Idxi].iQBPMatch;
               pQBPMatrix[Idxj][Idxi].iQBPMissMatch =other.pQBPMatrix[Idxj][Idxi].iQBPMissMatch;
               pQBPMatrix[Idxj][Idxi].iQBPGap       =other.pQBPMatrix[Idxj][Idxi].iQBPGap;
           }
       }
    }

    return *this;
}

CQBPMatrix::CQBPMatrix(int pQBPSizeX, int pQBPSizeY)
{
    int Idx;

    //if the container was not properly allocated...
    if(pQBPMatrix.size()>0)Clear();

    iQBPSizeX = pQBPSizeX +1;
    iQBPSizeY = pQBPSizeY +1;

    pQBPMatrix = vector< vector<CQBPMatrixValue> >(iQBPSizeY, vector<CQBPMatrixValue>(iQBPSizeX,CQBPMatrixValue()));

}

bool CQBPMatrix::Dimensiona(int pQBPSizeX, int pQBPSizeY)
{
    int Idx;

    Clear();

    iQBPSizeX = pQBPSizeX + 1;
    iQBPSizeY = pQBPSizeY + 1;

    pQBPMatrix = vector< vector<CQBPMatrixValue> >(iQBPSizeY, vector<CQBPMatrixValue>(iQBPSizeX,CQBPMatrixValue()));

    return true;
}

bool CQBPMatrix::Reset()
{
    int Idxi, Idxj; //Indices i,j

    for (Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        for (Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            pQBPMatrix[Idxj][Idxi].iQBPValue     = 0;
            pQBPMatrix[Idxj][Idxi].iQBPDirection = QBP_VAL_DIR_NONE;
            pQBPMatrix[Idxj][Idxi].bQBPMatch     = false;

            //debug info
            pQBPMatrix[Idxj][Idxi].iQBPTopo      =0;
            pQBPMatrix[Idxj][Idxi].iQBPDiagonal  =0;
            pQBPMatrix[Idxj][Idxi].iQBPLado      =0;
            pQBPMatrix[Idxj][Idxi].iQBPMatch     =0;
            pQBPMatrix[Idxj][Idxi].iQBPMissMatch =0;
            pQBPMatrix[Idxj][Idxi].iQBPGap       =0;
        }
    }
    return true;
}

bool CQBPMatrix::Extract(CQBPMatrixValue **pQBPSearchMatrix)
{
    int Idxi, Idxj; //Indices i,j

    //if the container was not properly allocated...
    if(!pQBPSearchMatrix)return false;

    for (Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        for (Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            pQBPSearchMatrix[Idxj][Idxi].iQBPRefX     = pQBPMatrix[Idxj][Idxi].iQBPRefX;
            pQBPSearchMatrix[Idxj][Idxi].iQBPRefY     = pQBPMatrix[Idxj][Idxi].iQBPRefY;
            pQBPSearchMatrix[Idxj][Idxi].iQBPValue    = pQBPMatrix[Idxj][Idxi].iQBPValue;
            pQBPSearchMatrix[Idxj][Idxi].iQBPDirection= pQBPMatrix[Idxj][Idxi].iQBPDirection;
            pQBPSearchMatrix[Idxj][Idxi].bQBPMatch    = pQBPMatrix[Idxj][Idxi].bQBPMatch;

            //debug info
            pQBPSearchMatrix[Idxj][Idxi].iQBPTopo     = pQBPMatrix[Idxj][Idxi].iQBPTopo;
            pQBPSearchMatrix[Idxj][Idxi].iQBPDiagonal = pQBPMatrix[Idxj][Idxi].iQBPDiagonal;
            pQBPSearchMatrix[Idxj][Idxi].iQBPLado     = pQBPMatrix[Idxj][Idxi].iQBPLado;
            pQBPSearchMatrix[Idxj][Idxi].iQBPMatch    = pQBPMatrix[Idxj][Idxi].iQBPMatch;
            pQBPSearchMatrix[Idxj][Idxi].iQBPMissMatch= pQBPMatrix[Idxj][Idxi].iQBPMissMatch;
            pQBPSearchMatrix[Idxj][Idxi].iQBPGap      = pQBPMatrix[Idxj][Idxi].iQBPGap;
        }
    }
    return true;
}

bool CQBPMatrix::Clear()
{
    int Idx;

    //Limpa Colunas alocadas
    for (Idx = 0; Idx < iQBPSizeY; Idx++)
    {
        pQBPMatrix[Idx].clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMatrix[Idx].shrink_to_fit();
    }

    pQBPMatrix.clear();
    pQBPMatrix.shrink_to_fit();

    //Zera os tamanhos
    iQBPSizeX = 0;
    iQBPSizeY = 0;

    return true;
}
CQBPMatrix::~CQBPMatrix()
{
    //Limpa a Matrix
    Clear();
}

int CQBPMatrix::GetSizeX()
{
    return iQBPSizeX;
}

int CQBPMatrix::GetSizeY()
{
    return iQBPSizeY;
}

int CQBPMatrix::GetVal(int x, int y,int &pDir,bool &pMatch)
{
    if (x > iQBPSizeX || y > iQBPSizeY || x < 0 || y < 0)return 0;//caso esteja fora dos indices

    //repassa a direção e acerto
    pDir    = pQBPMatrix[y][x].iQBPDirection;
    pMatch  = pQBPMatrix[y][x].bQBPMatch;
    //retorna o valor
    return pQBPMatrix[y][x].iQBPValue;
}

bool CQBPMatrix::SetVal(int x, int y, int pVal, int pDir, bool pMatch )
{
    if (x > iQBPSizeX || y > iQBPSizeY || x < 0 || y < 0 || pDir == 0)return false;//caso esteja fora dos indices

    pQBPMatrix[y][x].iQBPRefX      = x;
    pQBPMatrix[y][x].iQBPRefY      = y;
    pQBPMatrix[y][x].iQBPValue     = pVal;
    pQBPMatrix[y][x].iQBPDirection = pDir;
    pQBPMatrix[y][x].bQBPMatch     = pMatch;

    return true;
}

bool CQBPMatrix::Debbug(int x, int y,int  piQBPTopo ,int piQBPDiagonal ,int piQBPLado,int piQBPMatch,int piQBPMissMatch,int piQBPGap )
{
    if (x > iQBPSizeX || y > iQBPSizeY || x < 0 || y < 0)return false;//caso esteja fora dos indices

    pQBPMatrix[y][x].RegisterDebugInfo(piQBPTopo,piQBPDiagonal,piQBPLado,piQBPMatch,piQBPMissMatch,piQBPGap);

    return true;
}

bool CQBPMatrix::GetDebbug(int x, int y, int  &piQBPTopo ,int &piQBPDiagonal ,int &piQBPLado,int &piQBPMatch,int &piQBPMissMatch,int &piQBPGap )
{
    if (x > iQBPSizeX || y > iQBPSizeY || x < 0 || y < 0)return false;//caso esteja fora dos indices

    //repassa a direção e acerto
    piQBPTopo       = pQBPMatrix[y][x].iQBPTopo;
    piQBPDiagonal   = pQBPMatrix[y][x].iQBPDiagonal;
    piQBPLado       = pQBPMatrix[y][x].iQBPLado;
    piQBPMatch      = pQBPMatrix[y][x].iQBPMatch;
    piQBPMissMatch  = pQBPMatrix[y][x].iQBPMissMatch;
    piQBPGap        = pQBPMatrix[y][x].iQBPGap;

    //retorna o valor
    return true;
}

//Pega o valor máximo na substitution Matrix e retorna além das coordenada se existe mais de um path
int CQBPMatrix::GetMax(int &x, int &y , int &score)
{
    int iMaxValue, iMaxValueX, iMaxValueY , iQtdMax;

    iMaxValue = -999;
    iMaxValueX= 0;
    iMaxValueY= 0;
    iQtdMax   = 0;

    //Obtém o valor máximo de score
    for (int Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        for (int Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            //Estamos na Borda não mapeie valores(Causa a Mussix retornar 11 tracebacks (scores zerados de borda ja que podem ocorrer valores negativos com ela)
            if(Idxj==0 || Idxi==0)continue;

            if (pQBPMatrix[Idxj][Idxi].iQBPValue >= iMaxValue)
            {
                iMaxValue = pQBPMatrix[Idxj][Idxi].iQBPValue;
                iMaxValueX = Idxi;
                iMaxValueY = Idxj;
            }
        }
    }

    //Conta quantos resultados máximos temos na matriz
    for (int Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        for (int Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            //Estamos na Borda não mapeie valores(Causa a Mussix retornar 11 tracebacks (scores zerados de borda ja que podem ocorrer valores negativos com ela)
            if(Idxj==0 || Idxi==0)continue;

            if (pQBPMatrix[Idxj][Idxi].iQBPValue == iMaxValue)
            {
                iQtdMax++;
            }
        }
    }

    score = iMaxValue;
    x = iMaxValueX;
    y = iMaxValueY;

    return iQtdMax;
}

//Preenche um vortor de coordenadas baseado em um score
vector<path> CQBPMatrix::GetMax(int score)
{
    int iMaxValue, iMaxValueX, iMaxValueY , iQtdMax;
    vector<path> paths;
    path tpath;

    iMaxValueX= 0;
    iMaxValueY= 0;
    iQtdMax   = 0;

    //Obtém o valor máximo de score
    for (int Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        for (int Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            if (pQBPMatrix[Idxj][Idxi].iQBPValue == score)
            {
                tpath.Px = Idxi;
                tpath.Py = Idxj;
                paths.push_back(tpath);
            }
        }
    }


    return paths;
}

void CQBPMatrix::Print()
{
    QColor tColorFont;
    QColor tColorBackground;

    for (int Idxj = 0; Idxj < iQBPSizeY; Idxj++)
    {
        //imprime tabulação coluna
        tColorBackground = QColor(255,255,255);
        tColorFont = QColor(0,0,0);
        CQBPLogQueue::ColorPush(QString("\t"),tColorFont,tColorBackground);

        for (int Idxi = 0; Idxi < iQBPSizeX; Idxi++)
        {
            //imprime substitution matrix
            switch (pQBPMatrix[Idxj][Idxi].iQBPDirection)
            {
               case QBP_VAL_DIR_DIAG:
               {
                   //DIAGONAL TEM FONTE VERMELHA
                   tColorBackground = QColor(150,0,0);
                   tColorFont = QColor(255,255,255);
               }break;
               case QBP_VAL_DIR_LEFT:
               {
                   //ESQUERDA TEM FONTE VERDE
                   tColorBackground = QColor(0,0,150);
                   tColorFont = QColor(255,255,255);
               }break;
               case QBP_VAL_DIR_TOP:
               {
                   //TOPO TEM FONTE AZUL
                   tColorBackground = QColor(0,150,0);
                   tColorFont = QColor(255,255,255);
               }break;
               case QBP_VAL_DIR_NONE:
               {
                //Caminho bloqueado com fonte banca
                tColorBackground = QColor(150,150,150);
                tColorFont = QColor(255,255,255);
               }break;
               case QBP_VAL_DIR_INIT:
               {
                 //Inicialização com fonte Igual
                tColorBackground = QColor(150,150,150);
                tColorFont = QColor(150,150,150);
               }break;
            }
            CQBPLogQueue::ColorPush(QString("%1").arg(pQBPMatrix[Idxj][Idxi].iQBPValue,3, 10, QChar('0')),tColorFont,tColorBackground);
        }
        CQBPLogQueue::ColorPush(QString("\n"),tColorFont,tColorBackground);
    }
    //garante tres linhas apos impressao
    CQBPLogQueue::ColorPush(QString("\n\n\n"),tColorFont,tColorBackground);
}
