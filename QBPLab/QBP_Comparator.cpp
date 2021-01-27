#include "QBP_Comparator.h"

CQBPComparator::CQBPComparator()
{
    //Cria a Substitution Matrix Inicial
    pQBPSubstMatrix = new CQBPMatrix(10, 10);
    if(!pQBPSubstMatrix)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
        msgBox.exec();
    }
    //Cria uma nova mascara de processamento
    pQBPMask = new CQBPMask();
    if(!pQBPMask)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPMask!.");
        msgBox.exec();
    }

    //Cria repositorio de buscas(Obrigatorio ter o comparador)
    pQBPSearchResults = new CQBPSearchResults();
    if(!pQBPSearchResults)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPSearchResults!.");
        msgBox.exec();
    }

    iQBPBufferType  = QBP_BUFFER_TYPE_CHR;
    iQBPDatasetType = QBP_LOAD_TARGET_TESTSET;
    bQBPDebbugMode  = false;
}

CQBPComparator::CQBPComparator(const CQBPComparator &obj)
{
    //Atenção está errado passar somente a referencia!!!
    //devido a termos apenas uma instancia ainda não deu pau...
    pQBPSubstMatrix = obj.pQBPSubstMatrix;
    pQBPMask        = obj.pQBPMask;
    iQBPBufferType  = obj.iQBPBufferType;
    iQBPDatasetType = obj.iQBPDatasetType;
    bQBPDebbugMode  = obj.bQBPDebbugMode;
    //TODO:
    //Incluir SearchResults
}

CQBPComparator::CQBPComparator(int pQBP_MatrixType)
{
    //Cria a Substitution Matrix Inicial
    pQBPSubstMatrix = new CQBPMatrix(10, 10);
    if(!pQBPSubstMatrix)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
        msgBox.exec();
    }

    //Cria uma nova mascara de processamento
    switch (pQBP_MatrixType)
    {
    case QBP_MATRIX_TYPE_ORIGIN:
    {
        pQBPMask = new CQBPMask      ();
        iQBPBufferType  = QBP_BUFFER_TYPE_CHR;
    }break;
    case QBP_MATRIX_TYPE_MUSSUM:
    {
        pQBPMask = new CQBPMussumMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_CHR;
    }break;
    case QBP_MATRIX_TYPE_MUSSIX :
    {
        pQBPMask = new CQBPMussixMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_STR;
    }break;
    case QBP_MATRIX_TYPE_MUSSAT :
    {
        pQBPMask        = new CQBPAttitudeMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_STR;
    }break;
    default: {pQBPMask = new CQBPMask(); }break;
    }

    if(!pQBPMask)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPMask!.");
        msgBox.exec();
    }

    //Cria repositorio de buscas(Obrigatorio ter o comparador)
    pQBPSearchResults = new CQBPSearchResults();
    if(!pQBPSearchResults)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPSearchResults!.");
        msgBox.exec();
    }

    iQBPDatasetType = QBP_LOAD_TARGET_TESTSET;
    bQBPDebbugMode  = false;
}

CQBPComparator::~CQBPComparator()
{

}


bool CQBPComparator::SetUserBuffer(vector<stQBPStringBuffer> pQBPBufferB,string pQBPSongNameB)
{
    pQBPMask->BufferB.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMask->BufferB.shrink_to_fit();

    pQBPMask->BufferB   = pQBPBufferB;
    pQBPMask->SongNameB = pQBPSongNameB;
    pQBPMask->iQBPBufferType = QBP_BUFFER_TYPE_CHR;

    iQBPBufferType = pQBPMask->iQBPBufferType;

    return true;
}

bool CQBPComparator::SetCompBuffer(vector<stQBPStringBuffer> pQBPBufferA,string pQBPSongNameA)
{
    pQBPMask->BufferA.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMask->BufferA.shrink_to_fit();

    pQBPMask->BufferA = pQBPBufferA;
    pQBPMask->SongNameA = pQBPSongNameA;
    pQBPMask->iQBPBufferType = QBP_BUFFER_TYPE_CHR;

    iQBPBufferType = pQBPMask->iQBPBufferType;

    return true;
}

bool CQBPComparator::SetUserBuffer(vector<stQBPMusicBuffer> vQBP_IBufferB, string pQBPSongNameB)
{
    pQBPMask->vQBP_IBufferB.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMask->vQBP_IBufferB.shrink_to_fit();

    pQBPMask->vQBP_IBufferB = vQBP_IBufferB;
    pQBPMask->SongNameB = pQBPSongNameB;
    pQBPMask->iQBPBufferType = QBP_BUFFER_TYPE_STR;

    iQBPBufferType = pQBPMask->iQBPBufferType;
    return true;
}

bool CQBPComparator::SetCompBuffer(vector<stQBPMusicBuffer> vQBP_IBufferA, string pQBPSongNameA)
{
    pQBPMask->vQBP_IBufferA.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMask->vQBP_IBufferA.shrink_to_fit();

    pQBPMask->vQBP_IBufferA = vQBP_IBufferA;
    pQBPMask->SongNameA = pQBPSongNameA;
    pQBPMask->iQBPBufferType = QBP_BUFFER_TYPE_STR;

    iQBPBufferType = pQBPMask->iQBPBufferType;
    return true;
}

bool CQBPComparator::SetCompType(int pQBP_MatrixType , int pQBP_PProcType)
{
    //Limpa se criou anteriormente
    if(pQBPMask)
    {
        delete pQBPMask;
        pQBPMask=NULL;
    }
    //Cria uma nova mascara de processamento
    switch (pQBP_MatrixType)
    {
    case QBP_MATRIX_TYPE_ORIGIN:
    {
        pQBPMask = new CQBPMask      ();
        iQBPBufferType  = QBP_BUFFER_TYPE_CHR;
    }break;
    case QBP_MATRIX_TYPE_MUSSUM:
    {
        pQBPMask = new CQBPMussumMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_CHR;
    }break;
    case QBP_MATRIX_TYPE_MUSSIX :
    {
        pQBPMask = new CQBPMussixMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_STR;
    }break;
    case QBP_MATRIX_TYPE_MUSSAT :
    {
        pQBPMask        = new CQBPAttitudeMask();
        iQBPBufferType  = QBP_BUFFER_TYPE_STR;
    }break;
    default: {pQBPMask = new CQBPMask(); }break;
    }

    //Configura o PosProcessamento do algoritmo(Não confundir com Pos processamento da Busca!)
    iQBPPostProcessingType = (uint)pQBP_PProcType;
    pQBPMask->SetPProcType(iQBPPostProcessingType);

    if(!pQBPMask)
    {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível alocar memoria para QBPMask!.");
        msgBox.exec();
    }
    return true;
}

bool CQBPComparator::SetDatasetType(uint pQBP_DatasetType )
{
    iQBPDatasetType =pQBP_DatasetType;
    return true;
}

bool CQBPComparator::AddSearch()
{
    //Inclui uma busca nova no repositorio(e pega o ID)
    pQBPSearchResults->addSearch(iQBPCurrentSearch);
    return true;
}

bool CQBPComparator::AddSearch(QString pQBPSearchName)
{
    //Inclui uma busca nova no repositorio(e pega o ID)
    pQBPSearchResults->addSearch(iQBPCurrentSearch,pQBPSearchName);
    return true;
}
bool CQBPComparator::AddAlignment()
{
    //Inclui um alinhamento novo no repositorio(e pega o ID)
    pQBPSearchResults->addAlignment(iQBPCurrentAlignment);
    return true;
}
int CQBPComparator::CompareBuffer()
{
    int  tSimilarityScore = 0;
    uint tSearchID;

    if(iQBPBufferType==QBP_BUFFER_TYPE_CHR)if (pQBPMask->BufferA.size() <= 0 && pQBPMask->BufferB.size() <= 0)return 0;
    if(iQBPBufferType==QBP_BUFFER_TYPE_STR)if (pQBPMask->vQBP_IBufferA.size() <= 0 && pQBPMask->vQBP_IBufferB.size() <= 0)return 0;

    //prepara os valores da substitution matrix
    pQBPMask->PreparaMatrix();

    //Calcula e Imprime Matriz de Scores
    pQBPMask->CalculaScores();

    //Faz traceback e imprime melhor alinhamento local possivel
    pQBPMask->TraceBack();

    //Calcula o scoreFinal
    tSimilarityScore = pQBPMask->TraceBackScore();

    //Coleta o resultado do alinhamento.
    //Isto não é feito depois devido a programação dinâmica...
    //Retirado tratamento de teste para possibilitar agota listas geradas todas apontando para base full...
    //if(iQBPDatasetType != QBP_LOAD_TARGET_DATASET)CollectAlignment();

    if(bQBPDebbugMode)CollectAlignment();

    //calcula e retorna o score de similaridade
    return tSimilarityScore;
}

bool CQBPComparator::CollectAlignment()
{
    //get the current search
    CQBPSearch *tSearch = pQBPSearchResults->getSearch(iQBPCurrentSearch);
    //extract the current Alignment
    ExtractAlignment(tSearch,iQBPCurrentAlignment);
    return true;
}

bool CQBPComparator::ExtractAlignment(CQBPSearch *tSearch, uint pAlignmentID)
{
    int Idx;

    //If we not have a mask....
    if(!pQBPMask)return false;

    tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeX = CQBPMatrix::GetSizeX();
    tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeY = CQBPMatrix::GetSizeY();

    //If we have an invalid Matrix Size
    if(tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeX <= 0 || tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeY <= 0)return false;

    tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPSearchMatrix     = new CQBPMatrixValue*[tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeY];

    for (Idx = 0; Idx < tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeY; Idx++)
    {
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPSearchMatrix[Idx] = new CQBPMatrixValue[tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPMatrixSizeX];
    }

    tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPResultPathSize = pQBPMask->iQBPMaskPathSize;

    //aloca o espaço necessário...
    tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath = new CQBPMatrixValue[tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPResultPathSize];

    //Extract processing information from Mask.
    for(int i=0;i<tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPResultPathSize;i++)
    {
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPRefX      =pQBPMask->vTraceBack[i].iQBPRefX;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPRefY      =pQBPMask->vTraceBack[i].iQBPRefY;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPValue     =pQBPMask->vTraceBack[i].iQBPValue;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPDirection =pQBPMask->vTraceBack[i].iQBPDirection;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].bQBPMatch     =pQBPMask->vTraceBack[i].bQBPMatch;

        //debug info
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPTopo      = pQBPMask->vTraceBack[i].iQBPTopo;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPDiagonal  = pQBPMask->vTraceBack[i].iQBPDiagonal;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPLado      = pQBPMask->vTraceBack[i].iQBPLado;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPMatch     = pQBPMask->vTraceBack[i].iQBPMatch;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPMissMatch = pQBPMask->vTraceBack[i].iQBPMissMatch;
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPath[i].iQBPGap       = pQBPMask->vTraceBack[i].iQBPGap;
    }


    //Processa Grafos de Path
    //aloca espaço necessário para listas de paths.
    //Reserva o numero de listas necessário

    int tQtdPaths=pQBPMask->iQBPMaskQtdPaths;

    tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPResultQtdPaths = tQtdPaths;

    //aloca o espaço necessário...
    tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList = new stQBPGraphListMember[tQtdPaths];
    if(!tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList)
    {
        QMessageBox msgBox;
        msgBox.setText("Erro ao alocar memoria para Lista Path! QBPSearch.");
        msgBox.exec();
    }

    //Initialize the graph Lists
    for (Idx = 0; Idx < tQtdPaths; Idx++)
    {
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].iQBP_QtdPathNotes = pQBPMask->vTraceBackList[Idx].size();
        tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath     = new CQBPMatrixValue[pQBPMask->vTraceBackList[Idx].size()];
    }

    //Copy the Values...
    for (Idx = 0; Idx < tQtdPaths; Idx++)
    {
        int tPathSize = pQBPMask->vTraceBackList[Idx].size();
        for(uint i=0;i<tPathSize;i++)
        {
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefX      =pQBPMask->vTraceBackList[Idx][i].iQBPRefX;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefY      =pQBPMask->vTraceBackList[Idx][i].iQBPRefY;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPValue     =pQBPMask->vTraceBackList[Idx][i].iQBPValue;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDirection =pQBPMask->vTraceBackList[Idx][i].iQBPDirection;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].bQBPMatch     =pQBPMask->vTraceBackList[Idx][i].bQBPMatch;

           //debug info
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPTopo      = pQBPMask->vTraceBackList[Idx][i].iQBPTopo;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDiagonal  = pQBPMask->vTraceBackList[Idx][i].iQBPDiagonal;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPLado      = pQBPMask->vTraceBackList[Idx][i].iQBPLado;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMatch     = pQBPMask->vTraceBackList[Idx][i].iQBPMatch;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMissMatch = pQBPMask->vTraceBackList[Idx][i].iQBPMissMatch;
           tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPGap       = pQBPMask->vTraceBackList[Idx][i].iQBPGap;
        }
    }

    tSearch->pQBPSearchAlignments[pAlignmentID]->sQBPUserBuffer         = pQBPMask->BufferA;
    tSearch->pQBPSearchAlignments[pAlignmentID]->sQBPSystemBuffer       = pQBPMask->BufferB;
    tSearch->pQBPSearchAlignments[pAlignmentID]->vQBPUserBuffer         = pQBPMask->vQBP_IBufferA;
    tSearch->pQBPSearchAlignments[pAlignmentID]->vQBPSystemBuffer       = pQBPMask->vQBP_IBufferB;
    tSearch->pQBPSearchAlignments[pAlignmentID]->iQBPBufferType         = pQBPMask->iQBPBufferType;


    tSearch->pQBPSearchAlignments[pAlignmentID]->sQBPSystemSongName = pQBPMask->SongNameA.c_str();
    tSearch->pQBPSearchAlignments[pAlignmentID]->sQBPUserSongName   = pQBPMask->SongNameB.c_str();

    //Extract all values from the SW Matrix since we cannot copy the static object in a new instance...
    if(!CQBPMatrix::Extract(tSearch->pQBPSearchAlignments[pAlignmentID]->pQBPSearchMatrix))return false;

    return true;
}

void CQBPComparator::CleanUp()
{
    pQBPMask->CleanUp();
    pQBPSearchResults->clearResults();
}
