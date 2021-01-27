#include "QBP_MussixMask.h"



CQBPMussixMask::CQBPMussixMask()
{
    iQBPOctave    = 5;
}


CQBPMussixMask::~CQBPMussixMask()
{
    //CleanUp();
}

bool CQBPMussixMask::PreparaMatrix()
{
    return CQBPMatrix::Dimensiona((int)vQBP_IBufferA.size(), (int)vQBP_IBufferB.size());
}

bool CQBPMussixMask::CalculaScores()
{

    for (int i = 1; i < CQBPMatrix::GetSizeX(); i++)
    {

        for (int j = 1; j < CQBPMatrix::GetSizeY(); j++)
        {
            int  iSimScore;
            int  iTempDir;
            bool bSimMatch, bTempMatch;

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
            CQBPMatrix::SetVal(i, j, iQBPScore, iQBPDirection, bSimMatch);
            CQBPMatrix::Debbug(i, j, iQBPTopo,iQBPDiagonal,iQBPLado,iQBPMatch,iQBPMissMatch,iQBPGap);
        }
    }

    return true;
}


int CQBPMussixMask::CalculaSimilaridade(int pIndiceX, int pIndiceY, bool &pMatch)
{
    int resultado=0;

    //Caso a distancia seja 0 é um Match , caso contrário um Mismatch
    if (CalculaDistancia(vQBP_IBufferA[pIndiceX - 1],vQBP_IBufferB[pIndiceY - 1])==0)
    {
        //O Valor de Match é a oitava onde a nota se encontra
        iQBPMatch     =   vQBP_IBufferB[pIndiceY - 1].iQBP_Octave;

        //Caso tenha um acerto atribui a oitava da musica(diagonal), onde neste caso responde dinamicamente pela oitava da nota.
        resultado = iQBPMatch;

        pMatch = true;
    }
    else
    {
        /***********************************************************/
        /*Teste do novo calculo de penalidade baseado nos contornos*/
        /***********************************************************/
        //O Valor de Mismatch é o negativo da oitava da nota sendo consultada
        int tQBPScaleNoteA = vQBP_IBufferB[pIndiceY - 1].iQBP_Octave;

        //Garante valor negativo de Mismatch
        if(tQBPScaleNoteA>0)iQBPMissMatch = (tQBPScaleNoteA) * (-1);
        if(tQBPScaleNoteA<0)iQBPMissMatch = (tQBPScaleNoteA);

        resultado = iQBPMissMatch;

        //Calcula a penalidade pela formula dos contornos...
        double dMinFreq=0.0;
        double dMaxFreq=0.0;
        double dNorFreq=0.0;

        //Obtem as frequencias minima e máxima
        switch(vQBP_IBufferA[pIndiceX - 1].iQBP_Octave)
        {
        case  0:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  1:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  2:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  3:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  4:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  5:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  6:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  7:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  8:{dMinFreq=261.63; dMaxFreq = 493.88;}break;
        case  9:{dMinFreq=4186.0; dMaxFreq = 48.999;}break;
        case 10:{dMinFreq=51.913; dMaxFreq = 77.782;}break;
        }

        //Calcula Frequencia Normalizada
        dNorFreq = (vQBP_IBufferA[pIndiceX - 1].dQBP_Frequency - dMinFreq)/(dMaxFreq - dMinFreq);

        //Calcula qual foi o grau do erro do musico.
        float tQBPMistake = abs(dNorFreq / (vQBP_IBufferA[pIndiceX - 1].dQBP_Duration / 1000));
        //int tQBPMistake = abs(dNorFreq * (vQBP_IBufferA[pIndiceX - 1].dQBP_Duration / 1000));
        //int tQBPMistake = 1;

        iQBPGap = -abs(tQBPMistake);

        //Garante valor negativo no Gap
        if(iQBPGap>0)iQBPGap = (iQBPGap) * (-1);

        pMatch = false;
    }

    return resultado;
}

int CQBPMussixMask::CalculaDistancia(stQBPMusicBuffer  pSinalA ,stQBPMusicBuffer pSinalB)
{
    vector<int> tDistances;

    int tResultDistance=0;

    //Caso tenha um acerto na nota Simbolica atribui 1 a distancia no caso de erro
    string a = pSinalA.sQBP_Note;
    string b = pSinalB.sQBP_Note;

    if (a == b)tDistances.push_back(0);
    if (a != b)tDistances.push_back(1);

    //preenche vetor de distancias
    tDistances.push_back(pSinalA.iQBP_Pitch   - pSinalB.iQBP_Pitch);
    tDistances.push_back(pSinalA.iQBP_Contour - pSinalB.iQBP_Contour);
    tDistances.push_back(pSinalA.iQBP_Octave  - pSinalB.iQBP_Octave);

    //Calcula a Manhattan Distance entre as features.
    for (uint j = 0; j < tDistances.size(); j++)
    {
       tResultDistance += tDistances[j];
    }

    tDistances.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    tDistances.shrink_to_fit();

    return tResultDistance;
}
