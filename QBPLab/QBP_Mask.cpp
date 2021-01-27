/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Máscara - A idéia de se criar uma mascara para o desenvolvimento*/
/*do algoritmo veio dos algoritmos de processamento de imagens, no qual  */
/*constantemente aplicam filtros em matriz e utilizam os pixels vizinhos */
/*para calculos(exatamente como sao calculados os scores deste algoritmo)*/
/*************************************************************************/
#include "QBP_Mask.h"

CQBPMask::CQBPMask()
{
    iQBPMatch          =   2;
    iQBPMissMatch      =  -2;
    iQBPGap            =  -1;
    iQBPMaskPathSize   =  -1;
    iQBPMaskQtdPaths   =   0;
    iQBPPostProcType   =  QBP_POSTPROC_TYPE_F1;

}

CQBPMask::~CQBPMask()
{
   //CleanUp();
}

CQBPMask::CQBPMask(const CQBPMask &obj)
{
    int Idx;

    iQBPTopo     =obj.iQBPTopo;
    iQBPDiagonal =obj.iQBPDiagonal;
    iQBPLado     =obj.iQBPLado;
    iQBPScore    =obj.iQBPScore;
    iQBPDirection=obj.iQBPDirection;
    iQBPMatch    =obj.iQBPMatch;
    iQBPMissMatch=obj.iQBPMissMatch;
    iQBPGap      =obj.iQBPGap;
    iQBPMaskPathSize = obj.iQBPMaskPathSize;
    iQBPMaskQtdPaths = obj.iQBPMaskQtdPaths;

    BufferA=obj.BufferA;
    BufferB=obj.BufferB;

    vQBP_IBufferA=obj.vQBP_IBufferA;
    vQBP_IBufferB=obj.vQBP_IBufferB;

    vTraceBack.clear();
    vTraceBack.shrink_to_fit();
    vTraceBackList.clear();
    vTraceBackList.shrink_to_fit();

    for(int i=0;i<iQBPMaskPathSize;i++)
    {
        vTraceBack.push_back(CQBPMatrixValue());
    }


    //copia os valores
    for (Idx = 0; Idx < obj.iQBPMaskPathSize; Idx++)
    {

        vTraceBack[Idx].iQBPRefX      =obj.vTraceBack[Idx].iQBPRefX;
        vTraceBack[Idx].iQBPRefY      =obj.vTraceBack[Idx].iQBPRefY;
        vTraceBack[Idx].iQBPValue     =obj.vTraceBack[Idx].iQBPValue;
        vTraceBack[Idx].iQBPDirection =obj.vTraceBack[Idx].iQBPDirection;
        vTraceBack[Idx].bQBPMatch     =obj.vTraceBack[Idx].bQBPMatch;

        //debug info
        vTraceBack[Idx].iQBPTopo      =obj.vTraceBack[Idx].iQBPTopo;
        vTraceBack[Idx].iQBPDiagonal  =obj.vTraceBack[Idx].iQBPDiagonal;
        vTraceBack[Idx].iQBPLado      =obj.vTraceBack[Idx].iQBPLado;
        vTraceBack[Idx].iQBPMatch     =obj.vTraceBack[Idx].iQBPMatch;
        vTraceBack[Idx].iQBPMissMatch =obj.vTraceBack[Idx].iQBPMissMatch;
        vTraceBack[Idx].iQBPGap       =obj.vTraceBack[Idx].iQBPGap;
    }

    if(iQBPMaskQtdPaths > 0)
    {
        //Reserva o numero de listas necessário
        vTraceBackList = vector< vector<CQBPMatrixValue> >(iQBPMaskQtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

        //Monta todos os paths identificados
        for(uint i=0;i<iQBPMaskQtdPaths;i++)
        {
            //copia os valores
            for (Idx = 0; Idx < (uint)obj.vTraceBackList[i].size(); Idx++)
            {
                //vTraceBackList[i].push_back(obj.vTraceBackList[i][Idx]);

                vTraceBackList[i][Idx].iQBPRefX      = obj.vTraceBackList[i][Idx].iQBPRefX;
                vTraceBackList[i][Idx].iQBPRefY      = obj.vTraceBackList[i][Idx].iQBPRefY;
                vTraceBackList[i][Idx].iQBPValue     = obj.vTraceBackList[i][Idx].iQBPValue;
                vTraceBackList[i][Idx].iQBPDirection = obj.vTraceBackList[i][Idx].iQBPDirection;
                vTraceBackList[i][Idx].bQBPMatch     = obj.vTraceBackList[i][Idx].bQBPMatch;

                //debug info
                vTraceBackList[i][Idx].iQBPTopo      = obj.vTraceBackList[i][Idx].iQBPTopo;
                vTraceBackList[i][Idx].iQBPDiagonal  = obj.vTraceBackList[i][Idx].iQBPDiagonal;
                vTraceBackList[i][Idx].iQBPLado      = obj.vTraceBackList[i][Idx].iQBPLado;
                vTraceBackList[i][Idx].iQBPMatch     = obj.vTraceBackList[i][Idx].iQBPMatch;
                vTraceBackList[i][Idx].iQBPMissMatch = obj.vTraceBackList[i][Idx].iQBPMissMatch;
                vTraceBackList[i][Idx].iQBPGap       = obj.vTraceBackList[i][Idx].iQBPGap;
            }
        }
    }
}

CQBPMask & CQBPMask::operator = (const CQBPMask& other)
{
    int Idx;

    iQBPTopo     =other.iQBPTopo;
    iQBPDiagonal =other.iQBPDiagonal;
    iQBPLado     =other.iQBPLado;
    iQBPScore    =other.iQBPScore;
    iQBPDirection=other.iQBPDirection;
    iQBPMatch    =other.iQBPMatch;
    iQBPMissMatch=other.iQBPMissMatch;
    iQBPGap      =other.iQBPGap;
    iQBPMaskPathSize =other.iQBPMaskPathSize;
    iQBPMaskQtdPaths =other.iQBPMaskQtdPaths;

    BufferA=other.BufferA;
    BufferB=other.BufferB;

    vQBP_IBufferA=other.vQBP_IBufferA;
    vQBP_IBufferB=other.vQBP_IBufferB;

    vTraceBack.clear();
    vTraceBack.shrink_to_fit();
    vTraceBackList.clear();
    vTraceBackList.shrink_to_fit();

    for(int i=0;i<iQBPMaskPathSize;i++)
    {
        vTraceBack.push_back(CQBPMatrixValue());
    }


    //copia os valores
    for (Idx = 0; Idx < other.iQBPMaskPathSize; Idx++)
    {
        vTraceBack[Idx].iQBPRefX      =other.vTraceBack[Idx].iQBPRefX;
        vTraceBack[Idx].iQBPRefY      =other.vTraceBack[Idx].iQBPRefY;
        vTraceBack[Idx].iQBPValue     =other.vTraceBack[Idx].iQBPValue;
        vTraceBack[Idx].iQBPDirection =other.vTraceBack[Idx].iQBPDirection;
        vTraceBack[Idx].bQBPMatch     =other.vTraceBack[Idx].bQBPMatch;

        //debug info
        vTraceBack[Idx].iQBPTopo      = other.vTraceBack[Idx].iQBPTopo;
        vTraceBack[Idx].iQBPDiagonal  = other.vTraceBack[Idx].iQBPDiagonal;
        vTraceBack[Idx].iQBPLado      = other.vTraceBack[Idx].iQBPLado;
        vTraceBack[Idx].iQBPMatch     = other.vTraceBack[Idx].iQBPMatch;
        vTraceBack[Idx].iQBPMissMatch = other.vTraceBack[Idx].iQBPMissMatch;
        vTraceBack[Idx].iQBPGap       = other.vTraceBack[Idx].iQBPGap;
    }

    if(iQBPMaskQtdPaths > 0)
    {
        //Reserva o numero de listas necessário
        vTraceBackList = vector< vector<CQBPMatrixValue> >(iQBPMaskQtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

        //Monta todos os paths identificados
        for(uint i=0;i<iQBPMaskQtdPaths;i++)
        {
            //copia os valores
            for (Idx = 0; Idx < (uint)other.vTraceBackList[i].size(); Idx++)
            {
                //vTraceBackList[i].push_back(other.vTraceBackList[i][Idx]);

                vTraceBackList[i][Idx].iQBPRefX      = other.vTraceBackList[i][Idx].iQBPRefX;
                vTraceBackList[i][Idx].iQBPRefY      = other.vTraceBackList[i][Idx].iQBPRefY;
                vTraceBackList[i][Idx].iQBPValue     = other.vTraceBackList[i][Idx].iQBPValue;
                vTraceBackList[i][Idx].iQBPDirection = other.vTraceBackList[i][Idx].iQBPDirection;
                vTraceBackList[i][Idx].bQBPMatch     = other.vTraceBackList[i][Idx].bQBPMatch;

                //debug info
                vTraceBackList[i][Idx].iQBPTopo      = other.vTraceBackList[i][Idx].iQBPTopo;
                vTraceBackList[i][Idx].iQBPDiagonal  = other.vTraceBackList[i][Idx].iQBPDiagonal;
                vTraceBackList[i][Idx].iQBPLado      = other.vTraceBackList[i][Idx].iQBPLado;
                vTraceBackList[i][Idx].iQBPMatch     = other.vTraceBackList[i][Idx].iQBPMatch;
                vTraceBackList[i][Idx].iQBPMissMatch = other.vTraceBackList[i][Idx].iQBPMissMatch;
                vTraceBackList[i][Idx].iQBPGap       = other.vTraceBackList[i][Idx].iQBPGap;
            }
        }
    }

    return *this;
}

bool CQBPMask::PreparaMatrix()
{
    return CQBPMatrix::Dimensiona((int)BufferA.size(), (int)BufferB.size());
}

bool CQBPMask::CalculaScores()
{

    int MtxFrame = 0;

    for (int i = 1; i < CQBPMatrix::GetSizeX(); i++)
    {

        for (int j = 1; j < CQBPMatrix::GetSizeY(); j++)
        {
            int  iSimScore,iTempDir;
            bool bSimMatch,bTempMatch;

            iSimScore = CalculaSimilaridade(i, j, bSimMatch);

            //a direcao e match aqui e temporario e nao e considerada para fins de facilidade no metodo,
            //ja que neste momento so nos interessa o score da matriz.
            iQBPDiagonal = CQBPMatrix::GetVal(i - 1,j - 1, iTempDir, bTempMatch) + iSimScore;
            iQBPLado     = CQBPMatrix::GetVal(i - 1,j    , iTempDir, bTempMatch) + iQBPGap;
            iQBPTopo     = CQBPMatrix::GetVal(i    ,j - 1, iTempDir, bTempMatch) + iQBPGap;

            //a direcao valida agora sera a direcao apos o calculo do score
            iQBPScore = CalculaScoreMaximo(iQBPDirection);

            //Para garantir que a ultima formula seja respeitada aqui é o melhor lugar
            //Para colocá-la sem que se coloque um monte de ifs para garantir sempre valores zerados
            //quando o score é menor que zero
            //if(iQBPScore < 0)iQBPScore =0;

            //atribui o valor e direcao apos o calculo de Max.
            CQBPMatrix::SetVal(i,j, iQBPScore, iQBPDirection , bSimMatch);
            CQBPMatrix::Debbug(i,j,iQBPTopo,iQBPDiagonal,iQBPLado,iQBPMatch,iQBPMissMatch,iQBPGap);
            MtxFrame++;

        }
    }

    return true;
}

bool CQBPMask::TraceBack()
{

    //Inicializa tamanho do path deste backtracing
    iQBPMaskPathSize = 0;
    iQBPMaskQtdPaths = 0;
    iQBPMaskQtdPaths = 0;

    //Limpa TraceBack Anterior
    vTraceBack.clear();
    vTraceBack.shrink_to_fit();

    //Limpa Lista de Paths
    for (uint Idx = 0; Idx < vTraceBackList.size(); Idx++)
    {
        vTraceBackList[Idx].clear();
        vTraceBackList[Idx].shrink_to_fit();
    }

    //Para garantir Limpeza Pato Purific...
    vTraceBackList.clear();
    vTraceBackList.shrink_to_fit();

    //Processa o Calculo do Score de Similaridade de acordo com o Tipo de Pos-Processamento do algoritmo
    switch(iQBPPostProcType)
    {
    case QBP_POSTPROC_TYPE_F1:{TraceBackF1();}break;
    case QBP_POSTPROC_TYPE_B1:{TraceBackB1();}break;
    case QBP_POSTPROC_TYPE_G1:{TraceBackG1();}break;
    case QBP_POSTPROC_TYPE_A1:{TraceBackA1();}break;
    }

    return true;
}

bool CQBPMask::TraceBackF1()
{
    bool   TraceEnd = false;
    int    IdxMaxX, IdxMaxY, MaxScore , QtdPaths;
    int    iValue=0, iDirection;
    bool   bMatch;
    vector<path> tPaths;

    //Debug Info
    int  tiQBPTopo=0 ,tiQBPDiagonal=0 ,tiQBPLado=0 ,tiQBPMatch=0 ,tiQBPMissMatch=0 ,tiQBPGap=0 ;

    //Pega as coordenadas do valor maximo, score maximo e quantidade de scores presentes
    QtdPaths = CQBPMatrix::GetMax(IdxMaxX, IdxMaxY, MaxScore);
    //Pega todas as coordenadas existentes do Score Máximo(Já que esperamos pegar o melhor)
    tPaths   = CQBPMatrix::GetMax(MaxScore);

    //Reserva o numero de listas necessário
    vTraceBackList = vector< vector<CQBPMatrixValue> >(QtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

    //Monta todos os paths identificados
    for(uint i=0;i<QtdPaths;i++)
    {
       TraceEnd = false;
       IdxMaxX  = tPaths[i].Px;
       IdxMaxY  = tPaths[i].Py;
       //Realiza o caminhamento
       while (!TraceEnd)
       {
           //obtem valor e direção nos indices X,Y
           iValue = CQBPMatrix::GetVal(IdxMaxX, IdxMaxY, iDirection , bMatch);

           if (iValue == 0)
           {
               TraceEnd = true;
               continue;
           }

           //obtem informação de depuração
           CQBPMatrix::GetDebbug(IdxMaxX,IdxMaxY,tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

           CQBPMatrixValue tValue;

           tValue.bQBPMatch     = bMatch;
           tValue.iQBPDirection = iDirection;
           tValue.iQBPRefX      = IdxMaxX;
           tValue.iQBPRefY      = IdxMaxY;
           tValue.iQBPValue     = iValue;

           //Debbug Info
           tValue.iQBPTopo      =tiQBPTopo;
           tValue.iQBPDiagonal  =tiQBPDiagonal;
           tValue.iQBPLado      =tiQBPLado;
           tValue.iQBPMatch     =tiQBPMatch;
           tValue.iQBPMissMatch =tiQBPMissMatch;
           tValue.iQBPGap       =tiQBPGap;

           vTraceBackList[i].push_back(tValue);

           //decrementa indices de acordo com a direção de origem do valor
           switch (iDirection)
           {
              case QBP_VAL_DIR_DIAG:
              {
                  IdxMaxX--; IdxMaxY--;
              }break;
              case QBP_VAL_DIR_LEFT:
              {
                  IdxMaxX--;
              }break;
              case QBP_VAL_DIR_TOP:
              {
                  IdxMaxY--;
              }break;
           }
       }
    }

    //Agora que já temos o maior path desejado, copiamos ele para o principal
    vTraceBack       = vTraceBackList[0];
    iQBPMaskPathSize = (int)vTraceBack.size();
    iQBPMaskQtdPaths = (uint)vTraceBackList.size();

    return true;
}

bool CQBPMask::TraceBackB1()
{
    bool   TraceEnd = false;
    int    IdxMaxX, IdxMaxY, MaxScore , QtdPaths;
    int    iValue=0, iDirection;
    bool   bMatch;
    vector<path> tPaths;

    //Debug Info
    int  tiQBPTopo=0 ,tiQBPDiagonal=0 ,tiQBPLado=0 ,tiQBPMatch=0 ,tiQBPMissMatch=0 ,tiQBPGap=0 ;

    //Pega as coordenadas do valor maximo, score maximo e quantidade de scores presentes
    QtdPaths = CQBPMatrix::GetMax(IdxMaxX, IdxMaxY, MaxScore);
    //Pega todas as coordenadas existentes do Score Máximo(Já que esperamos pegar o melhor)
    tPaths   = CQBPMatrix::GetMax(MaxScore);

    //Reserva o numero de listas necessário
    vTraceBackList = vector< vector<CQBPMatrixValue> >(QtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

    //Monta todos os paths identificados
    for(uint i=0;i<QtdPaths;i++)
    {
       TraceEnd = false;
       IdxMaxX  = tPaths[i].Px;
       IdxMaxY  = tPaths[i].Py;
       //Realiza o caminhamento
       while (!TraceEnd)
       {
           //obtem valor e direção nos indices X,Y
           iValue = CQBPMatrix::GetVal(IdxMaxX,IdxMaxY, iDirection , bMatch);

           if (iValue == 0)
           {
               TraceEnd = true;
               continue;
           }

           //obtem informação de depuração
           CQBPMatrix::GetDebbug(IdxMaxX,IdxMaxY,tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

           CQBPMatrixValue tValue;

           tValue.bQBPMatch     = bMatch;
           tValue.iQBPDirection = iDirection;
           tValue.iQBPRefX      = IdxMaxX;
           tValue.iQBPRefY      = IdxMaxY;
           tValue.iQBPValue     = iValue;

           //Debbug Info
           tValue.iQBPTopo      =tiQBPTopo;
           tValue.iQBPDiagonal  =tiQBPDiagonal;
           tValue.iQBPLado      =tiQBPLado;
           tValue.iQBPMatch     =tiQBPMatch;
           tValue.iQBPMissMatch =tiQBPMissMatch;
           tValue.iQBPGap       =tiQBPGap;

           vTraceBackList[i].push_back(tValue);

           //decrementa indices de acordo com a direção de origem do valor
           switch (iDirection)
           {
              case QBP_VAL_DIR_DIAG:
              {
                  IdxMaxX--; IdxMaxY--;
              }break;
              case QBP_VAL_DIR_LEFT:
              {
                  IdxMaxX--;
              }break;
              case QBP_VAL_DIR_TOP:
              {
                  IdxMaxY--;
              }break;
           }
       }
    }

    uint GreaterPathScore=0;
    uint GreaterPathScoreIndex=0;
    for(int i=0;i<vTraceBackList.size();i++)
    {
        if(i==0)
        {
            int tTraceScore = 0;
            for (int j = 0; j < vTraceBackList[i].size(); j++)
            {
                //Incluido na pergunta se match == true pois queremos apenas acertos(qdo diagonal com false significa update)
                if (vTraceBackList[i][j].iQBPDirection == QBP_VAL_DIR_DIAG && vTraceBackList[i][j].bQBPMatch == true)
                {
                    tTraceScore++;
                }
            }

            GreaterPathScore = tTraceScore;
            GreaterPathScoreIndex= i;
            continue;
        }

        int tTraceScore = 0;
        for (int j = 0; j < vTraceBackList[i].size(); j++)
        {
            //Incluido na pergunta se match == true pois queremos apenas acertos(qdo diagonal com false significa update)
            if (vTraceBackList[i][j].iQBPDirection == QBP_VAL_DIR_DIAG && vTraceBackList[i][j].bQBPMatch == true)
            {
                tTraceScore++;
            }
        }

        if(GreaterPathScore < tTraceScore)
        {
            GreaterPathScore = tTraceScore;
            GreaterPathScoreIndex = i;
        }
    }

    //Agora que já temos o maior path desejado, copiamos ele para o principal
    vTraceBack       = vTraceBackList[GreaterPathScoreIndex];
    iQBPMaskPathSize = (int)vTraceBack.size();
    iQBPMaskQtdPaths = (uint)vTraceBackList.size();

    return true;
}

bool CQBPMask::TraceBackG1()
{
    bool   TraceEnd = false;
    int    IdxMaxX, IdxMaxY, MaxScore , QtdPaths;
    int    iValue=0, iDirection;
    bool   bMatch;
    vector<path> tPaths;

    //Debug Info
    int  tiQBPTopo=0 ,tiQBPDiagonal=0 ,tiQBPLado=0 ,tiQBPMatch=0 ,tiQBPMissMatch=0 ,tiQBPGap=0 ;

    //Pega as coordenadas do valor maximo, score maximo e quantidade de scores presentes
    QtdPaths = CQBPMatrix::GetMax(IdxMaxX, IdxMaxY, MaxScore);
    //Pega todas as coordenadas existentes do Score Máximo(Já que esperamos pegar o melhor)
    tPaths   = CQBPMatrix::GetMax(MaxScore);

    //Reserva o numero de listas necessário
    vTraceBackList = vector< vector<CQBPMatrixValue> >(QtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

    //Monta todos os paths identificados
    for(uint i=0;i<QtdPaths;i++)
    {
       TraceEnd = false;
       IdxMaxX  = tPaths[i].Px;
       IdxMaxY  = tPaths[i].Py;
       //Realiza o caminhamento
       while (!TraceEnd)
       {
           //obtem valor e direção nos indices X,Y
           iValue = CQBPMatrix::GetVal(IdxMaxX, IdxMaxY, iDirection , bMatch);

           if (iValue == 0)
           {
               TraceEnd = true;
               continue;
           }

           //obtem informação de depuração
           CQBPMatrix::GetDebbug(IdxMaxX,IdxMaxY,tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

           CQBPMatrixValue tValue;

           tValue.bQBPMatch     = bMatch;
           tValue.iQBPDirection = iDirection;
           tValue.iQBPRefX      = IdxMaxX;
           tValue.iQBPRefY      = IdxMaxY;
           tValue.iQBPValue     = iValue;

           //Debbug Info
           tValue.iQBPTopo      =tiQBPTopo;
           tValue.iQBPDiagonal  =tiQBPDiagonal;
           tValue.iQBPLado      =tiQBPLado;
           tValue.iQBPMatch     =tiQBPMatch;
           tValue.iQBPMissMatch =tiQBPMissMatch;
           tValue.iQBPGap       =tiQBPGap;

           vTraceBackList[i].push_back(tValue);

           //decrementa indices de acordo com a direção de origem do valor
           switch (iDirection)
           {
              case QBP_VAL_DIR_DIAG:
              {
                  IdxMaxX--; IdxMaxY--;
              }break;
              case QBP_VAL_DIR_LEFT:
              {
                  IdxMaxX--;
              }break;
              case QBP_VAL_DIR_TOP:
              {
                  IdxMaxY--;
              }break;
           }
       }
    }

    uint GreaterPathSize=0;
    uint GreaterPathIndex=0;
    //Calcula qual é o maior path da Lista
    for(uint i=0 ; i<vTraceBackList.size();i++ )
    {
        if(i==0)
        {
            GreaterPathSize = (uint)vTraceBackList[i].size();
            GreaterPathIndex= i;
            continue;
        }

        if(GreaterPathSize < (uint)vTraceBackList[i].size())
        {
            GreaterPathSize = (uint)vTraceBackList[i].size();
            GreaterPathIndex= i;
        }
    }

    //Agora que já temos o maior path desejado, copiamos ele para o principal
    vTraceBack = vTraceBackList[GreaterPathIndex];
    iQBPMaskPathSize = (int)vTraceBack.size();
    iQBPMaskQtdPaths = (uint)vTraceBackList.size();

    return true;
}

bool CQBPMask::TraceBackA1()
{
    bool   TraceEnd = false;
    int    IdxMaxX, IdxMaxY, MaxScore , QtdPaths;
    int    iValue=0, iDirection;
    bool   bMatch;
    vector<path> tPaths;

    //Debug Info
    int  tiQBPTopo=0 ,tiQBPDiagonal=0 ,tiQBPLado=0 ,tiQBPMatch=0 ,tiQBPMissMatch=0 ,tiQBPGap=0 ;

    //Pega as coordenadas do valor maximo, score maximo e quantidade de scores presentes
    QtdPaths = CQBPMatrix::GetMax(IdxMaxX, IdxMaxY, MaxScore);
    //Pega todas as coordenadas existentes do Score Máximo(Já que esperamos pegar o melhor)
    tPaths   = CQBPMatrix::GetMax(MaxScore);

    //Reserva o numero de listas necessário
    vTraceBackList = vector< vector<CQBPMatrixValue> >(QtdPaths, vector<CQBPMatrixValue>(0,CQBPMatrixValue()));

    //Monta todos os paths identificados
    for(uint i=0;i<QtdPaths;i++)
    {
       TraceEnd = false;
       IdxMaxX  = tPaths[i].Px;
       IdxMaxY  = tPaths[i].Py;
       //Realiza o caminhamento
       while (!TraceEnd)
       {
           //obtem valor e direção nos indices X,Y
           iValue = CQBPMatrix::GetVal(IdxMaxX, IdxMaxY, iDirection , bMatch);

           if (iValue == 0)
           {
               TraceEnd = true;
               continue;
           }

           //obtem informação de depuração
           CQBPMatrix::GetDebbug(IdxMaxX,IdxMaxY,tiQBPTopo,tiQBPDiagonal,tiQBPLado,tiQBPMatch,tiQBPMissMatch,tiQBPGap);

           CQBPMatrixValue tValue;

           tValue.bQBPMatch     = bMatch;
           tValue.iQBPDirection = iDirection;
           tValue.iQBPRefX      = IdxMaxX;
           tValue.iQBPRefY      = IdxMaxY;
           tValue.iQBPValue     = iValue;

           //Debbug Info
           tValue.iQBPTopo      =tiQBPTopo;
           tValue.iQBPDiagonal  =tiQBPDiagonal;
           tValue.iQBPLado      =tiQBPLado;
           tValue.iQBPMatch     =tiQBPMatch;
           tValue.iQBPMissMatch =tiQBPMissMatch;
           tValue.iQBPGap       =tiQBPGap;

           vTraceBackList[i].push_back(tValue);

           //decrementa indices de acordo com a direção de origem do valor
           switch (iDirection)
           {
              case QBP_VAL_DIR_DIAG:
              {
                  IdxMaxX--; IdxMaxY--;
              }break;
              case QBP_VAL_DIR_LEFT:
              {
                  IdxMaxX--;
              }break;
              case QBP_VAL_DIR_TOP:
              {
                  IdxMaxY--;
              }break;
           }
       }
    }

    iQBPMaskQtdPaths = (uint)vTraceBackList.size();

    return true;
}

//Calcula o score de similaridade baseado no tipo de processamento
int CQBPMask::TraceBackScore()
{
    int tTraceScore = 0;


    //Para todos os casos usamos apenas um path, porém para o A1 usamos todos
    if (iQBPPostProcType == QBP_POSTPROC_TYPE_F1 && iQBPMaskPathSize      == 0)return 0;
    if (iQBPPostProcType == QBP_POSTPROC_TYPE_B1 && iQBPMaskPathSize      == 0)return 0;
    if (iQBPPostProcType == QBP_POSTPROC_TYPE_G1 && iQBPMaskPathSize      == 0)return 0;
    if (iQBPPostProcType == QBP_POSTPROC_TYPE_A1 && vTraceBackList.size() == 0)return 0;


    if(iQBPPostProcType != QBP_POSTPROC_TYPE_A1)
    {
       for (int i = 0; i < iQBPMaskPathSize; i++)
       {
          //Incluido na pergunta se match == true pois queremos apenas acertos(qdo diagonal com false significa update)
          if (vTraceBack[i].iQBPDirection == QBP_VAL_DIR_DIAG && vTraceBack[i].bQBPMatch == true)
          {
              tTraceScore++;
          }
       }
    }
    else
    {
        for (int i = 0; i < vTraceBackList.size(); i++)
        {
           for(int j=0;j<vTraceBackList[i].size();j++)
           {
              //Incluido na pergunta se match == true pois queremos apenas acertos(qdo diagonal com false significa update)
              if (vTraceBackList[i][j].iQBPDirection == QBP_VAL_DIR_DIAG && vTraceBackList[i][j].bQBPMatch == true)
              {
                  tTraceScore++;
              }
           }
        }
    }

    return tTraceScore;
}


int CQBPMask::CalculaSimilaridade(int pIndiceX, int pIndiceY, bool &pMatch)
{
    int resultado;
    if ((BufferA[pIndiceX -1].sQBP_Note == BufferB[pIndiceY -1].sQBP_Note))
    {
        resultado = iQBPMatch;
        pMatch = true;
    }
    else
    {
        resultado = iQBPMissMatch;
        pMatch = false;
    }
    return resultado;
}

int CQBPMask::CalculaScoreMaximo(int &pDirection)
{

    if (iQBPTopo > iQBPDiagonal && iQBPTopo > iQBPLado)
    {
        pDirection = QBP_VAL_DIR_TOP;
        return iQBPTopo;
    }

    if (iQBPDiagonal > iQBPTopo && iQBPDiagonal > iQBPLado)
    {
        pDirection = QBP_VAL_DIR_DIAG;
        return iQBPDiagonal;
    }

    if (iQBPLado > iQBPDiagonal && iQBPLado > iQBPTopo)
    {
        pDirection = QBP_VAL_DIR_LEFT;
        return iQBPLado;
    }

    pDirection = QBP_VAL_DIR_NONE;
    return 0;
}

void CQBPMask::GetPath(CQBPMatrixValue *pQBPPath)
{
    for(uint i=0;i< iQBPMaskPathSize;i++)
    {
       pQBPPath[i].iQBPRefX      =vTraceBack[i].iQBPRefX;
       pQBPPath[i].iQBPRefY      =vTraceBack[i].iQBPRefY;
       pQBPPath[i].iQBPValue     =vTraceBack[i].iQBPValue;
       pQBPPath[i].iQBPDirection =vTraceBack[i].iQBPDirection;
       pQBPPath[i].bQBPMatch     =vTraceBack[i].bQBPMatch;

       //Debbug Info
       pQBPPath[i].iQBPTopo      =vTraceBack[i].iQBPTopo;
       pQBPPath[i].iQBPDiagonal  =vTraceBack[i].iQBPDiagonal;
       pQBPPath[i].iQBPLado      =vTraceBack[i].iQBPLado;
       pQBPPath[i].iQBPMatch     =vTraceBack[i].iQBPMatch;
       pQBPPath[i].iQBPMissMatch =vTraceBack[i].iQBPMissMatch;
       pQBPPath[i].iQBPGap       =vTraceBack[i].iQBPGap;
    }

}

void CQBPMask::GetPathValue(int pValueID, CQBPMatrixValue *pQBPPath)
{
   pQBPPath->iQBPRefX      =vTraceBack[pValueID].iQBPRefX;
   pQBPPath->iQBPRefY      =vTraceBack[pValueID].iQBPRefY;
   pQBPPath->iQBPValue     =vTraceBack[pValueID].iQBPValue;
   pQBPPath->iQBPDirection =vTraceBack[pValueID].iQBPDirection;
   pQBPPath->bQBPMatch     =vTraceBack[pValueID].bQBPMatch;

   //Debbug Info
   pQBPPath->iQBPTopo      =vTraceBack[pValueID].iQBPTopo;
   pQBPPath->iQBPDiagonal  =vTraceBack[pValueID].iQBPDiagonal;
   pQBPPath->iQBPLado      =vTraceBack[pValueID].iQBPLado;
   pQBPPath->iQBPMatch     =vTraceBack[pValueID].iQBPMatch;
   pQBPPath->iQBPMissMatch =vTraceBack[pValueID].iQBPMissMatch;
   pQBPPath->iQBPGap       =vTraceBack[pValueID].iQBPGap;

}

void CQBPMask::GetPathSize(int &pQBPPathSize)
{
    pQBPPathSize = iQBPMaskPathSize;
}

void CQBPMask::GetBuffers(vector<stQBPMusicBuffer> &pBufferA, vector<stQBPMusicBuffer> &pBufferB)
{
    pBufferA = vQBP_IBufferA;
    pBufferB = vQBP_IBufferB;
}

void CQBPMask::GetBuffers(vector<stQBPStringBuffer> &pBufferA, vector<stQBPStringBuffer> &pBufferB)
{
    pBufferA = BufferA;
    pBufferB = BufferB;
}

void CQBPMask::CleanUp()
{
    BufferA.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    BufferA.shrink_to_fit();

    BufferB.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    BufferB.shrink_to_fit();

    SongNameA.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    SongNameA.shrink_to_fit();

    SongNameB.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    SongNameB.shrink_to_fit();

    vQBP_IBufferA.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    vQBP_IBufferA.shrink_to_fit();

    vQBP_IBufferB.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    vQBP_IBufferB.shrink_to_fit();

    CQBPMatrix::Clear();

    vTraceBack.clear();
    vTraceBack.shrink_to_fit();

    //Limpa Lista de Paths
    for (uint Idx = 0; Idx < vTraceBackList.size(); Idx++)
    {
        vTraceBackList[Idx].clear();
        vTraceBackList[Idx].shrink_to_fit();
    }

    //Para garantir Limpeza Pato Purific...
    vTraceBackList.clear();
    vTraceBackList.shrink_to_fit();

}
