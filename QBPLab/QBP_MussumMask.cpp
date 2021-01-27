#include "QBP_MussumMask.h"



CQBPMussumMask::CQBPMussumMask()
{
}


CQBPMussumMask::~CQBPMussumMask()
{
    //CleanUp();
}

bool CQBPMussumMask::PreparaMatrix()
{
    return CQBPMatrix::Dimensiona((int)BufferA.size(), (int)BufferB.size());
}

bool CQBPMussumMask::CalculaScores()
{

    for (int i = 1; i < CQBPMatrix::GetSizeX(); i++)
    {

        for (int j = 1; j < CQBPMatrix::GetSizeY(); j++)
        {
            int  iSimScore, iTempDir;
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

int CQBPMussumMask::CalculaSimilaridade(int pIndiceX, int pIndiceY, bool &pMatch)
{
    int resultado=0;
    int notaA,notaB;

    //Caso tenha um acerto calcula valor da Diagonal
    string a = BufferA[pIndiceX - 1].sQBP_Note;
    string b = BufferB[pIndiceY - 1].sQBP_Note;

    if(a=="C" )notaA=1;
    if(a=="Db")notaA=2;
    if(a=="D" )notaA=3;
    if(a=="Eb")notaA=4;
    if(a=="E" )notaA=5;
    if(a=="F" )notaA=6;
    if(a=="Gb")notaA=7;
    if(a=="G" )notaA=8;
    if(a=="Ab")notaA=9;
    if(a=="A" )notaA=10;
    if(a=="Bb")notaA=11;
    if(a=="B" )notaA=12;

    if (BufferA[pIndiceX - 1].sQBP_Note == BufferB[pIndiceY - 1].sQBP_Note)
    {

        if(a=="C"  && b=="C" ) resultado = 8;
        if(a=="Db" && b=="Db") resultado = 8;
        if(a=="D"  && b=="D" ) resultado = 4;
        if(a=="Eb" && b=="Eb") resultado = 10;
        if(a=="E"  && b=="E" ) resultado = 5;
        if(a=="F"  && b=="F" ) resultado = 5;
        if(a=="Gb" && b=="Gb") resultado = 6;
        if(a=="G"  && b=="G" ) resultado = 5;
        if(a=="Ab" && b=="Ab") resultado = 10;
        if(a=="A"  && b=="A" ) resultado = 4;
        if(a=="Bb" && b=="Bb") resultado = 10;
        if(a=="B"  && b=="B" ) resultado = 5;

        iQBPMatch = resultado;

        pMatch = true;
    }
    else
    {
        switch(notaA)
        {
        case 1:
        {
            if(a=="C" && b=="Db") resultado = -1;
            if(a=="C" && b=="D" ) resultado = -2;
            if(a=="C" && b=="Eb") resultado = -3;
            if(a=="C" && b=="E" ) resultado = -4;
            if(a=="C" && b=="F" ) resultado = -5;
            if(a=="C" && b=="G" ) resultado = -6;
            if(a=="C" && b=="G" ) resultado = -7;
            if(a=="C" && b=="Ab") resultado = -8;
            if(a=="C" && b=="A" ) resultado = -9;
            if(a=="C" && b=="Bb") resultado = -10;
            if(a=="C" && b=="B" ) resultado = -11;
        }break;
        case 2:
        {
            if(a=="Db" && b=="C" ) resultado = -1;
            if(a=="Db" && b=="D" ) resultado = -1;
            if(a=="Db" && b=="Eb") resultado = -2;
            if(a=="Db" && b=="E" ) resultado = -3;
            if(a=="Db" && b=="F" ) resultado = -4;
            if(a=="Db" && b=="Gb") resultado = -5;
            if(a=="Db" && b=="G" ) resultado = -6;
            if(a=="Db" && b=="Ab") resultado = -7;
            if(a=="Db" && b=="A" ) resultado = -8;
            if(a=="Db" && b=="Bb") resultado = -9;
            if(a=="Db" && b=="B" ) resultado = -10;
        }break;
        case 3:
        {

            if(a=="D" && b=="C" ) resultado = -2;
            if(a=="D" && b=="Db") resultado = -1;
            if(a=="D" && b=="Eb") resultado = -1;
            if(a=="D" && b=="E" ) resultado = -2;
            if(a=="D" && b=="F" ) resultado = -3;
            if(a=="D" && b=="Gb") resultado = -4;
            if(a=="D" && b=="G" ) resultado = -5;
            if(a=="D" && b=="Ab") resultado = -6;
            if(a=="D" && b=="A" ) resultado = -7;
            if(a=="D" && b=="Bb") resultado = -8;
            if(a=="D" && b=="B" ) resultado = -9;

        }break;
        case 4:
        {
            if(a=="Eb" && b=="C" ) resultado = -3;
            if(a=="Eb" && b=="Db") resultado = -2;
            if(a=="Eb" && b=="D" ) resultado = -1;
            if(a=="Eb" && b=="E" ) resultado = -1;
            if(a=="Eb" && b=="F" ) resultado = -2;
            if(a=="Eb" && b=="Gb") resultado = -3;
            if(a=="Eb" && b=="G" ) resultado = -4;
            if(a=="Eb" && b=="Ab") resultado = -5;
            if(a=="Eb" && b=="A" ) resultado = -6;
            if(a=="Eb" && b=="Bb") resultado = -7;
            if(a=="Eb" && b=="B" ) resultado = -8;
        }break;
        case 5:
        {
            if(a=="E" && b=="C" ) resultado = -4;
            if(a=="E" && b=="Db") resultado = -3;
            if(a=="E" && b=="D" ) resultado = -2;
            if(a=="E" && b=="Eb") resultado = -1;
            if(a=="E" && b=="F" ) resultado = -1;
            if(a=="E" && b=="Gb") resultado = -2;
            if(a=="E" && b=="G" ) resultado = -3;
            if(a=="E" && b=="Ab") resultado = -4;
            if(a=="E" && b=="A" ) resultado = -5;
            if(a=="E" && b=="Bb") resultado = -6;
            if(a=="E" && b=="B" ) resultado = -7;
        }break;
        case 6:
        {
            if(a=="F" && b=="C" ) resultado = -5;
            if(a=="F" && b=="Db") resultado = -4;
            if(a=="F" && b=="D" ) resultado = -3;
            if(a=="F" && b=="Eb") resultado = -2;
            if(a=="F" && b=="E" ) resultado = -1;
            if(a=="F" && b=="Gb") resultado = -1;
            if(a=="F" && b=="G" ) resultado = -2;
            if(a=="F" && b=="Ab") resultado = -3;
            if(a=="F" && b=="A" ) resultado = -4;
            if(a=="F" && b=="Bb") resultado = -5;
            if(a=="F" && b=="B" ) resultado = -6;
        }break;
        case 7:
        {
            if(a=="Gb" && b=="C" ) resultado = -6;
            if(a=="Gb" && b=="Db") resultado = -5;
            if(a=="Gb" && b=="D" ) resultado = -4;
            if(a=="Gb" && b=="Eb") resultado = -3;
            if(a=="Gb" && b=="E" ) resultado = -2;
            if(a=="Gb" && b=="F" ) resultado = -1;
            if(a=="Gb" && b=="G" ) resultado = -1;
            if(a=="Gb" && b=="Ab") resultado = -2;
            if(a=="Gb" && b=="A" ) resultado = -3;
            if(a=="Gb" && b=="Bb") resultado = -4;
            if(a=="Gb" && b=="B" ) resultado = -5;
        }break;
        case 8:
        {
            if(a=="G" && b=="C" ) resultado = -7;
            if(a=="G" && b=="Db") resultado = -6;
            if(a=="G" && b=="D" ) resultado = -5;
            if(a=="G" && b=="Eb") resultado = -4;
            if(a=="G" && b=="E" ) resultado = -3;
            if(a=="G" && b=="F" ) resultado = -2;
            if(a=="G" && b=="Gb") resultado = -1;
            if(a=="G" && b=="Ab") resultado = -1;
            if(a=="G" && b=="A" ) resultado = -2;
            if(a=="G" && b=="Bb") resultado = -3;
            if(a=="G" && b=="B" ) resultado = -4;
        }break;
        case 9:
        {
            if(a=="Ab" && b=="C" ) resultado = -8;
            if(a=="Ab" && b=="Db") resultado = -7;
            if(a=="Ab" && b=="D" ) resultado = -6;
            if(a=="Ab" && b=="Eb") resultado = -5;
            if(a=="Ab" && b=="E" ) resultado = -4;
            if(a=="Ab" && b=="F" ) resultado = -3;
            if(a=="Ab" && b=="Gb") resultado = -2;
            if(a=="Ab" && b=="G" ) resultado = -1;
            if(a=="Ab" && b=="A" ) resultado = -1;
            if(a=="Ab" && b=="Bb") resultado = -2;
            if(a=="Ab" && b=="B" ) resultado = -3;
        }break;
        case 10:
        {
            if(a=="A" && b=="C" ) resultado = -9;
            if(a=="A" && b=="Db") resultado = -8;
            if(a=="A" && b=="D" ) resultado = -7;
            if(a=="A" && b=="Eb") resultado = -6;
            if(a=="A" && b=="E" ) resultado = -5;
            if(a=="A" && b=="F" ) resultado = -4;
            if(a=="A" && b=="Gb") resultado = -3;
            if(a=="A" && b=="G" ) resultado = -2;
            if(a=="A" && b=="Ab") resultado = -1;
            if(a=="A" && b=="Bb") resultado = -1;
            if(a=="A" && b=="B" ) resultado = -2;
        }break;
        case 11:
        {
            if(a=="Bb" && b=="C" ) resultado = -10;
            if(a=="Bb" && b=="Db") resultado = -9;
            if(a=="Bb" && b=="D" ) resultado = -8;
            if(a=="Bb" && b=="Eb") resultado = -7;
            if(a=="Bb" && b=="E" ) resultado = -6;
            if(a=="Bb" && b=="F" ) resultado = -5;
            if(a=="Bb" && b=="Gb") resultado = -4;
            if(a=="Bb" && b=="G" ) resultado = -3;
            if(a=="Bb" && b=="Ab") resultado = -2;
            if(a=="Bb" && b=="A" ) resultado = -1;
            if(a=="Bb" && b=="B" ) resultado = -1;
        }break;
        case 12:
        {
            if(a=="B" && b=="C" ) resultado = -11;
            if(a=="B" && b=="Db") resultado = -10;
            if(a=="B" && b=="D" ) resultado = -9;
            if(a=="B" && b=="Eb") resultado = -8;
            if(a=="B" && b=="E" ) resultado = -7;
            if(a=="B" && b=="F" ) resultado = -6;
            if(a=="B" && b=="Gb") resultado = -5;
            if(a=="B" && b=="G" ) resultado = -4;
            if(a=="B" && b=="Ab") resultado = -3;
            if(a=="B" && b=="A" ) resultado = -2;
            if(a=="B" && b=="Bb") resultado = -1;

        }break;
        }

        iQBPMissMatch = resultado;

        pMatch = false;
    }

    return resultado;
}
