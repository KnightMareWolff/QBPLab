#include "QBP_Alignment.h"

CQBPAlignment::~CQBPAlignment()
{

}

CQBPAlignment::CQBPAlignment()
{
    iQBPSearchID      =0;
    iQBPSearchType    =QBP_SCH_TYPE_SINGLE;
    iQBPComparatorType=QBP_MATRIX_TYPE_ORIGIN;
    iQBPSWScore       =0;
    bQBPUseAttitude   =false;
    bQBPRecordSWMatrix=false;
    //sQBPUserBuffer    ="";
    //sQBPSystemBuffer  ="";
    sQBPSearchName    ="";
    pQBPSearchMatrix  =NULL;
    pQBPGraphPath     =NULL;
    iQBPResultPathSize=0;
    iQBPResultQtdPaths=0;
    iQBPMatrixSizeX   =0;
    iQBPMatrixSizeY   =0;
    sQBPUserSongName  ="DummySongName";
    sQBPSystemSongName="DummySongName";
}

CQBPAlignment::CQBPAlignment(QString pQBPSearchName, uint pQBPSearchId)
{
   iQBPSearchID   = pQBPSearchId;
   sQBPSearchName = pQBPSearchName;


   iQBPSearchType    = QBP_SCH_TYPE_SINGLE;
   iQBPComparatorType= QBP_MATRIX_TYPE_ORIGIN;
   iQBPSWScore       = 0;
   bQBPUseAttitude   = false;
   bQBPRecordSWMatrix= false;
   //sQBPUserBuffer    = "";
   //sQBPSystemBuffer  = "";
   sQBPUserSongName  ="DummySongName";
   sQBPSystemSongName="DummySongName";

   iQBPMatrixSizeX= 0;
   iQBPMatrixSizeY= 0;
   iQBPResultPathSize=0;
   iQBPResultQtdPaths=0;

   pQBPSearchMatrix = NULL;
   pQBPGraphPath     =NULL;
}

CQBPAlignment::CQBPAlignment(const CQBPAlignment &obj)
{
   int Idx;
   int Idxi, Idxj;

   iQBPSearchID      = obj.iQBPSearchID;
   iQBPSearchType    = obj.iQBPSearchType;
   iQBPComparatorType= obj.iQBPComparatorType;
   iQBPSWScore       = obj.iQBPSWScore;
   bQBPUseAttitude   = obj.bQBPUseAttitude;
   bQBPRecordSWMatrix= obj.bQBPRecordSWMatrix;
   sQBPUserBuffer    = obj.sQBPUserBuffer;
   sQBPSystemBuffer  = obj.sQBPSystemBuffer;
   sQBPSearchName    = obj.sQBPSearchName;
   sQBPUserSongName  = obj.sQBPUserSongName;
   sQBPSystemSongName= obj.sQBPSystemSongName;

   iQBPMatrixSizeX= obj.iQBPMatrixSizeX;
   iQBPMatrixSizeY= obj.iQBPMatrixSizeY;

   //We are not using the copy constructor becouse the Matrix is static...
   if(iQBPMatrixSizeX >0 && iQBPMatrixSizeY > 0)
   {
      pQBPSearchMatrix     = new (std::nothrow) CQBPMatrixValue*[iQBPMatrixSizeY];
      if(pQBPSearchMatrix==nullptr)
      {
          QMessageBox msgBox;
          msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
          msgBox.exec();
      }

      for (Idx = 0; Idx < iQBPMatrixSizeY; Idx++)
      {
          pQBPSearchMatrix[Idx] = new (std::nothrow) CQBPMatrixValue[iQBPMatrixSizeX];
          if(pQBPSearchMatrix[Idx]==nullptr)
          {
              QMessageBox msgBox;
              msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
              msgBox.exec();
          }
      }

      for (Idxj = 0; Idxj < iQBPMatrixSizeY; Idxj++)
      {
          for (Idxi = 0; Idxi < iQBPMatrixSizeX; Idxi++)
          {
              //for the values we can use the copy constructor...
              pQBPSearchMatrix[Idxj][Idxi].iQBPRefX     =obj.pQBPSearchMatrix[Idxj][Idxi].iQBPRefX;
              pQBPSearchMatrix[Idxj][Idxi].iQBPRefY     =obj.pQBPSearchMatrix[Idxj][Idxi].iQBPRefY;
              pQBPSearchMatrix[Idxj][Idxi].iQBPValue    =obj.pQBPSearchMatrix[Idxj][Idxi].iQBPValue;
              pQBPSearchMatrix[Idxj][Idxi].iQBPDirection=obj.pQBPSearchMatrix[Idxj][Idxi].iQBPDirection;
              pQBPSearchMatrix[Idxj][Idxi].bQBPMatch    =obj.pQBPSearchMatrix[Idxj][Idxi].bQBPMatch;

              //debug info
              pQBPSearchMatrix[Idxj][Idxi].iQBPTopo      = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPTopo;
              pQBPSearchMatrix[Idxj][Idxi].iQBPDiagonal  = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPDiagonal;
              pQBPSearchMatrix[Idxj][Idxi].iQBPLado      = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPLado;
              pQBPSearchMatrix[Idxj][Idxi].iQBPMatch     = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPMatch;
              pQBPSearchMatrix[Idxj][Idxi].iQBPMissMatch = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPMissMatch;
              pQBPSearchMatrix[Idxj][Idxi].iQBPGap       = obj.pQBPSearchMatrix[Idxj][Idxi].iQBPGap;
          }
      }
   }

   iQBPResultPathSize = obj.iQBPResultPathSize;
   iQBPResultQtdPaths = obj.iQBPResultQtdPaths;

   //aloca o espaço necessário...
   pQBPGraphPath = new CQBPMatrixValue[iQBPResultPathSize];
   if(!pQBPGraphPath)
   {
       QMessageBox msgBox;
       msgBox.setText("Erro ao alocar memoria para Path! QBPSearch.");
       msgBox.exec();
   }

   //copia os valores
   for (Idx = 0; Idx < obj.iQBPResultPathSize; Idx++)
   {
       pQBPGraphPath[Idx].iQBPRefX      =obj.pQBPGraphPath[Idx].iQBPRefX;
       pQBPGraphPath[Idx].iQBPRefY      =obj.pQBPGraphPath[Idx].iQBPRefY;
       pQBPGraphPath[Idx].iQBPValue     =obj.pQBPGraphPath[Idx].iQBPValue;
       pQBPGraphPath[Idx].iQBPDirection =obj.pQBPGraphPath[Idx].iQBPDirection;
       pQBPGraphPath[Idx].bQBPMatch     =obj.pQBPGraphPath[Idx].bQBPMatch;

       //debug info
       pQBPGraphPath[Idx].iQBPTopo      = obj.pQBPGraphPath[Idx].iQBPTopo;
       pQBPGraphPath[Idx].iQBPDiagonal  = obj.pQBPGraphPath[Idx].iQBPDiagonal;
       pQBPGraphPath[Idx].iQBPLado      = obj.pQBPGraphPath[Idx].iQBPLado;
       pQBPGraphPath[Idx].iQBPMatch     = obj.pQBPGraphPath[Idx].iQBPMatch;
       pQBPGraphPath[Idx].iQBPMissMatch = obj.pQBPGraphPath[Idx].iQBPMissMatch;
       pQBPGraphPath[Idx].iQBPGap       = obj.pQBPGraphPath[Idx].iQBPGap;
   }

   //aloca o espaço necessário...
   pQBPGraphPathList = new stQBPGraphListMember[iQBPResultQtdPaths];
   if(!pQBPGraphPathList)
   {
       QMessageBox msgBox;
       msgBox.setText("Erro ao alocar memoria para Lista Path! QBPSearch.");
       msgBox.exec();
   }

   //Initialize the graph Lists
   for (Idx = 0; Idx < iQBPResultQtdPaths; Idx++)
   {
       pQBPGraphPathList[Idx].iQBP_QtdPathNotes = obj.pQBPGraphPathList[Idx].iQBP_QtdPathNotes;
       pQBPGraphPathList[Idx].pQBPGraphPath     = new CQBPMatrixValue[pQBPGraphPathList[Idx].iQBP_QtdPathNotes];
   }

   //Copy the Values...
   for (Idx = 0; Idx < iQBPResultQtdPaths; Idx++)
   {
       for(uint i=0;i<obj.pQBPGraphPathList[Idx].iQBP_QtdPathNotes;i++)
       {
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefX      =obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefX;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefY      =obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefY;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPValue     =obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPValue;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDirection =obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDirection;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].bQBPMatch     =obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].bQBPMatch;

          //debug info
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPTopo      = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPTopo;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDiagonal  = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDiagonal;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPLado      = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPLado;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMatch     = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMatch;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMissMatch = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMissMatch;
          pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPGap       = obj.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPGap;
       }
   }


}

CQBPAlignment & CQBPAlignment::operator = (const CQBPAlignment& other)
{
    int Idx;
    int Idxi, Idxj;

    iQBPSearchID       = other.iQBPSearchID;
    iQBPSearchType     = other.iQBPSearchType;
    iQBPComparatorType = other.iQBPComparatorType;
    iQBPSWScore        = other.iQBPSWScore;
    bQBPUseAttitude    = other.bQBPUseAttitude;
    bQBPRecordSWMatrix = other.bQBPRecordSWMatrix;
    sQBPUserBuffer     = other.sQBPUserBuffer;
    sQBPSystemBuffer   = other.sQBPSystemBuffer;
    sQBPSearchName     = other.sQBPSearchName;
    iQBPResultPathSize = other.iQBPResultPathSize;
    iQBPResultQtdPaths = other.iQBPResultQtdPaths;
    sQBPUserSongName   = other.sQBPUserSongName;
    sQBPSystemSongName = other.sQBPSystemSongName;

    iQBPMatrixSizeX= other.iQBPMatrixSizeX;
    iQBPMatrixSizeY= other.iQBPMatrixSizeY;

    //We are not using the copy constructor becouse the Matrix is static...
    if(iQBPMatrixSizeX >0 && iQBPMatrixSizeY > 0)
    {
       pQBPSearchMatrix     = new (std::nothrow) CQBPMatrixValue*[iQBPMatrixSizeY];
       if(pQBPSearchMatrix==nullptr)
       {
           QMessageBox msgBox;
           msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
           msgBox.exec();
       }

       for (Idx = 0; Idx < iQBPMatrixSizeY; Idx++)
       {
           pQBPSearchMatrix[Idx] = new (std::nothrow) CQBPMatrixValue[iQBPMatrixSizeX];
           if(pQBPSearchMatrix[Idx]==nullptr)
           {
               QMessageBox msgBox;
               msgBox.setText("Não foi possível alocar memoria para Substitution Matrix!.");
               msgBox.exec();
           }
       }

       for (Idxj = 0; Idxj < iQBPMatrixSizeY; Idxj++)
       {
           for (Idxi = 0; Idxi < iQBPMatrixSizeX; Idxi++)
           {
               //for the values we can use the copy constructor...
               pQBPSearchMatrix[Idxj][Idxi].iQBPRefX     =other.pQBPSearchMatrix[Idxj][Idxi].iQBPRefX;
               pQBPSearchMatrix[Idxj][Idxi].iQBPRefY     =other.pQBPSearchMatrix[Idxj][Idxi].iQBPRefY;
               pQBPSearchMatrix[Idxj][Idxi].iQBPValue    =other.pQBPSearchMatrix[Idxj][Idxi].iQBPValue;
               pQBPSearchMatrix[Idxj][Idxi].iQBPDirection=other.pQBPSearchMatrix[Idxj][Idxi].iQBPDirection;
               pQBPSearchMatrix[Idxj][Idxi].bQBPMatch    =other.pQBPSearchMatrix[Idxj][Idxi].bQBPMatch;

               //debug info
               pQBPSearchMatrix[Idxj][Idxi].iQBPTopo      = other.pQBPSearchMatrix[Idxj][Idxi].iQBPTopo;
               pQBPSearchMatrix[Idxj][Idxi].iQBPDiagonal  = other.pQBPSearchMatrix[Idxj][Idxi].iQBPDiagonal;
               pQBPSearchMatrix[Idxj][Idxi].iQBPLado      = other.pQBPSearchMatrix[Idxj][Idxi].iQBPLado;
               pQBPSearchMatrix[Idxj][Idxi].iQBPMatch     = other.pQBPSearchMatrix[Idxj][Idxi].iQBPMatch;
               pQBPSearchMatrix[Idxj][Idxi].iQBPMissMatch = other.pQBPSearchMatrix[Idxj][Idxi].iQBPMissMatch;
               pQBPSearchMatrix[Idxj][Idxi].iQBPGap       = other.pQBPSearchMatrix[Idxj][Idxi].iQBPGap;
           }
       }
    }

    pQBPGraphPath = NULL;

    //aloca o espaço necessário...
    pQBPGraphPath = new CQBPMatrixValue[iQBPResultPathSize];
    if(!pQBPGraphPath)
    {
        QMessageBox msgBox;
        msgBox.setText("Erro ao alocar memoria para Path! QBPSearch.");
        msgBox.exec();
    }

    //copia os valores
    for (Idx = 0; Idx < other.iQBPResultPathSize; Idx++)
    {
        pQBPGraphPath[Idx].iQBPRefX      =other.pQBPGraphPath[Idx].iQBPRefX;
        pQBPGraphPath[Idx].iQBPRefY      =other.pQBPGraphPath[Idx].iQBPRefY;
        pQBPGraphPath[Idx].iQBPValue     =other.pQBPGraphPath[Idx].iQBPValue;
        pQBPGraphPath[Idx].iQBPDirection =other.pQBPGraphPath[Idx].iQBPDirection;
        pQBPGraphPath[Idx].bQBPMatch     =other.pQBPGraphPath[Idx].bQBPMatch;

        //debug info
        pQBPGraphPath[Idx].iQBPTopo      = other.pQBPGraphPath[Idx].iQBPTopo;
        pQBPGraphPath[Idx].iQBPDiagonal  = other.pQBPGraphPath[Idx].iQBPDiagonal;
        pQBPGraphPath[Idx].iQBPLado      = other.pQBPGraphPath[Idx].iQBPLado;
        pQBPGraphPath[Idx].iQBPMatch     = other.pQBPGraphPath[Idx].iQBPMatch;
        pQBPGraphPath[Idx].iQBPMissMatch = other.pQBPGraphPath[Idx].iQBPMissMatch;
        pQBPGraphPath[Idx].iQBPGap       = other.pQBPGraphPath[Idx].iQBPGap;
    }

    //aloca o espaço necessário...
    pQBPGraphPathList = new stQBPGraphListMember[iQBPResultQtdPaths];
    if(!pQBPGraphPathList)
    {
        QMessageBox msgBox;
        msgBox.setText("Erro ao alocar memoria para Lista Path! QBPSearch.");
        msgBox.exec();
    }

    //Initialize the graph Lists
    for (Idx = 0; Idx < iQBPResultQtdPaths; Idx++)
    {
        pQBPGraphPathList[Idx].iQBP_QtdPathNotes = other.pQBPGraphPathList[Idx].iQBP_QtdPathNotes;
        pQBPGraphPathList[Idx].pQBPGraphPath     = new CQBPMatrixValue[pQBPGraphPathList[Idx].iQBP_QtdPathNotes];
    }

    //Copy the Values...
    for (Idx = 0; Idx < iQBPResultQtdPaths; Idx++)
    {
        for(uint i=0;i<other.pQBPGraphPathList[Idx].iQBP_QtdPathNotes;i++)
        {
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefX      =other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefX;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefY      =other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPRefY;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPValue     =other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPValue;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDirection =other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDirection;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].bQBPMatch     =other.pQBPGraphPathList[Idx].pQBPGraphPath[i].bQBPMatch;

           //debug info
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPTopo      = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPTopo;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDiagonal  = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPDiagonal;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPLado      = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPLado;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMatch     = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMatch;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMissMatch = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPMissMatch;
           pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPGap       = other.pQBPGraphPathList[Idx].pQBPGraphPath[i].iQBPGap;
        }
    }

    return *this;
}

int CQBPAlignment::getNode(int x, int y,int &pDir,bool &pMatch)
{
    if (x > iQBPMatrixSizeX || y > iQBPMatrixSizeY || x < 0 || y < 0)return 0;//caso esteja fora dos indices

    //repassa a direção e acerto
    pDir    = pQBPSearchMatrix[y][x].iQBPDirection;
    pMatch  = pQBPSearchMatrix[y][x].bQBPMatch;
    //retorna o valor
    return pQBPSearchMatrix[y][x].iQBPValue;
}

void CQBPAlignment::getDebug(int x, int y, int &piQBPTopo ,int  &piQBPDiagonal ,int &piQBPLado,int &piQBPMatch,int &piQBPMissMatch,int &piQBPGap)
{
    if (x > iQBPMatrixSizeX || y > iQBPMatrixSizeY || x < 0 || y < 0)return;//caso esteja fora dos indices

    //repassa a direção e acerto
    piQBPTopo       = pQBPSearchMatrix[y][x].iQBPTopo;
    piQBPDiagonal   = pQBPSearchMatrix[y][x].iQBPDiagonal;
    piQBPLado       = pQBPSearchMatrix[y][x].iQBPLado;
    piQBPMatch      = pQBPSearchMatrix[y][x].iQBPMatch;
    piQBPMissMatch  = pQBPSearchMatrix[y][x].iQBPMissMatch;
    piQBPGap        = pQBPSearchMatrix[y][x].iQBPGap;
}

bool CQBPAlignment::getGraphPath(QVector<QPointF> &pQBPPath)
{
    int Idx;

    //Limpa antes de copiar o path
    if(pQBPPath.size()>0)
    {
        pQBPPath.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPPath.shrink_to_fit();
    }

    for (Idx = 0; Idx < iQBPResultPathSize; Idx++)
    {
        pQBPPath.push_back(QPointF(pQBPGraphPath[Idx].iQBPRefX,pQBPGraphPath[Idx].iQBPRefY));
    }

    return true;
}

